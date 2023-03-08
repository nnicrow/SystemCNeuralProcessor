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


void CD::init()
{
    wr_o_memory.write(true);
    read_weight_from_file_and_send_it("data/weight.txt");
    rd_o_memory = false;
    data_s_o_memory = 0;
    data_len_o_memory = layer_count.read();
    load_data = true;
}

void CD::read_data_from_file(const std::string file_name)
{
    ifstream fin(file_name);
    while (!fin.eof()) {
        /*for (int i(0); i < 30; i++)
            for (int j(0); j < 49; j++)
            {
                fin >> mem[i][j];
            }
        for (int i(0); i < 3; i++)
            for (int j(0); j < 30; j++)
            {
                fin >> mem[i + 30][j];
            }*/
    }
}

void CD::read_weight_from_file_and_send_it(const std::string file_name)
{
    ifstream fin(file_name);
    while (!fin.eof()) {
        for (int i = 0; i < LAYER_TWO; i++) {
            for (int j = 0; j < LAYER_FIRST; j++) {
                fin >> buffer[0][i][j]; // Read the weights from the file and store them in buffer[0]
            }
        }
        for (int i = 0; i < LAYER_LAST; i++) {
            for (int j = 0; j < LAYER_TWO; j++) {
                fin >> buffer[1][i][j]; // Read the weights from the file and store them in buffer[1]
            }
        }
    }

    // Send the weights stored in buffer to the core
    for (int i = 0; i < LAYER_COUNT - 1; i++) {
        for (int j = 0; j < LAYER_LAST; j++) {
            for (int k = 0; k < LAYER_FIRST; k++) {
                out(buffer[i][j][k]); // Send the weights in buffer[i][j][k] to the core
            }
        }
    }
}


void CD::out()
{
    // TODO: write data to output stream
    // вы помещаем в data_s_o_memory начальный адрес нашей *****
    // а в data_len_o_memory длину *****
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