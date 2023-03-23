#include "../core.h"

void core::control_process()
{
    while (true)
    {
        while (!is_busy_flag_)
        {
            wait();
        }
        wait();
        core_is_busy.write(is_busy_flag_);
        is_last_flag_ = core_is_last.read();
        start_address_ = core_is_start_address.read();
        if (core_is_last.read())
            cout << "last core count" << endl;
        cout << "core " << core_num_ << " start count" << endl;

        if (is_last_flag_)
        {
            result_ = softmax(neurons_data_);
            memory_write(result_);
            is_busy_flag_ = false;
            core_is_busy.write(is_busy_flag_);
            wait();
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

        memory_write(result_);
        is_busy_flag_ = false;
        core_is_busy.write(is_busy_flag_);
        wait();
    }
}

void core::memory_write(const std::vector<float>& data)
{
    int num_packets = data.size() / BUFFER_SIZE + 1;
    for (int i = 0; i < num_packets; ++i)
    {
        const int start_index = i * BUFFER_SIZE;
        const int end_index = std::min(start_index + BUFFER_SIZE, (int)data.size());
        std::vector<float> packet_data(data.begin() + start_index, data.begin() + end_index);
        bus_memory_start_addr_i.write(start_index + start_address_);
        bus_memory_len_i.write(packet_data.size());
        for (int j = 0; j < packet_data.size(); ++j)
        {
            bus_memory_data_i[j]->write(packet_data[j]);
        }
        bus_memory_wr.write(true);
        wait(2);
    }
    bus_memory_wr.write(false);
}

bool core::core_task(int core_num, std::vector<float>& neurons, std::vector<std::vector<float>>& weight)
{
    if (is_busy_flag_)
    {
        return false;
    }
    is_busy_flag_ = true;
    
    neurons_data_ = neurons;
    weight_data_ = weight;
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