#include <apex/apex.h>
#include <iostream>

int
main(void)
{
    bool running = true;

    apx::expected<std::shared_ptr<apx::system::DisplayServer>, apx::system::SystemError>
        exp_display_server = apx::system::DisplayServer::create();

    if ( !exp_display_server )
        {
            std::cerr << "Failed to create display server" << std::endl;
            return 1;
        }

    std::shared_ptr<apx::system::DisplayServer> display_server = exp_display_server.value();
    std::shared_ptr<apx::system::Display>       display
        = display_server
              ->spawn_display(apx::system::Display::CreateOptions{
                  .title = "Apex Test Window",
              })
              .value();

    std::cout << "(" << display->current_width() << ", " << display->current_height() << ")"
              << std::endl;

    const auto handle
        = display->on<apx::system::DisplayClose>([&running](apx::system::DisplayClose close) {
              (void)close;
              running = false;
          });

    const auto escape_handle
        = display->on<apx::system::KeyDown>([&running](apx::system::KeyDown ev) {
              if ( ev.key != apx::Key::Code::Esc ) [[likely]]
                  return;

              std::cout << "Esc pressed. Ending application" << std::endl;
              running = false;
          });

    const auto key_handle = display->on<apx::system::KeyUp>(
        [](apx::system::KeyUp ev) { std::cout << "Key pressed: " << ev.key << std::endl; });

    while ( running )
        {
            display_server->pump_events();
            while ( const std::optional event = display->next_event() )
                {
                    if ( event->is<apx::system::MouseMoved>() )
                        {
                            std::cout << "Mouse moved: ("
                                      << event->get<apx::system::MouseMoved>().position.x << ", "
                                      << event->get<apx::system::MouseMoved>().position.y << ")"
                                      << std::endl;
                        }
                }
        }

    (void)display->remove_listener<apx::system::DisplayClose>(handle);
    (void)display->remove_listener<apx::system::KeyDown>(escape_handle);

    return 0;
}