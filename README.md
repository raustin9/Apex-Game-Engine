# Apex Game Engine

## Display

`apx::sys::Display` is the tool for windowing on desktop and the interactive display on a console (or other
non-windowing platforms).

#### Opening a display

```c++
apx::expected<apx::sys::DisplayManager, apx::sys::SystemError> display_manager
    = apx::sys::DisplayManager::create().value();
    
apx::expected<std::shared_ptr<apx::sys::Display, apx::sys::SystemError> main_display
    = display_manager->spawn_display(apx::sys::Dislay::CreateOptions {
        .title = "My Display"
    })
    .value();
```

#### Event handling

We support both callback functions and polling for events

```c++
// Callbacks
main_display->on<apx::sys::KeyDown>(
    [&should_close](const apx::sys::KeyUp ev) {
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
        if ( ev.is<apx::sys::DisplayResized>() )
        {
            std::cout << "Display resized: ("
                << event->get<apx::sys::DisplayResized>().new_origin.x
                << ", "
                << event->get<apx::sys::DisplayResized>().new_origin.y << ")"
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