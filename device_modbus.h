//
// Created by long on 2018/5/18.
//

#ifndef YANXIANG_DEVICE_MODBUS_H
#define YANXIANG_DEVICE_MODBUS_H

#include "device_base.h"
#include <string>
class Modbus_device:public Base_device
{
private:
    double temperature;
    double humidity;
    char *rd_cmd;
   // char *wt_cmd;
    bool is_fullone(char a);
    double func(int *a,int n);
public:
    Modbus_device();
    explicit Modbus_device(unsigned int id);
    ~Modbus_device();
    double get_temperature(char a,char b);
    double get_humidity(char a,char b);
    void set_rd_cmd();
    void show_temperature();
    void show_humidity();
    void run();
    //unsigned int get_deviceAddress();
    //void set_deviceAddress(unsigned int address);
};

#endif //YANXIANG_DEVICE_MODBUS_H
