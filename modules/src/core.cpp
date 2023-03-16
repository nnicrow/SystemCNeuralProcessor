#include "../core.h"

void core::control_process()
{
    while (true)
    {
        wait();
    }
    /*
    data_in // массив выходов с предыдущего слоя, массив вессов текщего слоя 
    цикл (пока не закончатся пары числе)    
        берём 8 пар (x, w)
        умножаем
        записываем друг 
        записываем в буфер //-- Этап конвеера
        
    while ()
    {
        data_in.start * 
    }
    */
}

std::vector<float>& core::read(int start_addr, int len)
{
    std::vector<float> data;
    return data;
}

void core::write(std::vector<float>& data, int start_address)
{
    cout << "core" << endl;
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
    return true;
}
