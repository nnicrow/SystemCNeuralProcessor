#pragma once

#include "../config.h"
#include "../interfaces/IMemory.h"

class memory : public sc_module, public IMemory
{
public:
    sc_in<bool> clk;
    
    std::vector<float>& read(int start_addr, int len) override;

    void write(std::vector<float> &data, int start_address) override;
    bool mem_is_busy() override;

    SC_CTOR(memory)
    {
        memory_data_.resize(MEM_SIZE);
        sensitive << clk.pos();
    }

private:
    std::vector<float> memory_data_;
    std::vector<float> return_data_;
};
