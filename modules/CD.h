#pragma once
#include "../interfaces/IMemory.h"
#include "../interfaces/ICore.h"
#include "../config.h"

class CD : public sc_module
{
public:
    // global
    sc_in<bool> clk; // Тактовый сигнал
    sc_port<IMemory> bus_memory_inst;
    sc_port<ICore, 0, SC_ZERO_OR_MORE_BOUND> bus_cores_inst;

    void proccess();

    // Конструктор модуля
    SC_CTOR(CD)
    {
        SC_THREAD(proccess)
        address_count_ = 0;
        address_.resize(ADDRESS_SIZE);
        sensitive << clk.pos();
    }

private:
    bool data_read_end_;
    bool data_result_ready_;
    std::vector<int> address_;
    int address_count_;
    int last_memory_busy_address_;
    const int layer_count_ = LAYER_COUNT; // колличество слоев
    const std::vector<int> layers_ = LAYER_S;
    
    void write_to_memory(std::vector<float>& data, int len);
};
