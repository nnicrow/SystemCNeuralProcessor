#pragma once
#include "../interfaces/ISlave.h"
#include "../config.h"

class CD : public sc_module
{
public:
    // global
    sc_in<bool> clk; // Тактовый сигнал
    sc_port<ISlave> bus_inst;

    void read_data();

    // Конструктор модуля
    SC_CTOR(CD)
    {
        SC_THREAD(read_data)
        address_count_ = 0;
        address_.resize(ADDRESS_SIZE);
        sensitive << clk.pos();
    }

private:
    /* ГОВНО КОД ДЕНИСА */

    std::vector<int> address_;
    int address_count_;
    int last_memory_busy_address_;
    const int layer_count_ = LAYER_COUNT; // колличество слоев
};