#pragma once

#include "../interfaces/IMemory.h"
#include "../interfaces/ICore.h"
#include "../config.h"

class queue
{
public:
    std::vector<float> data_;
    int start_address_;

    queue();

    queue(const std::vector<float>& data, int start_address);
};


class bus : public sc_module, public IMemory, public ICore 
{
public:
    sc_in<bool> clk;
    sc_port<IMemory> memory_inst;
    sc_port<ICore, 0, SC_ZERO_OR_MORE_BOUND> core_inst;

    std::vector<float>& read(int start_addr, int len) override;
    void write(std::vector<float>& data, int start_address) override;
    bool mem_is_busy() override;
    bool is_busy(int core_num) override;
    bool core_task(int core_num, std::vector<float>& neurons, std::vector<float>& weight, int start_address, bool is_last = false) override;;

    void bus_write_process();

    SC_CTOR(bus)
    {
        SC_THREAD(bus_write_process)
        sensitive << clk.pos();
    }

private:
    std::vector<queue> write_queue_;
};
