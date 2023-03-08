#include "systemc.h"

SC_MODULE(IO_Controller) {
    sc_out<sc_uint<32>> addr_bus; // �������� ���� ��� ������
    sc_in<sc_uint<64>> data_bus; // ������� ���� ��� ������
    sc_out<bool> clk_out; // �������� ���� ��� ��������� �������
    sc_out<bool> read_write; // �������� ���� ��� ������/������

    SC_CTOR(IO_Controller) {
        SC_THREAD(main_process);
    }

    void main_process() {
        while (true) {
            wait(); // ���� ������� ��������� �������
            if (read_write.read()) { // ���� ������ ������
                // ��������� ������ �� ������, ����������� �� ����
                sc_uint<64> data = read_data(addr_bus.read());
                // ���������� ��������� ������ �� ���� ������
                data_bus.write(data);
            } else { // ���� ������ ������
                // ���������� ���������� ������ �� ������, ����������� �� ����
                write_data(addr_bus.read(), data_bus.read());
            }
        }
    }

    sc_uint<64> read_data(sc_uint<32> addr) {
        // ���������� ������ ������ �� ������ �� ����������� ������
        // ...
    }

    void write_data(sc_uint<32> addr, sc_uint<64> data) {
        // ���������� ������ ������ � ������ �� ����������� ������
        // ...
    }
};