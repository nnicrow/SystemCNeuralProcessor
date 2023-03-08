#include "../CD.h"

void CD::control_process()
{
    /*while (true)
        {
            wait(); // Ожидание следующего такта

            // Если есть сигнал прерывания, то сохраняем текущий слой и адрес, куда нужно было передать данные
            if (interrupt_signal.read())
            {
                current_layer++; // Переходим к следующему слою
                target_address.write(result_address.read());
                // Передаем данные на вычисление в предыдущее вычислительное ядро
                layer_number.write(current_layer); // Сохраняем номер текущего слоя
            }

            // Если есть готовые данные на внешнем накопителе, то загружаем их в общую память
            if (data_ready.read())
            {
                load_data.write(true); // Посылаем сигнал на загрузку данных
            }

            // Если есть свободные вычислительные ядра и есть данные для передачи, то передаем данные на вычисление
            if (!is_busy && unload_data.read())
            {
                target_address.write(target_address.read() + 1); // Переходим к следующему нейрону в текущем слое
                result_address.write(result_address.read() + 1);
                // Переходим к следующему свободному адресу для записи результата
                unload_data.write(false);
                is_busy = true; // Устанавливаем флаг занятости вычислительных ядер
            }

            // Если есть готовый результат вычисления, то выгружаем его на выходной порт НС
            if (result_ready.read())
            {
                unload_result.write(true); // Посылаем сигнал на выгрузку результата
                is_busy = false; // Снимаем флаг занятости вычислительных ядер
            }
        }*/
}

void CD::read_data_from_file()
{
}

void CD::init()
{
}

void CD::out()
{
}

void CD::memory_write()
{
}

void CD::memory_read()
{
}
