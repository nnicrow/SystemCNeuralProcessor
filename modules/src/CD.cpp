#include "../CD.h"

#include <fstream>
#include "../../config.h"

void CD::proccess()
{
    // read data from file
    cout << "Start read data" << endl;

    // weight
    ifstream fin("data/weight.txt");

    while (!fin.eof())
    {
        for (int layer_num = 0; layer_num < layer_count_ - 1; ++layer_num)
        {
            std::vector<float> data;
            int len = layers_[layer_num] * layers_[layer_num + 1];
            data.resize(len);
            for (int i = 0; i < len; ++i)
            {
                fin >> data[i];
            }
            write_to_memory(data, len);
            wait();
        }
        break;
    }
    
    // read neurons
    ifstream fin2("data/circle.txt");
    while (!fin2.eof())
    {
        std::vector<float> data;
        int len = layers_[0];
        data.resize(len);
        for (int i = 0; i < len; ++i)
        {
            fin >> data[i];
        }
        write_to_memory(data, len);
        wait();
        break;
    }
    cout << "End read data" << endl;
    data_read_end_ = true;
}

void CD::write_to_memory(std::vector<float>& data, int len)
{
    address_[address_count_++] = last_memory_busy_address_;
    bus_memory_inst->write(data, last_memory_busy_address_);
    last_memory_busy_address_ += len;
}
