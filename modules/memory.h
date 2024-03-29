﻿#pragma once

#include "../config.h"

class memory : public sc_module
{
public:
    sc_in<bool> clk;
    
    sc_in<int> memory_start_addr_i;
    sc_in<int> memory_len_i;
    sc_in<float> memory_data_i[BUFFER_SIZE];
    sc_in<bool> memory_wr;
    sc_in<bool> memory_rd;
    
    sc_out<float> memory_data_o[BUFFER_SIZE];
    sc_out<bool> memory_is_busy;

    void proccess();
    
    SC_CTOR(memory)
    {
        memory_data_.resize(MEM_SIZE);
        SC_THREAD(proccess)
        sensitive << clk.pos();
    }

private:
    std::vector<float> memory_data_;
    void read();
    void write();
};
