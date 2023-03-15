#pragma once

#include "../config.h"
#include "../interfaces/ISlave.h"

class memory : public sc_module, public ISlave
{
public:
    sc_in<bool> clk;
    
    void read(int* data, int start_addr, int len) override;

    void write(int* data, int start_addr, int len) override;

    SC_CTOR(memory)
    {
        sensitive << clk.pos();
    }

private:
    // weights excluding first layer from 1..layer_count
    std::vector<std::vector<float>> weights_data_;
    std::vector<std::vector<float>> layers_data_;
    int layer_count_;
};
