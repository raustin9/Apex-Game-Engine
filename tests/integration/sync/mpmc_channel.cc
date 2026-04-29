#include <apex/apex.h>
#include <catch2/catch_test_macros.hpp>
#include <thread>

template <typename T>
void
test_mpmc_channel(T expected_result)
{
    auto [reader, writer] = apx::sync::mpmc::Channel<T>::create();

    STATIC_REQUIRE(std::is_copy_constructible_v<typename apx::sync::mpmc::Channel<T>::Reader>);
    STATIC_REQUIRE(std::is_copy_assignable_v<typename apx::sync::mpmc::Channel<T>::Reader>);
    STATIC_REQUIRE(std::is_move_constructible_v<typename apx::sync::mpmc::Channel<T>::Reader>);
    STATIC_REQUIRE(std::is_move_assignable_v<typename apx::sync::mpmc::Channel<T>::Reader>);

    STATIC_REQUIRE(std::is_copy_constructible_v<typename apx::sync::mpmc::Channel<T>::Writer>);
    STATIC_REQUIRE(std::is_copy_assignable_v<typename apx::sync::mpmc::Channel<T>::Writer>);
    STATIC_REQUIRE(std::is_move_constructible_v<typename apx::sync::mpmc::Channel<T>::Writer>);
    STATIC_REQUIRE(std::is_move_assignable_v<typename apx::sync::mpmc::Channel<T>::Writer>);

    std::thread t([writer, expected_result]() mutable { writer.write(expected_result); });

    REQUIRE(reader.read() == expected_result);

    t.join();
}

TEST_CASE("read + write", "[mpmc_channel]")
{
    test_mpmc_channel<int>(10);
    test_mpmc_channel<float>(10.0);
    test_mpmc_channel<double>(1000000000.0);

    std::string test = "test";
    test_mpmc_channel(test);
}
