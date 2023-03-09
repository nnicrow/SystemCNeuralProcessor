#include "../memory.h"

void memory::mem_layer_read()
{
	
}

void memory::mem_layer_write()
{
	int start_address = data_s_i.read();
	int data_len = data_len_i.read();
	
	layers_data_[current_layer.read()].resize(data_len);
	
	// Записываем данные из буфера CD в вектор весов
	
	for (int i = 0; i < data_len; ++i) {
		layers_data_[current_layer.read()][i] = buffer_cd[start_address + i].read();
		cout << layers_data_[current_layer.read()][i] << endl;
	}
}

void memory::mem_weights_read()
{
	int data_len = weights_data_[current_layer.read()].size();
	
	for (int i = 0; i < data_len; ++i) {
		buffer_memory[i] = weights_data_[current_layer.read()][i];
	}
}

void memory::mem_weights_write()
{
	int start_address = data_s_i.read();
	int data_len = data_len_i.read();
	
	weights_data_[current_layer.read()].resize(data_len);
	
	// Записываем данные из буфера CD в вектор весов
	
	for (int i = 0; i < data_len; ++i) {
		weights_data_[current_layer.read()][i] = buffer_cd[start_address + i].read();
	}
}

void memory::process()
{
	wait();
	weights_data_.resize(layer_count.read());
	layers_data_.resize(layer_count.read());
	
	while (true)
	{
		if (rd_i.read() && !w_or_l_i.read())
			mem_layer_read();

		if (wr_i.read() && !w_or_l_i.read())
			mem_layer_write();

		if (rd_i.read() && w_or_l_i.read())
			mem_weights_read();

		if (wr_i.read() && w_or_l_i.read())
			mem_weights_write();
		wait();
	}
}
