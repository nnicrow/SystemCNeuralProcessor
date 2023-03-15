#pragma once
#include "../interfaces/ISlave.h"

class CD : public sc_module
{
public:
    // global
    sc_in<bool> clk; // Тактовый сигнал
    sc_port<ISlave> bus_inst;
    
    // Конструктор модуля
    SC_CTOR(CD)
    {
        /*SC_THREAD(control_process)*/
        sensitive << clk.pos();
    }
private:
    
};
