#pragma once
#include <sysc/kernel/sc_module.h>

#include "../config.h"
#include "../interfaces/ISlave.h"

enum class core_mode { read, write, count, await };

class core : public sc_module, public ISlave
{
public:
    sc_in<bool> clk; // тактовый сигнал
    sc_port<ISlave> bus_inst;
    
    /*sc_buffer<float> buffer_cd[BOFFER_SIZE];

    sc_in<int> data_s; // вход данных
    sc_in<bool> w_or_l; // вход весов
    sc_in<int> data_count; // размер данных
    sc_in<int> res_s; // куда выгружать
    sc_in<bool> is_work; // в данный момент в работе
    sc_in<bool> is_last_layer; // флаг последнего слоя, true только у одного
    sc_out<bool> is_busy_o; // занятость ядра

    core_mode write_or_read;

    // функция которая будет получать данные весов и которая будет получать данные нейронов*/
    void control_process();

    void read() override;;
    
    void write() override;;

    SC_CTOR(core)
    {
        SC_THREAD(control_process)
        sensitive << clk.pos();
    }
};
