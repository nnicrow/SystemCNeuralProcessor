#pragma once

#include "systemc.h"

#define LAYER_COUNT 3
#define LAYER_S {49, 33, 3}
#define MEM_SIZE 2048
#define ADDRESS_SIZE (2048 / 64)
#define CORE_COUNT 3
#define QUEUE_SIZE (CORE_COUNT + 1)
