#pragma once

#include "systemc.h"

SC_MODULE(memory)
{
    // weights excluding first layer from 1..layer_count
    std::vector<float, float> weights_data;
    std::vector<float, float> layers_data;
    int layer_count;
    int result;

    sc_in<bool> clk;
    sc_in<bool> wr_i; // сигнал записи данных
    sc_in<bool> rd_i; // сигнал чтения данных

    // кидаем сигнал на чтение, все ядра получают свой отрезок в памяти, который они хотят прочитать, когда они считывают, они загружают его себе.
    // кидаем сигнал на запись данных, все данные
    
    SC_CTOR(memory)
    {
        sensitive << clk.pos();
    }
};
