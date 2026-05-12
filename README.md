# Apex Game Engine

## Display

`apx::system::Display` is the tool for windowing on desktop and the interactive display on a console (or other
non-windowing platforms).

#### Opening a display

```c++
apx::expected<apx::system::DisplayManager, apx::system::SystemError> display_manager
    = apx::system::DisplayManager::create().value();
    
apx::expected<std::shared_ptr<apx::system::Display, apx::system::SystemError> main_display
    = display_manager->spawn_display(apx::system::Dislay::CreateOptions {
        .title = "My Display"
    })
    .value();
```

#### Event handling

We support both callback functions and polling for events

```c++
// Callbacks
main_display->on<apx::system::KeyDown>(
    [&should_close](const apx::system::KeyUp ev) {
        switch ( ev.key.code() )
        {
            case apx::Key::Code::Esc:
                should_close = true;
                break;
            default:
                break;
        }
    }
);

// Event polling
do {
    while ( std::optional ev = main_display->next_event() )
    {
        if ( ev.is<apx::system::DisplayResized>() )
        {
            std::cout << "Display resized: ("
                << event->get<apx::system::DisplayResized>().new_origin.x
                << ", "
                << event->get<apx::system::DisplayResized>().new_origin.y << ")"
                << std::endl;
        }
    }
} while ( !should_close && display_manager->pump_events() );
```

### Programmatic manipulation of display

```c++
main_display->set_title("New Title");

main_display->resize(apx::Extent2D_u32{ 
    apx::Width_u32{ 1920 },
    apx::Height_u32{ 1080 }
});


// etc.
```