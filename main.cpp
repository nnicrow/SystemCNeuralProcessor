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

    sc_signal<int> layer_count;
    sc_signal<int> current_layer;

    // memory
    sc_signal<bool> wr_o_memory;
    sc_signal<bool> rd_o_memory;
    sc_signal<int> data_s_o_memory;
    sc_signal<int> data_len_o_memory;
    
    sc_signal<int> data_addr_s_i_memory;
    sc_signal<int> data_len_i_memory;

    sc_clock clk("clk_i", sc_time(10, SC_NS));
    memory.clk(clk);
    memory.layer_count(layer_count);

    sc_start(sc_time(40000, SC_NS));
    return 0;
}
