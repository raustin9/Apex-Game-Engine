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
    bool                        running  = true;
    bool                        is_large = false;

    constexpr apx::Extent2D_u32 original_extent
        = apx::Extent2D_u32{ apx::Width_u32(640), apx::Height_u32(480) };
    constexpr apx::Extent2D_u32 large_extent
        = apx::Extent2D_u32{ apx::Width_u32(1920), apx::Height_u32(1080) };

    apx::expected exp_display_server = apx::sys::DisplayServer::create();

    if ( !exp_display_server )
        {
            std::cerr << "Failed to create display server" << std::endl;
            std::exit(EXIT_FAILURE);
        }

    std::shared_ptr<apx::sys::DisplayServer> display_server = exp_display_server.value();
    std::shared_ptr<apx::sys::Display>       display
        = display_server
              ->spawn_display(apx::sys::Display::CreateOptions{
                  .title  = "Apex Test Window",
                  .extent = original_extent,
              })
              .value();

    std::cout << "(" << display->inner_width() << ", " << display->inner_height() << ")"
              << std::endl;

    // Callback for DisplayClose
    const auto handle
        = display->on<apx::sys::DisplayClose>([&running](const apx::sys::DisplayClose ev) {
              (void)ev;
              running = false;
          });

    // Callback for KeyDown events (kill application on Esc)
    const auto escape_handle
        = display->on<apx::sys::KeyDown>([&running](const apx::sys::KeyDown ev) {
              if ( ev.key != apx::Key::Code::Esc ) [[likely]]
                  return;

              std::cout << "Esc pressed. Ending application" << std::endl;
              running = false;
          });

    // Callback for KeyUp events
    const auto key_handle = display->on<apx::sys::KeyUp>(
        [&display, &is_large, large_extent, original_extent](const apx::sys::KeyUp ev) {
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
                case apx::Key::Code::P:
                    display->reposition(apx::Point2D_u32(50, 50));
                    break;
                default:
                    break;
                }
        });

    // Callback for DisplayResized events
    const auto resize_handle
        = display->on<apx::sys::DisplayResized>([](const apx::sys::DisplayResized ev) {
              std::cout << "Display resized: (" << ev.extent.width << ", " << ev.extent.height
                        << ")" << std::endl;
          });

    while ( running )
        {
            display_server->pump_events();

            // Poll events
            while ( const std::optional event = display->next_event() )
                {
                    if ( event->is<apx::sys::MouseMoved>() )
                        {
                            std::cout << "Mouse moved: ("
                                      << event->get<apx::sys::MouseMoved>().position.x << ", "
                                      << event->get<apx::sys::MouseMoved>().position.y << ")"
                                      << std::endl;
                        }
                    else if ( event->is<apx::sys::DisplayMoved>() )
                        {
                            std::cout << "Display moved: ("
                                      << event->get<apx::sys::DisplayMoved>().new_origin.x << ", "
                                      << event->get<apx::sys::DisplayMoved>().new_origin.y << ")"
                                      << std::endl;
                        }
                }
        }

    (void)display->remove_listener<apx::sys::DisplayClose>(handle);
    (void)display->remove_listener<apx::sys::KeyDown>(escape_handle);
    (void)display->remove_listener<apx::sys::KeyUp>(key_handle);
    (void)display->remove_listener<apx::sys::DisplayResized>(resize_handle);

    return EXIT_SUCCESS;
}