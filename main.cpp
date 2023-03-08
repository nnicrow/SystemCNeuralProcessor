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
    
    cout << "Hello World!";

    sc_clock clk("clk_i", sc_time(10, SC_NS));
    
    //bus.clk_i(clk);
    
    sc_start(sc_time(40000, SC_NS));
    return 0;
}