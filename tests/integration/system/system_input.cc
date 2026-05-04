#include <apex/apex.h>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("key down", "[system_input]")
{
    apx::system::InputHandler<apx::system::SystemEvents> input_handler;
    input_handler.fire<apx::system::KeyDown>(apx::Key::Code::A);
}

TEST_CASE("window resized", "[system_input]")
{
    apx::system::InputHandler<apx::system::SystemEvents> input_handler;
    input_handler.fire<apx::system::WindowResized>(apx::Width_f32(100), apx::Height_f32(100));
}
