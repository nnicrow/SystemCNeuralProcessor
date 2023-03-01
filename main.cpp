#include "systemc.h"

int sc_main(int argc, char* argv[])
{
    //bus bus("Bus");
    cout << "Hello World!";

    sc_clock clk("clk_i", sc_time(10, SC_NS));
    
    //bus.clk_i(clk);
    
    sc_start(sc_time(40000, SC_NS));
    return 0;
}