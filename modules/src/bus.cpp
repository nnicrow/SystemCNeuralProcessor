#include "../bus.h"


queue::queue(): start_address_(0)
{
}

queue::queue(const std::vector<float>& data, int start_address)
{
    data_ = data;
    start_address_ = start_address;
}

std::vector<float>& bus::read(int start_addr, int len)
{
    std::vector<float> data;
    return data;
}

void bus::write(std::vector<float>& data, int start_address, target current_target, int core_num)
{
    if (current_target == target_memory)
    {
        queue q{data, start_address};
        write_queue_.emplace_back(q);    
    }
    else
    {
        
    }
}

void bus::bus_write_process()
{
    while (true)
    {
        if (write_queue_.empty())
        {
            wait();
            continue;
        }

        queue q = write_queue_.back();
        write_queue_.pop_back();
        slaves_inst->write(q.data_, q.start_address_, target_memory);
        wait();
    }
}
