#include <apex/apex.h>
#include <catch2/catch_test_macros.hpp>
#include <chrono>
#include <iostream>
#include <thread>

TEST_CASE("startup and close immediately", "[system]")
{
    auto system = apx::system::System::create();
    while ( system->is_running() )
        {
            system->update();

            REQUIRE(system->is_running());
            REQUIRE(system->main_window().is_open());

            system->main_window().close();
            REQUIRE_FALSE(system->main_window().is_open());
        }
    system->shutdown();
}

TEST_CASE("test window dimensions", "[system]")
{
    const std::string     WINDOW_NAME{ "TEST WINDOW" };
    const apx::Width_u32  WIDTH{ 800 };
    const apx::Height_u32 HEIGHT{ 600 };
    const float           ASPECT_RATIO{ static_cast<float>(WIDTH.get()) / HEIGHT.get() };

    apx::expected<apx::system::System, apx::system::SystemError> system
        = apx::system::System::create(apx::system::WindowOptions{
            .title  = WINDOW_NAME,
            .extent = {
                       .width  = WIDTH,
                       .height = HEIGHT,
                       }
    });

    while ( system->is_running() )
        {
            system->update();

            REQUIRE(system->is_running());
            REQUIRE(system->main_window().is_open());
            REQUIRE(system->main_window().width() == WIDTH);
            REQUIRE(system->main_window().height() == HEIGHT);
            REQUIRE(WINDOW_NAME == std::string(system->main_window().title()));
            REQUIRE(system->main_window().aspect_ratio() == ASPECT_RATIO);

            system->main_window().close();
            REQUIRE_FALSE(system->main_window().is_open());
        }
    system->shutdown();
}

TEST_CASE("test window resize", "[system]")
{
    const std::string     WINDOW_NAME{ "TEST WINDOW" };
    const apx::Width_u32  WIDTH{ 800 };
    const apx::Height_u32 HEIGHT{ 600 };
    const float           ASPECT_RATIO{ static_cast<float>(WIDTH.get()) / HEIGHT.get() };

    const apx::Width_u32  NEW_WIDTH{ 1000 };
    const apx::Height_u32 NEW_HEIGHT{ 1000 };
    const float NEW_ASPECT_RATIO{ static_cast<float>(NEW_WIDTH.get()) / NEW_HEIGHT.get() };

    apx::expected<apx::system::System, apx::system::SystemError> system
        = apx::system::System::create(apx::system::WindowOptions{
            .title  = WINDOW_NAME,
            .extent = {
                       .width  = WIDTH,
                       .height = HEIGHT,
                       }
    });

    while ( system->is_running() )
        {
            system->update();

            REQUIRE(system->is_running());
            REQUIRE(system->main_window().is_open());
            REQUIRE(system->main_window().width() == WIDTH);
            REQUIRE(system->main_window().height() == HEIGHT);
            REQUIRE(WINDOW_NAME == std::string(system->main_window().title()));
            REQUIRE(system->main_window().aspect_ratio() == ASPECT_RATIO);

            system->main_window().resize(NEW_WIDTH, NEW_HEIGHT);

            // TODO: when we have event dispatching just read
            //       the event for finish resize instead of this
            std::this_thread::sleep_for(std::chrono::milliseconds(200));

            system->main_window().close();
            REQUIRE_FALSE(system->main_window().is_open());
            REQUIRE_FALSE(system->is_running());
        }

    REQUIRE(system->main_window().width() == NEW_WIDTH);
    REQUIRE(system->main_window().height() == NEW_HEIGHT);
    system->shutdown();
}

void
test_key(apx::Key::Code key_code, std::string expected_string, std::string_view expected_sv,
         bool is_alpha, bool is_numeric)
{

    apx::Key key  = key_code;
    apx::Key key2 = key_code;
    REQUIRE(key.code() == key_code);
    REQUIRE(key == key_code);
    REQUIRE(key == key2);

    std::stringstream ss;
    ss << key;
    std::string extracted_string = ss.str();
    REQUIRE(expected_string == extracted_string);

    REQUIRE(is_alpha == key.is_alpha());
    REQUIRE(is_numeric == key.is_numeric());
}

TEST_CASE("key", "[system]")
{
    test_key(apx::Key::Code::A, "A", "A", true, false);
    test_key(apx::Key::Code::Z, "Z", "Z", true, false);
    test_key(apx::Key::Code::Num1, "Num1", "Num1", false, true);
    test_key(apx::Key::Code::Num2, "Num2", "Num2", false, true);
    test_key(apx::Key::Code::Num3, "Num3", "Num2", false, true);
    test_key(apx::Key::Code::Num4, "Num4", "Num4", false, true);
    test_key(apx::Key::Code::Num5, "Num5", "Num5", false, true);
    test_key(apx::Key::Code::Num6, "Num6", "Num6", false, true);
    test_key(apx::Key::Code::Num7, "Num7", "Num7", false, true);
    test_key(apx::Key::Code::Num8, "Num8", "Num8", false, true);
    test_key(apx::Key::Code::Num9, "Num9", "Num9", false, true);
    test_key(apx::Key::Code::Num0, "Num0", "Num0", false, true);
}