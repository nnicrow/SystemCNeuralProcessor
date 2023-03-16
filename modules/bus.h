#pragma once

#include "../interfaces/ISlave.h"
#include "../config.h"

class queue
{
public:
    std::vector<float> data_;
    int start_address_;

    queue();

    queue(const std::vector<float>& data, int start_address);
};


class bus : public sc_module, public ISlave
{
public:
    sc_in<bool> clk;
    sc_port<ISlave, 0, SC_ZERO_OR_MORE_BOUND> slaves_inst;

    std::vector<float>& read(int start_addr, int len) override;
    void write(std::vector<float>& data, int start_address, target current_target, int core_num = 0) override;

    void bus_write_process();

    SC_CTOR(bus)
    {
        SC_THREAD(bus_write_process)
        sensitive << clk.pos();
    }

private:
    std::vector<queue> write_queue_;
};
