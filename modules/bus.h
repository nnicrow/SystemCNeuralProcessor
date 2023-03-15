#pragma once

#include "../config.h"

SC_MODULE(bus)
{
    sc_in<bool> clk; // тактовый сигнал
    
    SC_CTOR(bus)
    {
        
        sensitive << clk.pos();
    }
};
