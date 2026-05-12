#include <apex/apex.h>
#include <iostream>

#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif // EXIT_FAILURE

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif // EXIT_SUCCESS

int
main(void)
{
    bool                    running  = true;
    bool                    is_large = false;

    const apx::Extent2D_u32 original_extent
        = apx::Extent2D_u32{ apx::Width_u32(640), apx::Height_u32(480) };
    const apx::Extent2D_u32 large_extent
        = apx::Extent2D_u32{ apx::Width_u32(1920), apx::Height_u32(1080) };

    apx::expected<std::shared_ptr<apx::system::DisplayServer>, apx::system::SystemError>
        exp_display_server = apx::system::DisplayServer::create();

    if ( !exp_display_server )
        {
            std::cerr << "Failed to create display server" << std::endl;
            std::exit(EXIT_FAILURE);
        }

    std::shared_ptr<apx::system::DisplayServer> display_server = exp_display_server.value();
    std::shared_ptr<apx::system::Display>       display
        = display_server
              ->spawn_display(apx::system::Display::CreateOptions{
                  .title  = "Apex Test Window",
                  .extent = original_extent,
              })
              .value();

    std::cout << "(" << display->current_width() << ", " << display->current_height() << ")"
              << std::endl;

    // Callback for DisplayClose
    const auto handle
        = display->on<apx::system::DisplayClose>([&running](const apx::system::DisplayClose ev) {
              (void)ev;
              running = false;
          });

    // Callback for KeyDown events (kill application on Esc)
    const auto escape_handle
        = display->on<apx::system::KeyDown>([&running](const apx::system::KeyDown ev) {
              if ( ev.key != apx::Key::Code::Esc ) [[likely]]
                  return;

              std::cout << "Esc pressed. Ending application" << std::endl;
              running = false;
          });

    // Callback for KeyUp events
    const auto key_handle = display->on<apx::system::KeyUp>(
        [&display, &is_large, large_extent, original_extent](const apx::system::KeyUp ev) {
            std::cout << "Key pressed: " << ev.key << std::endl;

            switch ( ev.key.code() )
                {
                case apx::Key::Code::T:
                    display->set_title("New Title");
                    break;
                case apx::Key::Code::R:
                    if ( is_large )
                        display->resize(original_extent);
                    else
                        display->resize(large_extent);

                    is_large = !is_large;
                    break;
                default:
                    break;
                }
        });

    // Callback for DisplayResized events
    const auto resize_handle
        = display->on<apx::system::DisplayResized>([](const apx::system::DisplayResized ev) {
              std::cout << "Display resized: (" << ev.extent.width << ", " << ev.extent.height
                        << ")" << std::endl;
          });

    while ( running )
        {
            display_server->pump_events();

            // Poll events
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
    (void)display->remove_listener<apx::system::KeyUp>(key_handle);
    (void)display->remove_listener<apx::system::DisplayResized>(resize_handle);

    return EXIT_SUCCESS;
}