#include <apex/apex.h>
#include <iostream>

int
main(void)
{
    auto system = apx::system::System::create();
    while ( system->is_running() )
        {
            system->update();
        }

    system->shutdown();
}