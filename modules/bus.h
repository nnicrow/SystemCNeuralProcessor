#pragma once

#include "../interfaces/ISlave.h"
#include "../config.h"

class bus : public sc_module, public ISlave
{
public:
    sc_in<bool> clk;
    sc_port<ISlave, 0, SC_ZERO_OR_MORE_BOUND> slaves_inst;
    
    void read(int* data, int start_addr, int len) override;
    int write(std::vector<float> &data, int len) override;

    SC_CTOR(bus)
    {
        sensitive << clk.pos();
    }
};
