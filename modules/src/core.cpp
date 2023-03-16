#include "../core.h"

void core::control_process()
{
    while (!is_busy_flag_)
    {
        wait();
        continue;
    }
    cout << "core " << core_num_ << " start count" << endl;

    // массив выходов с предыдущего слоя
    std::vector<float> data_in = neurons_data_;

    // цикл (пока не закончатся пары числе)
    for (int i = 0; i < weight_data_[0].size(); i += 8)
    {
        std::vector<float> result(8);

        // берём 8 пар (x, w)
        for (int j = 0; j < 8; ++j)
        {
            float x = data_in[j];
            float w = weight_data_[j][i + j];

            // умножаем
            result[j] = x * w;
        }

        // записываем в буфер
        buffer_.push_back(result);

        // Этап конвеера - умножение на веса и применение функции активации
        for (int j = 0; j < 8; ++j)
        {
            float sum = 0.0;
            for (int k = 0; k < 8; ++k)
            {
                sum += buffer_.back()[k] * weight_data_[j][i + k];
            }
            neurons_data_[j] = activ_f(sum);
        }
    }

    // обработка последнего слоя
    if (is_last)
    {
        std::vector<float> result(8);
        for (int j = 0; j < 8; ++j)
        {
            float sum = 0.0;
            for (int k = 0; k < weight_data_[0].size(); ++k)
            {
                sum += neurons_data_[k] * weight_data_[j][k];
            }
            result[j] = activ_f(sum);
        }
        buffer_.push_back(result);
    }

    // сброс флага занятости
    is_busy_flag_ = false;
}


bool core::is_busy(int core_num)
{
    return is_busy_flag_;
}

bool core::core_task(int core_num, std::vector<float>& neurons, std::vector<std::vector<float>>& weight, int start_address, bool is_last)
{
    if (is_busy(core_num))
    {
        return false;
    }
    neurons_data_ = neurons;
    weight_data_ = weight;
    is_busy_flag_ = true;
    core_num_ = core_num;
    return true;
}

float core::activ_f(float data)
{
    return 1 / (1 + exp(-data));
}
