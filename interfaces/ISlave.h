#pragma once

#include "systemc.h"

class ISlave : public virtual sc_interface
{
public:
    virtual void read() = 0;
    virtual void write() = 0;
};
