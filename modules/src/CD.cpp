﻿#include "../CD.h"

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
            write_to_memory(data, len);
            wait();
        }
        break;
    }

    // read and push neurons to memory
    ifstream fin2("data/square.txt");
    while (!fin2.eof())
    {
        std::vector<float> data;
        int len = layers_[0];
        data.resize(len);
        for (int i = 0; i < len; ++i)
        {
            fin2 >> data[i];
        }
        write_to_memory(data, len);
        wait();
        break;
    }
    cout << "End read data" << endl;

    for (int layer_num = 0; layer_num < layer_count_ - 1; ++layer_num)
    {
        while (bus_memory_inst->mem_is_busy())
        {
            wait();
        }

        // запрос данных слоев
        std::vector<float> neurons = bus_memory_inst->read(address_[layer_num + layer_count_ - 1], layers_[layer_num]);
        wait();

        // запрос данных весов
        std::vector<float> weight = bus_memory_inst->read(address_[layer_num],
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
        int size_of_task = layers_[layer_num + 1] / 3;
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
                    weight_tasks[i][j][k] = weight_data[j][k];
                }
            }

            total_neurons += tasks[i];
        }

        // распределяем задачи
        for (int i = 0; i < CORE_COUNT; ++i)
        {
            while (true)
            {
                // елси ложь, то ядро не может принять задачу.
                if (bus_cores_inst->core_task(i, neurons, weight_tasks[i], last_memory_busy_address_))
                    break;
                wait();
            }
            last_memory_busy_address_ += tasks[i];
        }
    }
    // расчёт закончен. Осталось применить функцию soft_max
    while (bus_memory_inst->mem_is_busy())
    {
        wait();
    }
    std::vector<float> neurons = bus_memory_inst->read(address_[layer_count_ + layer_count_ - 1],
                                                       layers_[layer_count_ - 1]);
    wait();
    std::vector<std::vector<float>> weight_task;
    while (true)
    {
        // елси ложь, то ядро не может принять задачу.
        if (bus_cores_inst->core_task(0, neurons, weight_task, last_memory_busy_address_, true))
            break;
        wait();
    }
    last_memory_busy_address_ += layers_[layer_count_ - 1];
    std::vector<float> result = bus_memory_inst->read(address_[layer_count_ + layer_count_], layers_[layer_count_ - 1]);
    
    
}

void CD::write_to_memory(std::vector<float>& data, int len)
{
    address_[address_count_++] = last_memory_busy_address_;
    bus_memory_inst->write(data, last_memory_busy_address_);
    last_memory_busy_address_ += len;
}

RESULT_ENUM

void CD::out_result(std::vector<float>& data)
{
    int max_index = 0;

    for (int i = 1; i < data.size(); ++i) {
        if (data[i] > data[max_index]) {
            max_index = i;
        }
    }
    result_enum e = static_cast<result_enum>(max_index);
    cout << "Result is" << e << endl;
}