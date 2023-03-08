#pragma once

#include "systemc.h"

SC_MODULE(memory)
{
    // входные сигналы
    sc_in<bool> clk;
    sc_in<int> layer_count; // задает колличество слоев при инициализации
    sc_in<bool> wr_i; // сигнал записи данных
    sc_in<bool> rd_i; // сигнал чтения данных
    sc_in<int> current_layer; // переменный параметр, указывает с каким слоем мы сейчас работаем

    // выходные сигналы
    sc_out<int> layer_addr_s; // началльный адрес данных слоя
    sc_out<int> layer_addr_e; // конечный адрес данных слоя
    sc_out<int> weights_addr_s; // началльный адрес весов
    sc_out<int> weights_addr_e; // конечный адрес весов 

    void mem_layer_read();
    void mem_layer_write();
    void mem_weights_read();
    void mem_weights_write();

    // кидаем сигнал на чтение, все ядра получают свой отрезок в памяти, который они хотят прочитать, когда они считывают, они загружают его себе.
    // кидаем сигнал на запись данных, все данные

    SC_CTOR(memory)
    {
        sensitive << clk.pos();
    }

private:
    // weights excluding first layer from 1..layer_count
    std::vector<std::vector<float>> weights_data_;
    std::vector<std::vector<float>> layers_data_;
    int layer_count_;
    int result_;
};
