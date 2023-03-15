#include "../core.h"

void core::control_process()
{
    while (true)
    {
        wait();
    }
}

void core::read(int* data, int start_addr, int len)
{
}

int core::write(std::vector<float> &data, int len)
{
    return 0;
}
