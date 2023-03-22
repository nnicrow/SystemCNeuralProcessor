#pragma once
#include <sysc/kernel/sc_module.h>

#include "../config.h"
#include "../interfaces/ICore.h"

class core : public sc_module, public ICore
{
public:
    sc_in<bool> clk; // тактовый сигнал

    // core
    sc_out<bool> core_is_busy;
    
    // memory
    sc_out<int> bus_memory_start_addr_i;
    sc_out<int> bus_memory_len_i;
    sc_out<float> bus_memory_data_i[BUFFER_SIZE];
    sc_out<bool> bus_memory_wr;
    
    // функция которая будет получать данные весов и которая будет получать данные нейронов
    void control_process();

    bool is_busy(int core_num) override;
    bool core_task(int core_num, std::vector<float>& neurons, std::vector<std::vector<float>>& weight,
                   int start_address, bool is_last = false) override;

    SC_CTOR(core)
    {
        SC_THREAD(control_process)
        sensitive << clk.pos();
    }

private:
    int core_num_;
    std::vector<float> neurons_data_;
    std::vector<std::vector<float>> weight_data_;
    int start_address_;
    bool is_busy_flag_;
    bool is_last_flag_;
    std::vector<float> result_;

    float activ_f(float data);
    std::vector<float> softmax(std::vector<float> t);
    void memory_write(const std::vector<float>& data);
};
