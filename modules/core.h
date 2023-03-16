﻿#pragma once
#include <sysc/kernel/sc_module.h>

#include "../config.h"
#include "../interfaces/IMemory.h"
#include "../interfaces/ICore.h"

enum class core_mode { read, write, count, await };

class core : public sc_module, public ICore
{
public:
    sc_in<bool> clk; // тактовый сигнал
    sc_port<IMemory> bus_inst;

    // функция которая будет получать данные весов и которая будет получать данные нейронов
    void control_process();
    
    bool is_busy(int core_num) override;
    bool core_task(int core_num, std::vector<float>& neurons, std::vector<float>& weight, int start_address) override;

    SC_CTOR(core)
    {
        SC_THREAD(control_process)
        sensitive << clk.pos();
    }
private:
    std::vector<float> neurons;
    std::vector<std::vector<float>> weight;
    bool is_busy_flag;

    float activ_f(float data);
};
