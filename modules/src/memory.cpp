#include "../memory.h"

void memory::mem_layer_read()
{
    if (rd_i.read()) {
        int layer = current_layer.read();
        int data_s = data_s_i.read();
        int data_len = data_len_i.read();

        data_addr_s_o.write(data_s);
        data_len_o.write(data_len);

        for (int i = 0; i < data_len; ++i) {
            layers_data_[layer][i] = layers_data_[layer][data_s + i];
        }
    }
}

void memory::mem_layer_write()
{
    if (wr_i.read()) {
        int layer = current_layer.read();
        int data_s = data_s_i.read();
        int data_len = data_len_i.read();

        for (int i = 0; i < data_len; ++i) {
            layers_data_[layer][data_s + i] = layers_data_[layer][i];
        }
    }
}

void memory::mem_weights_read()
{
    if (rd_i.read()) {
        int layer = current_layer.read();

        data_addr_s_o.write(layer + 1);
        data_len_o.write(weights_data_[layer].size());

        for (int i = 0; i < weights_data_[layer].size(); ++i) {
            layers_data_[layer + 1][i] = weights_data_[layer][i];
        }
    }
}

void memory::init()
{
    if (current_layer.read() == 0) {
        layer_count_ = layer_count.read();

        // Load weights
        weights_data_.resize(layer_count_ - 1);
        for (int i = 0; i < layer_count_ - 1; ++i) {
            weights_data_[i].resize(layers_data_[i].size());
        }

        // Load input layer
        layers_data_[0].resize(data_len_i.read());

        // Initialize result
        result_ = 0;

        // Write weights
        mem_weights_write();
    }
}

void memory::mem_weights_write()
{
    if (wr_i.read() && current_layer.read() != 0) {
        int layer = current_layer.read() - 1;

        for (int i = 0; i < weights_data_[layer].size(); ++i) {
            weights_data_[layer][i] = layers_data_[layer + 1][i];
        }
    }
}
