//
// Created by long on 2018/6/4.
//

#ifndef YANXIANG_DEVICE_MODBUS_TH_H
#define YANXIANG_DEVICE_MODBUS_TH_H

#include "device_modbus.h"
#include "sqlcon_modbus_th.h"
#include <string>
class Modbus_device_th:public Modbus_device
{
private:
    double temperature;
    double humidity;
    sqlcon_modbus_th * ptr_sqlcon_modbus;
    bool is_fullone(char a);//此函数用于温度计算
    double func(int *a,int n);//用于温度计算
    void set_rd_cmd(unsigned char *rd_cmd,unsigned int id);
public:
    Modbus_device_th();
    Modbus_device_th(unsigned int id,char *path);
    ~Modbus_device_th();
    double get_temperature(char a,char b);
    double get_humidity(char a,char b);

    /*用于封装sqlcon_modbus的insert与update方法*/
    void update();
    void insert();

    void show_temperature();
    void show_humidity();
    void run();
};
#endif //YANXIANG_DEVICE_MODBUS_TH_H
