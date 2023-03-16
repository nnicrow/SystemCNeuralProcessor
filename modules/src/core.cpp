#include "../core.h"

void core::control_process()
{
    while (!is_busy_flag)
    {
        wait();
        continue;
    }
    // TODO: алгоритм расчета

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
    return is_busy_flag;
}

bool core::core_task(int core_num, std::vector<float>& neurons, std::vector<float>& weight, int start_address)
{
    if (is_busy(core_num))
    {
        return false;
    }

    // принимает задачу и кидает данные в локальную область памяти, а потом ждем что все выполнится и когда выполняется, ставим is_busy_flag в ложь
    // TODO: разобрать вектора на двумерный вектор, чтобы было проще работать
    is_busy_flag = true;
    return true;
}

float core::activ_f(float data)
{
    return 1 / (1 + exp(-data));
}
