#include <apex/apex.h>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("basic system startup", "[system]")
{
    auto system = apx::system::System::create();
    while ( system->is_running() )
        {
            system->update();
        }
    system->shutdown();
}