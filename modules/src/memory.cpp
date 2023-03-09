#include "../memory.h"

void memory::mem_layer_read()
{
    cout << "1" << endl;
}

void memory::mem_layer_write()
{
    cout << "2" << endl;
}

void memory::mem_weights_read()
{
    cout << "3" << endl;
}

void memory::mem_weights_write()
{
    cout << "4" << endl;
}

void memory::process()
{
    while (true)
    {
        cout << "process" << endl;
        if (rd_i.read() && !w_or_l_i.read())
            mem_layer_read();
        
        if (wr_i.read() && !w_or_l_i.read())
            mem_layer_write();
        
        if (rd_i.read() && w_or_l_i.read())
            mem_weights_read();
        
        if (wr_i.read() && w_or_l_i.read())
            mem_weights_write();
        wait(10);
    }
}
