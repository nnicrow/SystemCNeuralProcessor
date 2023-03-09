#pragma once

#include "CD.h"
#include "systemc.h"

SC_MODULE(memory)
{
    // входные сигналы
    sc_in<bool> clk;
    sc_in<int> layer_count;
    sc_in<int> current_layer; // переменный параметр, указывает с каким слоем мы сейчас работаем
    sc_in<float> buffer_cd[BOFFER_SIZE];
    sc_out<float> buffer_memory[BOFFER_SIZE];
    sc_in<int> buffer_address_cd;
    sc_out<int> buffer_address_memory;
    sc_out<bool> load_data;
    
    sc_in<bool> wr_i; // сигнал записи данных
    sc_in<bool> rd_i; // сигнал чтения данных
    sc_in<bool> w_or_l_i; // истина, если веса. ложь, если слои
    sc_in<int> data_s_i; // началльный адрес данных слоя
    sc_in<int> data_len_i; // ширина данных

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
    // запись весов в weights_data_ под индексом номера слоя + 1
    void mem_weights_write();

    void process();

    // если current_layer = 0, то инициализация данных, загрузка
    // layer_count и mem_weights_write должны работать только в данном случае

    SC_CTOR(memory)
    {        
        SC_THREAD(process)
        sensitive << clk.pos();
    }

private:
    // weights excluding first layer from 1..layer_count
    std::vector<std::vector<float>> weights_data_;
    std::vector<std::vector<float>> layers_data_;
    int layer_count_;
};
