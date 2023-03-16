#pragma once

#include "../interfaces/ISlave.h"
#include "../config.h"

class queue
{
public:
    std::vector<float> data_;
    int start_address_;

    queue(): start_address_(0)
    {
    }

    queue(const std::vector<float>& data, int start_address)
    {
        data_ = data;
        start_address_ = start_address;
    }
};


class bus : public sc_module, public ISlave
{
public:
    sc_in<bool> clk;
    sc_port<ISlave, 0, SC_ZERO_OR_MORE_BOUND> slaves_inst;

    std::vector<float>& read(int start_addr, int len) override;
    void write(std::vector<float>& data, int start_address) override;

    void write_process();

    SC_CTOR(bus)
    {
        SC_THREAD(write_process)
        queue_.resize(QUEUE_SIZE);
        sensitive << clk.pos();
    }

private:
    std::vector<queue> queue_;
};
