#include "systemc.h"
#include "modules/CD.h"
#include "modules/core.h"
#include "modules/memory.h"

int sc_main(int argc, char* argv[])
{
    CD CD("ControlDevice");
    core core("core");
    memory memory("memory");

    // global parameters
    sc_clock clk("clk_i", sc_time(10, SC_NS));
    sc_signal<int> layer_count;
    sc_signal<int> current_layer;

    // memory
    // out
    sc_signal<bool> wr_o_memory;
    sc_signal<bool> rd_o_memory;
    sc_signal<int> data_s_o_memory;
    sc_signal<int> data_len_o_memory;
    // in
    sc_signal<int> data_addr_s_i_memory;
    sc_signal<int> data_len_i_memory;
    
    // CD
    sc_signal<bool> data_ready;
    sc_signal<bool> load_data;
    sc_signal<bool> result_ready;

    // core
    sc_signal<int> data_s_core;
    sc_signal<int> weight_s_core;
    sc_signal<int> data_count_core;
    sc_signal<int> res_s_core;
    sc_signal<bool> is_work_core;
    sc_signal<bool> is_last_layer_core;
    sc_signal<bool> is_busy_o_core;
    
    // memory
    memory.clk(clk);
    memory.layer_count(layer_count);
    memory.current_layer(current_layer);
    
    memory.wr_i(wr_o_memory);
    memory.rd_i(rd_o_memory);
    memory.data_s_i(data_s_o_memory);
    memory.data_len_i(data_len_o_memory);
    memory.data_addr_s_o(data_addr_s_i_memory);
    memory.data_len_o(data_len_i_memory);

    // Core
    core.clk(clk);
    core.data_s(data_s_core);
    core.weight_s(weight_s_core);
    core.data_count(data_count_core);
    core.res_s(res_s_core);
    core.is_work(is_work_core);
    core.is_last_layer(is_last_layer_core);
    core.is_busy_o(is_busy_o_core);
    
    // CD
    CD.clk(clk);
    CD.layer_count(layer_count);
    CD.current_layer(current_layer);

    CD.data_ready(data_ready);
    CD.load_data(load_data);
    CD.result_ready(result_ready);
    
    CD.wr_o_memory(wr_o_memory);
    CD.rd_o_memory(rd_o_memory);
    CD.data_s_o_memory(data_s_o_memory);
    CD.data_len_o_memory(data_len_o_memory);
    CD.data_addr_s_i_memory(data_addr_s_i_memory);
    CD.data_len_i_memory(data_len_i_memory);
    
    CD.data_s_core(data_s_core);
    CD.weight_s_core(weight_s_core);
    CD.data_count_core(data_count_core);
    CD.res_s_core(res_s_core);
    CD.is_work_core(is_work_core);
    CD.is_last_layer_core(is_last_layer_core);
    CD.is_busy_o_core(is_busy_o_core);
    
    sc_start(sc_time(40000, SC_NS));
    return 0;
}
