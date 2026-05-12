#include <apex/apex.h>
#include <catch2/catch_test_macros.hpp>
#include <chrono>
#include <iostream>
#include <thread>

TEST_CASE("startup and close immediately", "[system]")
{
    const std::string_view title          = "TEST_TITLE";
    bool                   running        = true;
    auto                   display_server = apx::sys::DisplayServer::create().value();
    auto                   display = display_server->spawn_display({ .title = title }).value();

    const auto             handle
        = display->on<apx::sys::DisplayClose>([&running](const apx::sys::DisplayClose ev) {
              (void)ev;
              running = false;
          });

    do
        {
            REQUIRE(display->is_open());
            REQUIRE(display->request_close());
            REQUIRE_FALSE(display->is_open());
        }
    while ( running );

    REQUIRE(display->remove_listener<apx::sys::DisplayClose>(handle));
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