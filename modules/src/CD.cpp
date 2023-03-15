#include "../CD.h"

#include <fstream>
#include "../../config.h"

void CD::read_data()
{
    ifstream fin("data/weight.txt");
    float var;
    while (!fin.eof())
    {
        std::vector<float> data;
        data.resize(LAYER_FIRST);
        for (int i = 0; i < LAYER_FIRST; ++i)
        {
            fin >> var;
            data[i] = var;
        }
        address_[address_count_++] = last_memory_busy_address_;
        bus_inst->write(data, last_memory_busy_address_);
        last_memory_busy_address_ += LAYER_FIRST;
        wait();
        
        data.resize(LAYER_TWO);
        for (int i = 0; i < LAYER_TWO; ++i)
        {
            fin >> var;
            data[i] = var;
        }
        address_[address_count_++] = last_memory_busy_address_;
        bus_inst->write(data, last_memory_busy_address_);
        last_memory_busy_address_ += LAYER_TWO;
        wait();
    }
}
