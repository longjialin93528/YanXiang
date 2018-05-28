//
// Created by long on 2018/5/18.
//

#ifndef YANXIANG_DEVICE_MODBUS_H
#define YANXIANG_DEVICE_MODBUS_H

#include "device_base.h"
#include "sqlcon_modbus.h"
#include <string>
class Modbus_device:public Base_device
{
private:
    double temperature;
    double humidity;
    char *device_path;
    unsigned char *rd_cmd;
    sqlcon_modbus * ptr_sqlcon_modbus;
    bool is_fullone(char a);//此函数用于温度计算
    double func(int *a,int n);//用于温度计算
    /*用于计算crc循环函数*/
    void InvertUint8(unsigned char *dBuf, unsigned char *srcBuf);
    void InvertUint16(unsigned short *dBuf, unsigned short *srcBuf);
    unsigned short CRC16_MODBUS(unsigned char *puchMsg, unsigned int usDataLen);
    void set_rd_cmd(unsigned char *rd_cmd,unsigned int id);
public:
    Modbus_device();
    Modbus_device(unsigned int id,char *path);
    ~Modbus_device();
    double get_temperature(char a,char b);
    double get_humidity(char a,char b);

    /*用于封装sqlcon_modbus的insert与update方法*/
    void update();
    void insert();

    void show_temperature();
    void show_humidity();
    void run();
    //unsigned int get_deviceAddress();
    //void set_deviceAddress(unsigned int address);
};

#endif //YANXIANG_DEVICE_MODBUS_H
