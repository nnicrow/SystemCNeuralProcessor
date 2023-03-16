#pragma once

#include "systemc.h"

#define LAYER_COUNT 3
#define LAYER_S {49, 30, 3}
#define MEM_SIZE 4096
#define ADDRESS_SIZE (2048 / 64)
#define CORE_COUNT 3
#define QUEUE_SIZE (CORE_COUNT + 1)
#define RESULT_ENUM enum result_enum { circle, square, triangle};
