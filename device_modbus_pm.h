//
// Created by long on 2018/5/30.
//

#ifndef YANXIANG_DEVICE_MODBUS_PM_H
#define YANXIANG_DEVICE_MODBUS_PM_H

#include "device_modbus.h"
#include "sqlcon_modbus_pm.h"
#include <string>
class Modbus_device_pm:public Modbus_device
{
private:
    unsigned int PM2;
    unsigned int PM10;
    sqlcon_modbus_pm * ptr_sqlcon_modbus_pm;
    /*用于计算PM值的辅助函数*/
    unsigned int get_hec(int *str);
    unsigned int my_pow(int n);
    /*用于计算crc循环函数*/
    void set_rd_cmd(unsigned char *rd_cmd,unsigned int id);
public:
    Modbus_device_pm();
    Modbus_device_pm(unsigned int id,char * path);
    ~Modbus_device_pm();
    unsigned int get_PM2(char a,char b);
    unsigned int get_PM10(char a,char b);

    /*用于封装sqlcon_modbus_pm的insert与update方法*/
    void update();
    void insert();

    void show_PM2();
    void show_PM10();
    void run();
};
#endif //YANXIANG_DEVICE_MODBUS_PM_H
