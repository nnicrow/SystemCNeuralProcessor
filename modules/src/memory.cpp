#include "../memory.h"

void memory::read(int* data, int start_addr, int len)
{
	
}

void memory::write(std::vector<float> &data, int start_address)
{
	for (int i = 0; i < data.size(); ++i)
	{
		memory_data_[start_address + i] = data[i];
	}
}
