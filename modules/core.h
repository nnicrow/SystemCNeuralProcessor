#pragma once
#include <sysc/kernel/sc_module.h>

#include "../interfaces/IMemory.h"
#include "../interfaces/ICore.h"

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
    int core_num_;
    std::vector<float> neurons_data_;
    std::vector<float> weight_data_;
    bool is_busy_flag_;

    float activ_f(float data);
};
