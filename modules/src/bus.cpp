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
    // TODO: 
    /*return memory_inst->read(start_addr, len);*/
    return read_data;
}

void bus::write(std::vector<float>& data, int start_address)
{
    for (int i = 0; i < BUFFER_SIZE;++i)
    {
        queue q{data, start_address}; 
        write_queue_.emplace_back(q);    
    }
    
}

bool bus::mem_is_busy()
{
    /*return memory_inst->mem_is_busy() && !write_queue_.empty();*/
    return memory_is_busy.read() && !write_queue_.empty();
}

bool bus::is_busy(int core_num)
{
    return core_inst[core_num]->is_busy(core_num);
}

bool bus::core_task(int core_num, std::vector<float>& neurons, std::vector<std::vector<float>>& weight,
                    int start_address, bool is_last)
{
    return core_inst[core_num]->core_task(core_num, neurons, weight, start_address, is_last);
}

void bus::process()
{
    while (true)
    {
        // если есть элементы на запись
        if (!write_queue_.empty())
        {
            memory_wr.write(true);
            queue q = write_queue_.front();
            write_queue_.erase(write_queue_.begin());
            memory_write(q);
            memory_wr.write(false);
        }
        wait();
    }
}

void bus::memory_write(const queue& queue)
{
    memory_start_addr_i.write(queue.start_address_);
    memory_len_i.write(queue.data_.size());
    for (int i = 0; i < memory_len_i; ++i)
    {
        memory_data_i[i].write(queue.data_[i]);
    }
}

void bus::memory_read()
{
    // TODO: 
}
