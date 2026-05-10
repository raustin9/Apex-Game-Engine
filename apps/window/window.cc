#include <apex/apex.h>
#include <iostream>

int
main(void)
{
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

    return 0;
}