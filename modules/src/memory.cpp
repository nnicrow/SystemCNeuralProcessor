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
	cout << "Memory write data at " << start_address << endl;
	for (int i = 0; i < data.size(); ++i)
	{
		memory_data_[start_address + i] = data[i];
	}
}

bool memory::mem_is_busy()
{
	return false;
}
