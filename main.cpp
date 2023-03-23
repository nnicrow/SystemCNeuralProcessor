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

    // bus
    sc_signal<int> bus_memory_start_addr_i[CORE_COUNT + 1];
    sc_signal<int> bus_memory_len_i[CORE_COUNT + 1];
    sc_signal<float> bus_memory_data_i[CORE_COUNT + 1][BUFFER_SIZE];
    sc_signal<bool> bus_memory_wr[CORE_COUNT + 1];

    sc_signal<float> bus_memory_data_o[BUFFER_SIZE];
    sc_signal<bool> bus_memory_is_busy;
    sc_signal<bool> bus_memory_rd;

    // memory
    sc_signal<int> memory_start_addr_i;
    sc_signal<int> memory_len_i;
    sc_signal<bool> memory_is_busy;
    sc_signal<float> memory_data_i[BUFFER_SIZE];
    sc_signal<float> memory_data_o[BUFFER_SIZE];
    sc_signal<bool> memory_wr;
    sc_signal<bool> memory_rd;

    // core
    // sc_signal<bool> bus_core_is_busy[CORE_COUNT];
    sc_signal<bool> core_is_busy[CORE_COUNT];
    // sc_signal<bool> bus_core_is_last[CORE_COUNT];
    sc_signal<bool> core_is_last[CORE_COUNT];
    sc_signal<int> core_is_start_address[CORE_COUNT];
    sc_signal<int> core_start_addr_i[CORE_COUNT];
    sc_signal<int> core_len_i[CORE_COUNT];
    sc_signal<float> core_data_i[CORE_COUNT][BUFFER_SIZE];
    sc_signal<bool> core_wr[CORE_COUNT];
    
    // memory
    memory.clk(clk);
    memory.memory_start_addr_i(memory_start_addr_i);
    memory.memory_len_i(memory_len_i);
    memory.memory_wr(memory_wr);
    memory.memory_rd(memory_rd);
    for (int i = 0; i < BUFFER_SIZE; ++i)
    {
        memory.memory_data_i[i](memory_data_i[i]);
        memory.memory_data_o[i](memory_data_o[i]);
    }
    memory.memory_is_busy(memory_is_busy);

    // bus
    bus.clk(clk);

    bus.memory_start_addr_i(memory_start_addr_i);
    bus.memory_len_i(memory_len_i);
    bus.memory_wr(memory_wr);
    bus.memory_rd(memory_rd);
    for (int i = 0; i < BUFFER_SIZE; ++i)
    {
        bus.memory_data_i[i](memory_data_i[i]);
        bus.memory_data_o[i](memory_data_o[i]);
    }
    bus.memory_is_busy(memory_is_busy);
    
    bus.bus_memory_start_addr_i[0](bus_memory_start_addr_i[0]);
    bus.bus_memory_len_i[0](bus_memory_len_i[0]);
    for (int j = 0; j < BUFFER_SIZE; ++j)
    {
        bus.bus_memory_data_i[0][j](bus_memory_data_i[0][j]);
        bus.bus_memory_data_o[j](bus_memory_data_o[j]);
        CD.bus_memory_data_i[j](bus_memory_data_i[0][j]);
        CD.bus_memory_data_o[j](bus_memory_data_o[j]);
    }
    bus.bus_memory_wr[0](bus_memory_wr[0]);
    bus.bus_memory_rd(bus_memory_rd);
    bus.bus_memory_is_busy(bus_memory_is_busy);

    // CD
    CD.clk(clk);
    CD.bus_cores_inst(bus);
    CD.bus_memory_start_addr_i(bus_memory_start_addr_i[0]);
    CD.bus_memory_len_i(bus_memory_len_i[0]);
    CD.bus_memory_wr(bus_memory_wr[0]);
    CD.bus_memory_rd(bus_memory_rd);
    CD.bus_memory_is_busy(bus_memory_is_busy);
    
    for (int i = 0; i < CORE_COUNT; ++i)
    {
        cores[i].clk(clk);
        cores[i].bus_memory_start_addr_i(bus_memory_start_addr_i[i + 1]);
        cores[i].bus_memory_len_i(bus_memory_len_i[i + 1]);
        cores[i].bus_memory_wr(bus_memory_wr[i + 1]);
        
        cores[i].core_is_busy(core_is_busy[i]);
        CD.cors_is_busy[i](core_is_busy[i]);
        cores[i].core_is_last(core_is_last[i]);
        CD.bus_core_is_last[i](core_is_last[i]);
        cores[i].core_is_start_address(core_is_start_address[i]);
        CD.core_is_start_address[i](core_is_start_address[i]);

        cores[i].core_start_addr_i(core_start_addr_i[i]);
        cores[i].core_len_i(core_len_i[i]);
        cores[i].core_wr(core_wr[i]);
        CD.core_start_addr_i[i](core_start_addr_i[i]);
        CD.core_len_i[i](core_len_i[i]);
        CD.core_wr[i](core_wr[i]);
        
        bus.bus_memory_start_addr_i[i + 1](bus_memory_start_addr_i[i + 1]);
        bus.bus_memory_len_i[i + 1](bus_memory_len_i[i + 1]);
        for (int j = 0; j < BUFFER_SIZE; ++j)
        {
            cores[i].core_data_i[j](core_data_i[i][j]);
            cores[i].bus_memory_data_i[j](bus_memory_data_i[i + 1][j]);
            bus.bus_memory_data_i[i + 1][j](bus_memory_data_i[i + 1][j]);
            CD.core_data_i[i][j](core_data_i[i][j]);
        }
        bus.bus_memory_wr[i + 1](bus_memory_wr[i + 1]);
        bus.core_inst(cores[i]);
    }

    sc_start(sc_time(20000, SC_NS));
    return 0;
}
