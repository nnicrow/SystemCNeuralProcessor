#pragma once

#include "../interfaces/ICore.h"
#include "../config.h"

class CD : public sc_module
{
public:
    // global
    sc_in<bool> clk; // Тактовый сигнал

    sc_out<int> bus_memory_start_addr_i;
    sc_out<int> bus_memory_len_i;
    sc_out<float> bus_memory_data_i[BUFFER_SIZE];
    sc_out<bool> bus_memory_wr;
    sc_out<bool> bus_memory_rd;

    sc_in<float> bus_memory_data_o[BUFFER_SIZE];
    sc_in<bool> bus_memory_is_busy;

    // core
    sc_in<bool> cors_is_busy[CORE_COUNT];
    
    sc_port<ICore, 0, SC_ZERO_OR_MORE_BOUND> bus_cores_inst;
    
    void proccess();

    // Конструктор модуля
    SC_CTOR(CD)
    {
        SC_THREAD(proccess)
        address_count_ = 0;
        sensitive << clk.pos();
    }

private:
    std::vector<int> address_;
    int address_count_;
    int last_memory_busy_address_;
    const int layer_count_ = LAYER_COUNT; // колличество слоев
    const std::vector<int> layers_ = LAYER_S;
    
    void end_write_to_memory(int len);
    void memory_address_selection(int len);
    void out_result(std::vector<float>& data);
    void memory_write(const std::vector<float>& data);
    std::vector<float> memory_read(int start_address, int len);
};
