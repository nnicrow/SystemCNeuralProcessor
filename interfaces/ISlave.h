#pragma once

#include "systemc.h"
#include "target.h"

class ISlave : public virtual sc_interface
{
public:
    virtual std::vector<float>& read(int start_addr, int len) = 0;
    virtual void write(std::vector<float>& data, int start_address, target current_target, int core_num = 0) = 0;
};
