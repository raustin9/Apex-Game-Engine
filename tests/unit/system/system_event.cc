#include <apex/apex.h>
#include <catch2/catch_test_macros.hpp>

template <typename T>
void
test_event(T data)
{
    apx::SystemEvent event{ data };

    REQUIRE(event.is<T>());
}

TEST_CASE("basic event type", "[system_event]")
{
    test_event(apx::sys::KeyUp{ .key = apx::Key::Code::A });
    test_event(apx::sys::DisplayOpen{});
}

template <typename Is, typename Isnt>
void
test_event_handler(Is is, Isnt)
{
    apx::sys::SystemEventHandler<apx::sys::SystemEventList> handler{};
    bool                                                    wrong_callback_called{ false };
    bool                                                    callback_was_called{ false };

    auto handle = handler.on<Is>([&callback_was_called](Is ev) { callback_was_called = true; });
    auto handle2
        = handler.on<Isnt>([&wrong_callback_called](Isnt ev) { wrong_callback_called = true; });

    handler.dispatch(is);

    const std::optional<apx::sys::SystemEvent> event = handler.next_event();

    REQUIRE(event.has_value());
    REQUIRE(event->is<Is>());
    REQUIRE_FALSE(event->is<Isnt>());

    REQUIRE(callback_was_called);
    REQUIRE_FALSE(wrong_callback_called);

    REQUIRE(handler.remove_listener<Is>(handle));
    REQUIRE(handler.remove_listener<Isnt>(handle2));

    const std::optional<apx::sys::SystemEvent> event2 = handler.next_event();
    REQUIRE_FALSE(event2.has_value());
}

TEST_CASE("system event handler", "[system_event]")
{
    test_event_handler(apx::sys::DisplayOpen{}, apx::sys::DisplayClose{});
    test_event_handler(apx::sys::DisplayClose{}, apx::sys::DisplayOpen{});
    test_event_handler(apx::sys::KeyUp{ .key = apx::Key{ apx::Key::Code::A } },
                       apx::sys::DisplayOpen{});
}
