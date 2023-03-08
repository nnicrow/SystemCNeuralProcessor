#pragma once

#include "systemc.h"

sc_buffer<float> buffer[1024];
sc_signal<int> buffer_address;

SC_MODULE(memory)
{
    // входные сигналы
    sc_in<bool> clk;
    sc_in<int> layer_count;
    sc_in<int> current_layer; // переменный параметр, указывает с каким слоем мы сейчас работаем

    sc_in<bool> wr_i; // сигнал записи данных
    sc_in<bool> rd_i; // сигнал чтения данных
    sc_in<int> data_s_i; // началльный адрес данных слоя
    sc_in<int> data_len_i; // ширина данных
    sc_in<bool> w_or_l_i; // ширина данных

    // выходные сигналы
    sc_out<int> data_addr_s_o; // началльный адрес данных слоя
    sc_out<int> data_len_o; // длина

    SC_HAS_PROCESS(memory);

    // чтение данных из layers_data_ под индексом номера слоя
    void mem_layer_read();
    // запись данных в layers_data_ под индексом номера слоя
    void mem_layer_write();
    // чтение весов в weights_data_ под индексом номера слоя + 1
    void mem_weights_read();

    // инициализация. На данном этапе загружаются все веса, входной слой и колличество слоев layer_count
    void process();

    // запись весов в weights_data_ под индексом номера слоя + 1
    void mem_weights_write();

    // если current_layer = 0, то инициализация данных, загрузка
    // layer_count и mem_weights_write должны работать только в данном случае

    SC_CTOR(memory)
    {
        sensitive << clk.pos();
        SC_METHOD(mem_layer_read)
        SC_METHOD(mem_layer_write)
        SC_METHOD(mem_weights_read)
        SC_METHOD(process)
    }

private:
    // weights excluding first layer from 1..layer_count
    std::vector<std::vector<float>> weights_data_;
    std::vector<std::vector<float>> layers_data_;
    int layer_count_;
    int result_;
};
