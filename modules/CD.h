﻿#pragma once
#include <sysc/kernel/sc_module.h>

#include "systemc.h"

SC_MODULE(CD)
{
    // global
    sc_in<bool> clk; // Тактовый сигнал
    sc_in<int> layer_count; // колличество слоев
    sc_out<int> current_layer; // переменный параметр, указывает с каким слоем мы сейчас работаем

    // CD
    sc_in<bool> data_ready; // Флаг готовности данных на внешнем накопителе
    sc_out<bool> load_data; // Сигнал загрузки данных из внешнего накопителя в общую память
    sc_out<bool> result_ready; // Флаг готовности результата вычисления НС
    
    // memory
    // out
    sc_out<bool> wr_o_memory; // сигнал на переход памяти в режим записи
    sc_out<bool> rd_o_memory; // сигнал на переход памяти в режим чтения
    sc_out<int> data_s_o_memory; // адрес с которого начинаются данные для запись в память
    sc_out<int> data_len_o_memory; // колличество элементов для запись в память
    // in
    sc_in<int> data_addr_s_i_memory; // адрес с которого начинаются данные для чтения с памяти
    sc_in<int> data_len_i_memory; // колличество элементов для чтения с памяти    

    /*
    // Core
    sc_in<bool> interrupt_signal; // Сигнал прерывания от вычислительных ядер
    sc_out<int> target_address; // Адрес, куда нужно передать данные для вычислений
    sc_out<int> result_address; // Адрес, куда нужно поместить результат вычислений
    sc_out<int> layer_number; // Номер текущего обрабатываемого слоя
    sc_in<bool> unload_data; // Сигнал выгрузки данных из общей памяти на вычислительное ядро
    bool is_busy = false; // Флаг занятости вычислительных ядер
    */
    
    // Процессор, отвечающий за управление устройством
    void control_process();

    // чтение данных из файла TODO добавить параметр название файла, и то, как данные принимать
    void read_data_from_file();

    // инициализация, достает данные из файла и отправляет их в память, запускается когда data_ready && !load_data && !result_ready
    void init();

    // отправка данных в поток вывода
    void out();

    // запись данных в память
    void memory_write();

    // чтение из памяти
    void memory_read();
    
    // Конструктор модуля
    SC_CTOR(CD)
    {
        // Запускаем процессор, отвечающий за управление устройством
        SC_THREAD(control_process);
        sensitive << clk.pos(); // Привязываем процесс к положительному фронту тактового сигнала
    }
};
