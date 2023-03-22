#include "systemc.h"
#include "modules/CD.h"
#include "modules/core.h"
#include "modules/memory.h"
#include "modules/bus.h"
#include "config.h"

int sc_main(int argc, char* argv[])
{
    CD CD("ControlDevice");
    memory memory("memory");
    sc_vector<core> cores("core", CORE_COUNT);
    bus bus("bus");
    
    // global parameters
    sc_clock clk("clk_i", sc_time(10, SC_NS));

    // memory
    sc_signal<int> memory_start_addr_i;
    sc_signal<int> memory_len_i;
    sc_signal<bool> memory_is_busy;
    sc_signal<float> memory_data_i[BUFFER_SIZE];
    sc_signal<float> memory_data_o[BUFFER_SIZE];
    sc_signal<bool> memory_wr;
    sc_signal<bool> memory_rd;
    
    // memory
    memory.clk(clk);
    memory.memory_start_addr_i(memory_start_addr_i);
    memory.memory_len_i(memory_len_i);
    memory.memory_wr(memory_wr);
    memory.memory_rd(memory_rd);
    for (int i = 0; i < BUFFER_SIZE ; ++i)
    {
        memory.memory_data_i[i](memory_data_i[i]);
        memory.memory_data_o[i](memory_data_o[i]);
    }
    memory.memory_is_busy(memory_is_busy);
    
    // bus
    bus.clk(clk);
    /*bus.memory_inst(memory);*/
    bus.memory_start_addr_i(memory_start_addr_i);
    bus.memory_len_i(memory_len_i);
    bus.memory_wr(memory_wr);
    bus.memory_rd(memory_rd);
    for (int i = 0; i < BUFFER_SIZE ; ++i)
    {
        bus.memory_data_i[i](memory_data_i[i]);
        bus.memory_data_o[i](memory_data_o[i]);
    }
    bus.memory_is_busy(memory_is_busy);

    // CD
    CD.clk(clk);
    CD.bus_memory_inst(bus);
    CD.bus_cores_inst(bus);
    
    for (int i = 0; i < CORE_COUNT; ++i)
    {
        cores[i].clk(clk);
        cores[i].bus_inst(bus);
        bus.core_inst(cores[i]);
    }
    
    sc_start(sc_time(4000, SC_NS));
    return 0;
}
