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
    test_event(apx::system::KeyUp{ .key = apx::Key::Code::A });
    test_event(apx::system::WindowOpen{});
}

template <typename Is, typename Isnt>
void
test_event_handler(Is is, Isnt)
{
    apx::system::SystemEventHandler<apx::system::SystemEventList> handler{};
    bool                                                          wrong_callback_called{ false };
    bool                                                          callback_was_called{ false };

    auto handle = handler.on<Is>([&callback_was_called](Is ev) { callback_was_called = true; });
    auto handle2
        = handler.on<Isnt>([&wrong_callback_called](Isnt ev) { wrong_callback_called = true; });

    handler.dispatch(is);

    const std::optional<apx::system::SystemEvent> event = handler.next_event();

    REQUIRE(event.has_value());
    REQUIRE(event->is<Is>());
    REQUIRE_FALSE(event->is<Isnt>());

    REQUIRE(callback_was_called);
    REQUIRE_FALSE(wrong_callback_called);

    REQUIRE(handler.remove_listener<Is>(handle));
    REQUIRE(handler.remove_listener<Isnt>(handle2));

    const std::optional<apx::system::SystemEvent> event2 = handler.next_event();
    REQUIRE_FALSE(event2.has_value());
}

TEST_CASE("system event handler", "[system_event]")
{
    test_event_handler(apx::system::WindowOpen{}, apx::system::WindowClose{});
    test_event_handler(apx::system::WindowClose{}, apx::system::WindowOpen{});
    test_event_handler(apx::system::KeyUp{ .key = apx::Key{ apx::Key::Code::A } },
                       apx::system::WindowOpen{});
}
