#pragma once
#include "../config.h"
#include "../interfaces/ISlave.h"

class CD : public sc_module
{
public:
    // global
    sc_in<bool> clk; // Тактовый сигнал
    sc_port<ISlave> bus_inst;
    
    /*sc_out<int> layer_count; // колличество слоев
    sc_out<int> current_layer; // переменный параметр, указывает с каким слоем мы сейчас работаем
    sc_out<float> buffer_cd[BOFFER_SIZE]; //буфер для СД
    sc_in<float> buffer_memory[BOFFER_SIZE]; //буфер памяти
    sc_out<int> buffer_address_cd; //адрес буфера СД
    sc_in<int> buffer_address_memory; //адрес буфера памяти

    // CD
    sc_in<bool> data_ready; // Флаг готовности данных на внешнем накопителе
    sc_in<bool> load_data; // Сигнал загрузки данных из внешнего накопителя в общую память
    sc_out<bool> result_ready; // Флаг готовности результата вычисления НС

    // memory
    // out
    sc_out<bool> wr_o_memory; // сигнал на переход памяти в режим записи
    sc_out<bool> rd_o_memory; // сигнал на переход памяти в режим чтения
    sc_out<int> data_s_o_memory; // адрес с которого начинаются данные для запись в память
    sc_out<int> data_len_o_memory; // колличество элементов для запись в память
    sc_out<bool> w_or_l; // колличество элементов для запись в память
    // in
    sc_in<int> data_addr_s_i_memory; // адрес с которого начинаются данные для чтения с памяти
    sc_in<int> data_len_i_memory; // колличество элементов для чтения с памяти    

    // core
    sc_in<int> data_s_core;
    sc_in<int> weight_s_core;
    sc_in<int> data_count_core;
    sc_in<int> res_s_core;
    sc_in<bool> is_work_core;
    sc_in<bool> is_last_layer_core;
    sc_in<bool> is_busy_o_core;

    /*
    sc_in<bool> interrupt_signal; // Сигнал прерывания от вычислительных ядер
    sc_out<int> target_address; // Адрес, куда нужно передать данные для вычислений
    sc_out<int> result_address; // Адрес, куда нужно поместить результат вычислений
    sc_out<int> layer_number; // Номер текущего обрабатываемого слоя
    sc_in<bool> unload_data; // Сигнал выгрузки данных из общей памяти на вычислительное ядро
    bool is_busy = false; // Флаг занятости вычислительных ядер
    #1#

    // Процессор, отвечающий за управление устройством
    void control_process();

    // чтение данных из файла TODO добавить параметр название файла, и то, как данные принимать

    // отправка данных в поток вывода
    void out();

    // запись данных в память
    void memory_write(int data_s_o_memory, int data_len_o_memory);
    void memory_write_off();
    void memory_read_off();
    // чтение из памяти
    void memory_read();*/

    
    // Конструктор модуля
    SC_CTOR(CD)
    {
        /*SC_THREAD(control_process)*/
        sensitive << clk.pos();
    }

/*private:
    bool is_init = false;*/
};
