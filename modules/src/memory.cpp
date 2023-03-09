#include "../memory.h"

void memory::mem_layer_read()
{
}

void memory::mem_layer_write()
{
}

void memory::mem_weights_read()
{

}

void memory::mem_weights_write()
{

	int start_address = data_s_i.read();
	int data_len = data_len_i.read();

	// Выбираем вектор весов для текущего слоя (layer)
	std::vector<float>& weights = weights_data_.at(current_layer.read() );

	// Записываем данные из буфера CD в вектор весов
	for (int i = 0; i < data_len; i++) {
		weights[start_address + i] = buffer_cd[i];
	}

}

void memory::process()
{
	weights_data_.resize(layer_count.read());
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
