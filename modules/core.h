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

    // функция которая будет получать данные весов и которая будет получать данные нейронов*/
    void control_process();

    void read(int* data, int start_addr, int len) override;
    
    int write(std::vector<float> &data) override;;

    SC_CTOR(core)
    {
        SC_THREAD(control_process)
        sensitive << clk.pos();
    }
};
