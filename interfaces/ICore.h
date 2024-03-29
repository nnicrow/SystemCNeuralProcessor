﻿#pragma once

#include "systemc.h"

class ICore : public virtual sc_interface
{
public:
    virtual bool core_task(int core_num, std::vector<std::vector<float>>& weight) = 0;
};
