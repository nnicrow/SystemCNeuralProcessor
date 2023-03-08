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

    // CD
    sc_signal<bool> program_start; // сигнал готовности входных данных, начало работы
    sc_signal<bool> progrma_end; // сигнал готовности выходных данных, конец работы, вывод результата

    // memory
    
    // cores

    // bus
    // после инициализзации кидаем сигнал program_start, в конце кидаем сигнал progrma_end
    
    sc_signal<bool> CD_IOC_data_ready;
    
    
    
    sc_clock clk("clk_i", sc_time(10, SC_NS));
    CD.clk(clk);

    
    //bus.clk_i(clk);
    
    sc_start(sc_time(40000, SC_NS));
    return 0;
}