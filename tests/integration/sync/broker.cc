#include <apex/apex.h>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("add subscriber", "[mpmc_broker]")
{
    apx::sync::Broker<int> broker{};
    auto                   callback = [](int i) { return i; };

    (void)broker.subscribe(callback);
    REQUIRE(broker.num_subscriptions() == 1);
}

TEST_CASE("remove subscriber", "[mpmc_broker]")
{
    apx::sync::Broker<int> broker{};
    auto                   callback = [](int i) { return i; };

    auto                   handle = broker.subscribe(callback);
    REQUIRE(broker.num_subscriptions() == 1);

    REQUIRE(broker.unsubscribe(handle));
    REQUIRE(broker.num_subscriptions() == 0);
}

TEST_CASE("subscribe and notify (1)", "[mpmc_broker]")
{
    constexpr int          Expected = 1;
    apx::sync::Broker<int> broker{};
    auto                   callback = [](int i) { REQUIRE(i == Expected); };

    (void)broker.subscribe(callback);
    REQUIRE(broker.num_subscriptions() == 1);

    auto publisher = broker.get_publisher();
    publisher.notify(Expected);
}
