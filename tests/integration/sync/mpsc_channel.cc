#include <apex/apex.h>
#include <catch2/catch_test_macros.hpp>
#include <thread>

template <typename T>
void
test_mpsc_channel(const T expected_result)
{
    auto [reader, writer] = apx::sync::mpsc::Channel<T>::create();

    std::thread t([writer, expected_result]() mutable { writer.write(expected_result); });

    REQUIRE(reader.read() == expected_result);

    t.join();
}

TEST_CASE("write + read primitives", "[mpsc_channel]")
{
    test_mpsc_channel<int>(10);
    test_mpsc_channel<float>(10.0);
    test_mpsc_channel<double>(1000000000.0);
}

TEST_CASE("write + read custom object", "[mpsc_channel]")
{
    class Tracker
    {
      public:
        explicit Tracker(std::string_view name) : m_name(name) {}

        bool
        operator==(const Tracker &other) const
        {
            return m_name == other.m_name;
        }

      private:
        std::string m_name;
    };

    const Tracker tracker{ "test" };
    test_mpsc_channel(tracker);
}
TEST_CASE("write + read move-only object", "[mpsc_channel]")
{
    class MoveOnlyTracker
    {
      public:
        explicit MoveOnlyTracker(std::string_view name) : m_name(name) {}

        bool
        operator==(const std::string &name) const
        {
            return m_name == name;
        }

        MoveOnlyTracker(const MoveOnlyTracker &other)            = delete;
        MoveOnlyTracker &operator=(const MoveOnlyTracker &other) = delete;
        MoveOnlyTracker(MoveOnlyTracker &&other)                 = default;
        MoveOnlyTracker &operator=(MoveOnlyTracker &&other)      = default;

      private:
        std::string m_name;
    };

    std::string     name{ "test" };
    MoveOnlyTracker tracker{ name };

    auto [reader, writer] = apx::sync::mpsc::Channel<MoveOnlyTracker>::create();
    std::thread t(
        [writer, tracker = std::move(tracker)]() mutable { writer.write(std::move(tracker)); });

    REQUIRE(reader.read() == name);
    t.join();
}
