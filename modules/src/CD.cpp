#include "../CD.h"
#include "../memory.h"
#include <fstream>
#include <memory.h>
void CD::control_process()
{
    while (true) {
        if (data_ready && !load_data && !result_ready) {
            init();
        }
        wait();
    }
}

void CD::read_data_from_file()
{
    ifstream fin("data/weight.txt");
    while (!fin.eof()) {
        for (int i(0); i < 30; i++)
            for (int j(0); j < 49; j++)
            {
                fin >> mem[i][j];
            }
        for (int i(0); i < 3; i++)
            for (int j(0); j < 30; j++)
            {
                fin >> mem[i + 30][j];
            }
    }
}

void CD::init()
{
    read_data_from_file();
    wr_o_memory = true;
    rd_o_memory = false;
    data_s_o_memory = 0;
    data_len_o_memory = layer_count.read();
    load_data = true;
}

void CD::out()
{
    // TODO: write data to output stream
}

void CD::memory_write()
{
    while (true) {
        wait();
        if (wr_o_memory) {
            for (int i = 0; i < data_len_o_memory.read(); i++) {
                memory[data_s_o_memory.read() + i] = data_out[i];
            }
            wr_o_memory = false;
        }
    }
}

void CD::memory_read()
{
    while (true) {
        wait();
        if (rd_o_memory) {
            for (int i = 0; i < data_len_i_memory.read(); i++) {
                data_in[i] = memory[data_addr_s_i_memory.read() + i];
            }
            rd_o_memory = false;
        }
    }
}