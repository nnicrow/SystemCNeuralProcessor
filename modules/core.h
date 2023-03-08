#pragma once
#include <sysc/kernel/sc_module.h>

#include "systemc.h"

enum class core_mode { read, write, count, await };

SC_MODULE(core)
{
    sc_in<bool> clk;
    sc_in<int> data_s;
    sc_in<int> weight_s;
    sc_in<int> data_count;
    sc_in<int> res_s;
    sc_in<bool> is_work;
    sc_in<bool> is_last_layer;
    sc_out<bool> is_busy_o;

    core_mode write_or_read;

    SC_CTOR(core)
    {
    }
};
