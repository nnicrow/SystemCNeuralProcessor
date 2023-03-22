#include "../memory.h"

void memory::read()
{
    for (int i = 0; i < memory_len_i.read(); ++i)
    {
        memory_data_o[i].write(memory_data_[memory_start_addr_i.read() + i]);
    }
}

void memory::write()
{
    cout << "Memory write data at " << memory_start_addr_i.read() << endl;
    
    for (int i = 0; i < memory_len_i.read(); ++i)
    {
        cout << "memory " <<  memory_data_i[i].read() << endl;
        memory_data_[memory_start_addr_i.read() + i] = memory_data_i[i].read();
    }
}

void memory::proccess()
{
    while (true)
    {
        // если запись
        if (memory_wr.read())
        {
            memory_is_busy.write(true);
            write();
        }
        // если чтение
        else if (memory_rd.read())
        {
            for (int i = 0; i < memory_data_.size() - 1; ++i)
            {
                cout << memory_data_[i] << endl;    
            }
            
            return;
            memory_is_busy.write(true);
            read();
        }
        else
            memory_is_busy.write(false);

        wait();
    }
}
