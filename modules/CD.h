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
        address_.resize(MEM_SIZE / 16);
        sensitive << clk.pos();
    }
private:
    std::vector<int> address_;
    int address_count_;
};
