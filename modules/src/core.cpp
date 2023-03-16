#include "../core.h"

void core::control_process()
{
    while (!is_busy_flag_)
    {
        wait();
        continue;
    }
    cout << "core " << core_num_ << " start count" << endl;

    for (int task_num = 0; task_num < weight_data_.size() - 1; ++task_num)
    {
        int var;
    }
    
    /*
    data_in // массив выходов с предыдущего слоя, массив вессов текщего слоя 
    цикл (пока не закончатся пары числе)    
        берём 8 пар (x, w)
        умножаем
        записываем друг 
        записываем в буфер //-- Этап конвеера
    */
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
