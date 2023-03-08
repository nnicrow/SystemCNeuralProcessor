#include "systemc.h"
#include "modules/bus.h"
#include "modules/CD.h"
#include "modules/core.h"
#include "modules/memory.h"

int sc_main(int argc, char* argv[])
{
    CD CD("ControlDevice");
    bus bus("bus");
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

    /*
    // bus
    bus.clk(clk);
    bus.layer_count(layer_count);
    bus.current_layer(current_layer);
    
    bus.wr_o_memory(wr_o_memory);
    bus.rd_o_memory(rd_o_memory);
    bus.data_s_i_memory(data_s_o_memory);
    bus.data_len_i_memory(data_len_i_memory);*/
    
    sc_start(sc_time(40000, SC_NS));
    return 0;
}
