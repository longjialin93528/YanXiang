//
// Created by long on 2018/5/30.
//

#ifndef YANXIANG_DEVICE_DIDO_H
#define YANXIANG_DEVICE_DIDO_H

#include "device_base.h"
#include "sqlcon_dido.h"
#include <string>
class Modbus_device_dido:public Base_device
{
private:
    unsigned int di1;
    unsigned int di2;
    unsigned int di3;
    unsigned int di4;
    unsigned int di5;
    unsigned int di6;
    unsigned int di7;
    unsigned int di8;
    char * device_path;
    unsigned char * rd_cmd;
    sqlcon_dido * ptr_sqlcon_dido;
    /*用于计算crc循环函数*/
    void InvertUint8(unsigned char *dBuf, unsigned char *srcBuf);
    void InvertUint16(unsigned short *dBuf, unsigned short *srcBuf);
    unsigned short CRC16_MODBUS(unsigned char *puchMsg, unsigned int usDataLen);
    void set_rd_cmd(unsigned char *rd_cmd,unsigned int id);

public:
    Modbus_device_dido();
    Modbus_device_dido(unsigned int id,char * path);
    ~Modbus_device_dido();
    didodata get_dido(char a);

    /*用于封装sqlcon_modbus_pm的insert与update方法*/
    void update();
    void insert();

    void show_dido();
    void run();
};
#endif //YANXIANG_DEVICE_DIDO_H
