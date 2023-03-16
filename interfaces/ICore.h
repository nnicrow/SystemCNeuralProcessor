#pragma once

#include "systemc.h"

class ICore : public virtual sc_interface
{
public:
    virtual bool is_busy(int core_num) = 0;
    virtual void core_task(int core_num, std::vector<float>& neurons, std::vector<float>& weight, int start_address) = 0;
};
