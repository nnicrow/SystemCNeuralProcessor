#pragma once

#include "../config.h"
#include "../interfaces/ISlave.h"

class memory : public sc_module, public ISlave
{
public:
    sc_in<bool> clk;
    
    void read(int* data, int start_addr, int len) override;

    void write(std::vector<float> &data, int start_address) override;

    SC_CTOR(memory)
    {
        memory_data_.resize(MEM_SIZE);
        sensitive << clk.pos();
    }

private:
    std::vector<float> memory_data_;
};
