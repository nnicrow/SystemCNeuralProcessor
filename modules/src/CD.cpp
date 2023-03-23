#include "../CD.h"

#include <fstream>
#include "../../config.h"

void CD::proccess()
{
    // read data from file
    cout << "Start read data" << endl;

    // read and push weight to memory
    ifstream fin("data/weight.txt");
    while (!fin.eof())
    {
        for (int layer_num = 0; layer_num < layer_count_ - 1; ++layer_num)
        {
            std::vector<float> data;
            int len = layers_[layer_num] * layers_[layer_num + 1];
            data.resize(len);
            for (int i = 0; i < len; ++i)
            {
                fin >> data[i];
            }
            memory_write(data);
            end_write_to_memory(len);
        }
        break;
    }
    while (bus_memory_is_busy.read())
    {
        wait();
    }
    // read and push neurons to memory
    std::string filename = FILE_NAME;
    ifstream fin2(filename);
    while (!fin2.eof())
    {
        std::vector<float> data;
        int len = layers_[0];
        data.resize(len);
        for (int i = 0; i < len; ++i)
        {
            fin2 >> data[i];
        }
        memory_write(data);
        end_write_to_memory(len);
        break;
    }
    while (bus_memory_is_busy.read())
    {
        wait();
    }
    cout << "End read data" << endl;
    bus_memory_rd.write(true);

    // расчёты
    for (int layer_num = 0; layer_num < layer_count_ - 1; ++layer_num)
    {
        // запрос данных слоев
        std::vector<float> neurons = memory_read(address_[layer_num + layer_count_ - 1], layers_[layer_num]);

        // запрос данных весов
        std::vector<float> weight = memory_read(address_[layer_num],
                                                layers_[layer_num] * layers_[layer_num + 1]);

        std::vector<std::vector<float>> weight_data;
        weight_data.resize(layers_[layer_num + 1]);
        int weight_counter = 0;
        for (int i = 0; i < layers_[layer_num + 1]; ++i)
        {
            weight_data[i].resize(layers_[layer_num]);
            for (int j = 0; j < layers_[layer_num]; ++j)
            {
                weight_data[i][j] = weight[weight_counter++];
            }
        }

        // объявляем параметры
        std::vector<int> tasks;
        tasks.resize(CORE_COUNT);
        std::vector<std::vector<std::vector<float>>> weight_tasks;
        weight_tasks.resize(CORE_COUNT);

        // считаем вектор размера задачи 
        int size_of_task = layers_[layer_num + 1] / CORE_COUNT;
        for (int i = 0; i < CORE_COUNT; ++i)
        {
            tasks[i] = size_of_task;
        }
        int remainder = layers_[layer_num + 1] % CORE_COUNT;
        for (int i = 0; i < remainder; ++i)
        {
            tasks[i] += 1;
        }

        // считаем вектор задачи
        int total_neurons = 0;
        for (int i = 0; i < CORE_COUNT; ++i)
        {
            weight_tasks[i].resize(tasks[i]);

            for (int j = 0; j < tasks[i]; ++j)
            {
                weight_tasks[i][j].resize(layers_[layer_num]);
                for (int k = 0; k < layers_[layer_num]; ++k)
                {
                    weight_tasks[i][j][k] = weight_data[j + tasks[i] * i][k];
                }
            }

            total_neurons += tasks[i];
        }

        memory_address_selection(layers_[layer_num + 1]);
        // распределяем задачи
        for (int i = 0; i < CORE_COUNT; ++i)
        {
            while (cors_is_busy[i].read())
            {
                wait();
            }
            bus_cores_inst->core_task(i, neurons, weight_tasks[i]);
            core_is_start_address[i].write(last_memory_busy_address_);
            last_memory_busy_address_ += tasks[i];
        }
        wait();
        for (int i = 0; i < CORE_COUNT; ++i)
        {
            while (cors_is_busy[i].read())
            {
                wait(CORE_COUNT + 1);
            }
        }

        while (bus_memory_is_busy.read())
        {
            wait();
        }
    }

    std::vector<float> neurons = memory_read(address_.back(), layers_[layer_count_ - 1]);
    
    std::vector<std::vector<float>> weight_task;
    while (cors_is_busy[0].read())
    {
        wait();
    }
    bus_cores_inst->core_task(0, neurons, weight_task);
    memory_address_selection(layers_[layer_count_ - 1]);
    last_memory_busy_address_ += layers_[layer_count_ - 1];
    core_is_start_address[0].write(last_memory_busy_address_);
    bus_core_is_last[0].write(true);

    wait();
    std::vector<float> result = memory_read(address_.back(), layers_[layer_count_ - 1]);
    for (const float i : result)
    {
        cout << i << endl;
    }
    out_result(result);
}

void CD::end_write_to_memory(const int len)
{
    address_.resize(address_.size() + 1);
    address_[address_count_++] = last_memory_busy_address_;
    last_memory_busy_address_ += len;
    bus_memory_wr.write(false);
}

void CD::memory_write(const std::vector<float>& data)
{
    int num_packets = data.size() / BUFFER_SIZE + 1;
    for (int i = 0; i < num_packets; ++i)
    {
        const int start_index = i * BUFFER_SIZE;
        const int end_index = std::min(start_index + BUFFER_SIZE, (int)data.size());
        std::vector<float> packet_data(data.begin() + start_index, data.begin() + end_index);
        bus_memory_start_addr_i.write(start_index + last_memory_busy_address_);
        bus_memory_len_i.write(packet_data.size());
        for (int j = 0; j < packet_data.size(); ++j)
        {
            bus_memory_data_i[j]->write(packet_data[j]);
        }
        bus_memory_wr.write(true);
        wait();
    }
}

std::vector<float> CD::memory_read(int start_address, int len)
{
    std::vector<float> res_data;
    res_data.resize(len);
    int num_packets = len / BUFFER_SIZE + 1;
    for (int i = 0; i < num_packets; ++i)
    {
        int start_index = i * BUFFER_SIZE;
        int end_index = std::min(start_index + BUFFER_SIZE, len);
        bus_memory_start_addr_i.write(start_address + start_index);
        bus_memory_len_i.write(end_index - start_index);
        bus_memory_rd.write(true);

        wait(4);
        for (int j = 0; j < end_index - start_index; ++j)
        {
            res_data[i * BUFFER_SIZE + j] = bus_memory_data_o[j].read();
        }
        wait();
    }
    bus_memory_rd.write(false);
    return res_data;
}

void CD::memory_address_selection(const int len)
{
    address_.resize(address_.size() + 1);
    address_[address_count_++] = last_memory_busy_address_;
    // last_memory_busy_address_ += len;
}

enum result_enum { circle, square, triangle };

inline const char* ToString(result_enum e)
{
    switch (e)
    {
    case circle: return "Circle";
    case square: return "Square";
    case triangle: return "Triangle";
    }
}

void CD::out_result(std::vector<float>& data)
{
    int max_index = 0;

    for (int i = 1; i < data.size(); ++i)
    {
        if (data[i] > data[max_index])
        {
            max_index = i;
        }
    }
    result_enum e = static_cast<result_enum>(max_index);

    cout << endl;
    cout << "Result is " << ToString(e) << endl;
}
