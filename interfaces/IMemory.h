#pragma once

#include "systemc.h"

class IMemory : public virtual sc_interface
{
public:
    virtual std::vector<float>& read(int start_addr, int len) = 0;
    virtual void write(std::vector<float>& data, int start_address) = 0;
    virtual bool mem_is_busy() = 0;
};
