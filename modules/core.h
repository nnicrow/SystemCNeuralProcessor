#pragma once
#include <sysc/kernel/sc_module.h>

#include "systemc.h"

enum class core_mode { read, write, count, await };

SC_MODULE(core)
{
    sc_in<bool> clk; // тактовый сигнал
    
    sc_in<int> data_s; // вход данных
    sc_in<int> weight_s; // вход весов
    sc_in<int> data_count; // размер данных
    sc_in<int> res_s; // куда выгружать
    sc_in<bool> is_work; // в данный момент в работе
    sc_in<bool> is_last_layer; // флаг последнего слоя, true только у одного
    sc_out<bool> is_busy_o; // занятость ядра

    core_mode write_or_read;

    // функция которая будет получать данные весов и которая будет получать данные нейронов
    
    SC_CTOR(core)
    {
    }
};
