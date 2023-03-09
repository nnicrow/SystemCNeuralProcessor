#include "../memory.h"

void memory::mem_layer_read()
{
    cout << "9";
    if (!rd_i.read() || w_or_l_i.read())
        wait();
    cout << "1";
}

void memory::mem_layer_write()
{
    if (!wr_i.read() || w_or_l_i.read())
        wait();
    cout << "2";
}

void memory::mem_weights_read()
{
    if (!rd_i.read() || !w_or_l_i.read())
        wait();
    cout << "3";
}

void memory::mem_weights_write()
{
    if (!wr_i.read() || w_or_l_i.read())
        wait();
    cout << "4";
}
