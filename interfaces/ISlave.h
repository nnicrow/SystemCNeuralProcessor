#pragma once

#include "systemc.h"

class ISlave : public virtual sc_interface
{
public:
    virtual void read(int* data, int start_addr, int start_address) = 0;
    virtual void write(std::vector<float> &data, int start_address) = 0;
};
