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

void bus::write(std::vector<float>& data, int start_address)
{
    queue q{data, start_address};
    write_queue_.emplace_back(q);
}

bool bus::is_busy(int core_num)
{
    return core_inst[core_num]->is_busy(core_num);
}

void bus::core_task(int core_num, std::vector<float>& neurons, std::vector<float>& weight, int start_address)
{
    // TODO: проверка на занятость ядра, если оно занято, то ожидаем, пока не освободится
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
        memory_inst->write(q.data_, q.start_address_);
        wait();
    }
}
