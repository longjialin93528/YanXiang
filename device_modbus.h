//
// Created by long on 2018/5/18.
//

#ifndef YANXIANG_DEVICE_MODBUS_H
#define YANXIANG_DEVICE_MODBUS_H

#include "device_base.h"
#include <string>
class Modbus_device:public Base_device
{
protected:
    char * device_path;
    unsigned char *rd_cmd;
    /*用于计算crc循环函数*/
    void InvertUint8(unsigned char *dBuf, unsigned char *srcBuf);
    void InvertUint16(unsigned short *dBuf, unsigned short *srcBuf);
    unsigned short CRC16_MODBUS(unsigned char *puchMsg, unsigned int usDataLen);
    virtual void set_rd_cmd(unsigned char *rd_cmd,unsigned int id);
public:
    Modbus_device();
    virtual ~Modbus_device();
};

#endif //YANXIANG_DEVICE_MODBUS_H
