﻿#include "../core.h"

void core::control_process()
{
    while (true)
    {
        while (!is_busy_flag_)
        {
            wait();
        }
        cout << "core " << core_num_ << " start count" << endl;

        if (is_last_flag_)
        {
            result_ = softmax(neurons_data_);
            
            int num_packets = result_.size() / 16;
            for (int i = 0; i < num_packets; ++i)
            {
                int start_index = i * BUFFER_SIZE;
                int end_index = std::min(start_index + BUFFER_SIZE, (int)result_.size());
                std::vector<float> packet_data(result_.begin() + start_index, result_.begin() + end_index);
                memory_write(packet_data, i, start_index);
                wait();
            }
            is_busy_flag_ = false;
            return;
        }
    
        // цикл по задачам
        for (int task_num = 0; task_num < weight_data_.size(); ++task_num)
        {
            float res = 0;
            for (int neuron = 0; neuron < weight_data_[task_num].size(); ++neuron)
            {
                res += weight_data_[task_num][neuron] * neurons_data_[neuron];
            }
            result_[task_num] = activ_f(res);
        }

        int num_packets = result_.size() / 16;
        for (int i = 0; i < num_packets; ++i)
        {
            int start_index = i * BUFFER_SIZE;
            int end_index = std::min(start_index + BUFFER_SIZE, (int)result_.size());
            std::vector<float> packet_data(result_.begin() + start_index, result_.begin() + end_index);
            memory_write(packet_data, i, start_index);
            wait();
        }
        is_busy_flag_ = false;
        wait();
    }
}

void core::memory_write(std::vector<float>& packet_data, int i, int start_index)
{
    bus_memory_start_addr_i.write(i * packet_data.size() + start_index);
    bus_memory_len_i.write(packet_data.size());
    for (int k = 0; k < packet_data.size(); ++k)
    {
        bus_memory_data_i->write(packet_data[k]);
    }
}

bool core::is_busy(int core_num)
{
    return is_busy_flag_;
}

bool core::core_task(int core_num, std::vector<float>& neurons, std::vector<std::vector<float>>& weight,
                     int start_address, bool is_last)
{
    if (is_busy(core_num))
    {
        return false;
    }
    is_busy_flag_ = true;
    
    neurons_data_ = neurons;
    weight_data_ = weight;
    start_address_ = start_address;
    is_last_flag_ = is_last;
    core_num_ = core_num;
    result_.resize(weight_data_.size());
    return true;
}

float core::activ_f(float data)
{
    return 1 / (1 + exp(-data));
}

std::vector<float> core::softmax(std::vector<float> t)
{
    std::vector<float> out;
    out.resize(t.size());
    double sum = 0;
    for (int i = 0; i < t.size(); ++i) {
        out[i] = std::exp(t[i]);
        sum += out[i];
    }
    for (int i = 0; i < t.size(); ++i) {
        out[i] /= sum;

    }
    return out;
}