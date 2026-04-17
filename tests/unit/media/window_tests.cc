#include <catch2/catch_test_macros.hpp>
#include <apex/media/window/window.h>

TEST_CASE( "init window (failure)", "[window]" )
{
    apx::expected<apx::media::Window, apx::media::WindowError> window = apx::media::Window::create(apx::media::Window::Options{
        .title = "",
        .height = 480,
        .width = 640,
    });

    REQUIRE_FALSE(window);
    REQUIRE_FALSE(window.has_value());
}

TEST_CASE( "init window (success)", "[window]" )
{
    apx::expected<apx::media::Window, apx::media::WindowError> window = apx::media::Window::create(apx::media::Window::Options{
        .title = "Apex Window",
        .height = 480,
        .width = 640,
    });

    REQUIRE(window);
    REQUIRE(window.has_value());

}
