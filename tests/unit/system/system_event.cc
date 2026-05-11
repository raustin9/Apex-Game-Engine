#include <apex/apex.h>
#include <catch2/catch_test_macros.hpp>

template <typename T>
void
test_event(T data)
{
    apx::Event event{ data };

    REQUIRE(event.is<T>());
}

TEST_CASE("basic event type", "[system_event]")
{
    test_event(apx::system::KeyUp{ .key = apx::Key::Code::A });
    test_event(apx::system::WindowOpen{});
}

TEST_CASE("system event handler", "[system_event]")
{
    bool                                                          lambda_called = false;
    apx::system::SystemEventHandler<apx::system::SystemEventList> handler{};

    auto handle = handler.on<apx::system::WindowClose>(
        [&](apx::system::WindowClose ev) { lambda_called = true; });

    handler.dispatch(apx::system::WindowClose{});

    const auto event = handler.next_event();
    REQUIRE(event.is<apx::system::WindowClose>());
    REQUIRE_FALSE(event.is<apx::system::WindowOpen>());
    REQUIRE(lambda_called);
    REQUIRE(handler.remove_listener<apx::system::WindowClose>(handle));
}
