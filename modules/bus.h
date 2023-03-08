#pragma once
#include <sysc/kernel/sc_module.h>

#include "systemc.h"

SC_MODULE(bus)
{
    /*sc_in<bool> clk;
    sc_in<int> layer_count;
    sc_in<int> current_layer; // переменный параметр, указывает с каким слоем мы сейчас работаем

    // memory
    sc_out<bool> wr_o_memory; // сигнал записи данных
    sc_out<bool> rd_o_memory; // сигнал чтения данных
    sc_in<int> data_s_i_memory; // началльный адрес данных слоя
    sc_in<int> data_len_i_memory; // ширина данных*/

    //
    void bus_process();
    
    SC_CTOR(bus)
    {
        
    }
};
