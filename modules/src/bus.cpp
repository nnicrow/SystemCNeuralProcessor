#include "../bus.h"


queue::queue(): start_address_(0)
{
}

queue::queue(const std::vector<float>& data, int start_address)
{
    data_ = data;
    start_address_ = start_address;
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
        // потребляем данные со всех портов и закидываем их в очередь на запись
        for (int i = 0; i < CORE_COUNT + 1; ++i)
        {
            if (bus_memory_wr[i].read())
            {
                get_data_from_port(i);
            }
        }

        // если есть что писать, то пишем в память
        if (!write_queue_.empty())
        {
            bus_memory_is_busy.write(true);
            queue q = write_queue_.front();
            write_queue_.erase(write_queue_.begin());
            memory_write(q);
        }
        else if (bus_memory_rd.read())
        {
            bus_memory_is_busy.write(true);
            memory_read();
        }
        else
        {
            bus_memory_is_busy.write(memory_is_busy.read());
            memory_rd.write(false);
            memory_wr.write(false);
        }

        // если есть что писать, то пишем
        wait();
    }
}

void bus::memory_write(const queue& q)
{
    memory_start_addr_i.write(q.start_address_);
    memory_len_i.write(q.data_.size());
    for (int i = 0; i < q.data_.size(); ++i)
    {
        memory_data_i[i].write(q.data_[i]);
    }
    memory_wr.write(true);
}

void bus::memory_read()
{
    while (bus_memory_rd.read())
    {
        int start_addr = bus_memory_start_addr_i[0].read();
        int len = bus_memory_len_i[0].read();
        
        memory_start_addr_i.write(start_addr);
        memory_len_i.write(len);
        memory_rd.write(true);

        wait(2);

        for (int j = 0; j < len; ++j)
        {
            bus_memory_data_o[j].write(memory_data_o[j].read());    
        }
        wait(3);
    }
    memory_rd.write(false);
}

void bus::get_data_from_port(const int index)
{
    std::vector<float> data;
    data.resize(bus_memory_len_i[index].read());
    for (int i = 0; i < bus_memory_len_i[index].read(); ++i)
    {
        data[i] = bus_memory_data_i[index][i].read();
    }
    queue q{data, bus_memory_start_addr_i[index].read()};
    write_queue_.emplace_back(q);
}
