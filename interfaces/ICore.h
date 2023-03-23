#pragma once

#include "systemc.h"

class ICore : public virtual sc_interface
{
public:
    virtual bool core_task(int core_num, std::vector<float>& neurons, std::vector<std::vector<float>>& weight,
                           int start_address) = 0;
};
