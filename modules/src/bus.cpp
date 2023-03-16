#include "../bus.h"


std::vector<float>& bus::read(int start_addr, int len)
{
    std::vector<float> data;
    return data;
}

void bus::write(std::vector<float> &data, int start_address)
{
    queue q{data, start_address};
    queue_.emplace_back(q);
}

void bus::write_process()
{
    while (true)
    {
        cout << "write_process" << endl;
        wait();
    }
}
