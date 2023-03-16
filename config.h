#pragma once

#include "systemc.h"

#define LAYER_COUNT 3
#define LAYER_S {49, 30, 3}
#define MEM_SIZE 40960
#define ADDRESS_SIZE (20480 / 64)
#define CORE_COUNT 1
#define QUEUE_SIZE (CORE_COUNT + 1)
#define FILE_NAME "data/triangle.txt"
