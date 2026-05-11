#include <apex/apex.h>
#include <catch2/catch_test_macros.hpp>

template <typename T>
void
test_broker(T data)
{
    auto broker = apx::EventBroker<T>{};
    broker.fire(std::move(data));
}

TEST_CASE("system event handler", "[system_event]") {}

// TEST_CASE("event broker", "[system_event]")
// {
//     test_broker<int>(10);
//     test_broker<float>(10.f);
//     test_broker(apx::system::KeyDown{ apx::Key::Code::A });
//     test_broker(std::string("hello"));
// }
//
// TEST_CASE("event logged", "[system_event]")
// {
//     auto system = apx::system::System::create();
//     while ( system->is_running() )
//         {
//             system->update();
//
//             REQUIRE(system->is_running());
//             REQUIRE(system->main_window().is_open());
//
//             system->main_window().close();
//             REQUIRE_FALSE(system->main_window().is_open());
//         }
//     system->shutdown();
// }
