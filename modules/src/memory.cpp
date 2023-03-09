#include "../memory.h"

void memory::mem_layer_read()
{
    if (!rd_i.read() || w_or_l_i.read())
        wait();
    
}

void memory::mem_layer_write()
{
    if (!wr_i.read() || w_or_l_i.read())
        wait();
}

void memory::mem_weights_read()
{
    if (!rd_i.read() || !w_or_l_i.read())
        wait();
}

void memory::mem_weights_write()
{
    if (!wr_i.read() || w_or_l_i.read())
        wait();
}