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
        /*SC_THREAD(control_process)*/
        address_count_ = 0;
        address_.resize(ADDRESS_SIZE);
        sensitive << clk.pos();
    }
private:
    std::vector<int> address_;
    int address_count_;
    int last_address_;
    const int layer_count_ = LAYER_COUNT;
};
