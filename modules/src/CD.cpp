#include "../CD.h"
#include <fstream>

void CD::control_process()
{
    init();
    cout << "Initialized" << endl;
    if (!is_init)
        wait();
}

void CD::init()
{
    if (!data_ready || is_init)
        return;
    // ставим значение контролера адресов в буфере в 0
    buffer_address_cd.write(0);
    read_weight_from_file_and_send_it("data/weight.txt");
    read_data_from_file("data/circle.txt");

    if (!load_data)
        return;

    is_init = true;
}

void CD::read_data_from_file(const std::string file_name)
{
    w_or_l_memory.write(false);
    int start_address = buffer_address_cd.read();
    buffer_address_cd.write(start_address + LAYER_FIRST);
    ifstream fin(file_name);
    float var;
    while (!fin.eof())
    {
        for (int i = 0; i < LAYER_FIRST; i++)
        {
            fin >> var;
            buffer_cd[i] = var;
        }
        memory_write(start_address, LAYER_FIRST);
        break;
    }
}

void CD::read_weight_from_file_and_send_it(const std::string file_name)
{
    w_or_l_memory.write(true);
    int start_address = buffer_address_cd.read();
    buffer_address_cd.write(start_address + LAYER_FIRST);
    ifstream fin(file_name);
    float var;
    while (!fin.eof())
    {
        for (int i = 0; i < LAYER_FIRST; i++)
        {
            fin >> var;
            buffer_cd[i] = var;
        }
        memory_write(start_address, LAYER_FIRST);

        start_address = buffer_address_cd.read();
        buffer_address_cd.write(start_address + LAYER_TWO);
        memory_write_off();
        for (int i = 0; i < LAYER_TWO; i++)
        {
            fin >> var;
            buffer_cd[i] = var;
        }
        memory_write(start_address, LAYER_TWO);
        memory_write_off();
        break;
    }
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
