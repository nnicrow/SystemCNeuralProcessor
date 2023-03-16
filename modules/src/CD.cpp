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
        
        // запрос данных весов
        int weight_len = layers_[layer_num] * layers_[layer_num + 1];
        std::vector<float> weight = bus_memory_inst->read(address_[layer_num], weight_len);
        wait();

        // запрос данных слоев
        std::vector<float> neurons = bus_memory_inst->read(address_[layer_num + layer_count_ - 1], layers_[layer_num]);
        // считаем вектор размера задачи
        std::vector<int> tasks;
        tasks.resize(CORE_COUNT);
        int size_of_task = layers_[layer_num] / 3;
        for (int i = 0; i < CORE_COUNT; ++i)
        {
            tasks[i] = size_of_task;
        }
        int remainder = layers_[layer_num] % CORE_COUNT;
        for (int i = 0; i < remainder; ++i)
        {
            tasks[i] += 1;
        }

        // считаем вектор задачи
        std::vector<std::vector<float>> neurons_tasks;
        neurons_tasks.resize(CORE_COUNT);
        int total_neurons = 0;
        for (int i = 0; i < CORE_COUNT; ++i)
        {
            neurons_tasks[i].resize(tasks[i]);
            for (int j = 0; j < tasks[i]; ++j)
            {
                neurons_tasks[i][j] = neurons[total_neurons + j];
            }
            total_neurons += tasks[i];
        }

        // распределяем задачи
        for (int i = 0; i < CORE_COUNT; ++i)
        {
            while (true)
            {
                // елси ложь, то ядро не может принять задачу.
                if (bus_cores_inst->core_task(i, neurons_tasks[i], weight, tasks[i] + last_memory_busy_address_))
                    break;
                wait();
            }
        }
        last_memory_busy_address_ += layers_[layer_num + 1];
    }
    // расчёт закончен. Осталось применить функцию soft_max
    while (bus_memory_inst->mem_is_busy())
    {
        wait();
    }
    // TODO result
    // std::vector<float> result = bus_memory_inst->read(address_[layer_num + layer_count_ - 1], layers_[layer_count_ - 1]);
    
}

void CD::write_to_memory(std::vector<float>& data, int len)
{
    address_[address_count_++] = last_memory_busy_address_;
    bus_memory_inst->write(data, last_memory_busy_address_);
    last_memory_busy_address_ += len;
}
