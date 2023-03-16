#pragma once

#include "systemc.h"

class ICore : public virtual sc_interface
{
public:
    virtual bool is_busy(int core_num) = 0;
    virtual bool core_task(int core_num, std::vector<float>& neurons, std::vector<float>& weight, int start_address, bool is_last = false) = 0;
};
