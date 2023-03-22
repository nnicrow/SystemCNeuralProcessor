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

    // memory
    sc_out<int> memory_start_addr_i;
    sc_out<int> memory_len_i;
    sc_out<float> memory_data_i[BUFFER_SIZE];
    sc_out<bool> memory_wr;
    sc_out<bool> memory_rd;
    
    sc_in<float> memory_data_o[BUFFER_SIZE];
    sc_in<bool> memory_is_busy;
    
    /*sc_port<IMemory> memory_inst;*/
    sc_port<ICore, 0, SC_ZERO_OR_MORE_BOUND> core_inst;

    std::vector<float>& read(int start_addr, int len) override;
    void write(std::vector<float>& data, int start_address) override;
    bool mem_is_busy() override;
    bool is_busy(int core_num) override;
    bool core_task(int core_num, std::vector<float>& neurons, std::vector<std::vector<float>>& weight, int start_address, bool is_last = false) override;;
    
    void process();

    SC_CTOR(bus)
    {
        SC_THREAD(process)
        sensitive << clk.pos();
    }

private:
    std::vector<queue> write_queue_;
    std::vector<queue> read_queue_;
    std::vector<float> read_data;
    void memory_write(const queue& queue);
    void memory_read();
};
