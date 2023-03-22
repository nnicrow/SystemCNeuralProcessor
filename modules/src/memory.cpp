#include "../memory.h"

void memory::read()
{
    cout << "Memory read data at " << memory_start_addr_i.read() << endl;
    for (int i = 0; i < memory_len_i.read(); ++i)
    {
        memory_data_o[i].write(memory_data_[memory_start_addr_i.read() + i]);
    }
    wait(4);
}

void memory::write()
{
    cout << "Memory write data at " << memory_start_addr_i.read() << endl;

    for (int i = 0; i < memory_len_i.read(); ++i)
    {
        memory_data_[memory_start_addr_i.read() + i] = memory_data_i[i].read();
    }
}

void memory::proccess()
{
    while (true)
    {
        wait();

        // если запись
        if (memory_wr.read())
        {
            memory_is_busy.write(true);
            write();
        }
        // если чтение
        else if (memory_rd.read())
        {
            memory_is_busy.write(true);
            read();
        }
        else
            memory_is_busy.write(false);
    }
}
