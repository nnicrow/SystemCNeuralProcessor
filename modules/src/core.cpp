#include "../core.h"

void core::control_process()
{
    while (true)
    {
        wait();

    }
}

std::vector<float>& core::read(int start_addr, int len)
{
    std::vector<float> data;
    return data;
}

void core::write(std::vector<float> &data, int start_address, target current_target, int core_num)
{
    cout << "core" << endl;
}
