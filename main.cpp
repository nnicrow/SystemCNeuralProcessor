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

    // memory
    memory.clk(clk);
    
    // bus
    bus.clk(clk);
    bus.memory_inst(memory);

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
