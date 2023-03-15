#pragma once

#include "systemc.h"

class ISlave : public virtual sc_interface
{
public:
    virtual void read(int* data, int start_addr, int len) = 0;
    virtual int write(std::vector<float> &data) = 0;
};
