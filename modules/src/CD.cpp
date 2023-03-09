#include "../CD.h"
#include <fstream>

void CD::control_process()
{
    layer_count.initialize(LAYER_COUNT);
    current_layer.initialize(0);
    // инициализация, достает данные из файла и отправляет их в память, запускается когда data_ready
    while (true)
    {
        if (!data_ready) wait();
        else break;
    }
    cout << "Initialized start" << endl;
    buffer_address_cd.write(0);
    w_or_l.initialize(true);

    // старт чтения весов
    int start_address = buffer_address_cd.read();
    buffer_address_cd.write(start_address + LAYER_FIRST);
    ifstream fin("data/weight.txt");
    float var;
    while (!fin.eof())
    {
        for (int i = 0; i < LAYER_FIRST; ++i)
        {
            fin >> var;
            buffer_cd[i].write(var);
        }
        memory_write(start_address, LAYER_FIRST);
        wait();
        start_address = buffer_address_cd.read();
        buffer_address_cd.write(start_address + LAYER_TWO);

        memory_write_off();
        wait();

        for (int i = 0; i < LAYER_TWO; ++i)
        {
            fin >> var;
            buffer_cd[start_address + i].write(var);
        }
        memory_write(start_address, LAYER_TWO);
        wait();
        break;
    }
    memory_write_off();
    wait();
    w_or_l.write(false);
    start_address = buffer_address_cd.read();
    buffer_address_cd.write(start_address + LAYER_FIRST);
    ifstream fin2("data/circle.txt");
    while (!fin2.eof())
    {
        for (int i = 0; i < LAYER_FIRST; ++i)
        {
            fin2 >> var;
            buffer_cd[start_address + i].write(var);
        }
        memory_write(start_address, LAYER_FIRST);
        wait();
        break;
    }

    memory_write_off();
    wait();
    memory_read();
    wait();
    memory_read_off();
}

void CD::out()
{
    // TODO: write data to output stream
    // вы помещаем в data_s_o_memory начальный адрес нашей *****
    // а в data_len_o_memory длину *****
}

void CD::memory_write(int data_s, int data_len)
{
    rd_o_memory.write(false);
    data_s_o_memory.write(data_s);
    data_len_o_memory.write(data_len);
    wr_o_memory.write(true);
}

void CD::memory_write_off()
{
    wr_o_memory.write(false);
}

void CD::memory_read()
{
    wr_o_memory.write(false);
    rd_o_memory.write(true);
}

void CD::memory_read_off()
{
    rd_o_memory.write(false);
}
