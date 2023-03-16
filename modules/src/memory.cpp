#include "../memory.h"

std::vector<float>& memory::read(int start_addr, int len)
{
	return_data_.resize(len);
	for (int i = 0; i < len; ++i)
	{
		return_data_[i] = memory_data_[start_addr + i];
	}
	return return_data_;
}

void memory::write(std::vector<float> &data, int start_address)
{
	for (int i = 0; i < data.size(); ++i)
	{
		memory_data_[start_address + i] = data[i];
	}
}
