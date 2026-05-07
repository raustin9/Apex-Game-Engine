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