//
// Created by long on 2018/5/18.
//
#include "device_modbus.h"
using namespace std;
Modbus_device::Modbus_device() {
    rd_cmd=NULL;
    device_path=NULL;
}
Modbus_device::~Modbus_device() {
    if(rd_cmd!= NULL)
    {
        delete rd_cmd;
    }
    if(device_path!=NULL)
    {
        delete device_path;
    }
}
/*私有函数的声明，主要服务于内部函数的实现*/
void Modbus_device::InvertUint8(unsigned char *dBuf, unsigned char *srcBuf) {
    int i;
    unsigned char tmp[4];
    tmp[0] = 0;
    for (i = 0; i< 8; i++)
    {
        if (srcBuf[0] & (1 << i))
            tmp[0] |= 1 << (7 - i);
    }
    dBuf[0] = tmp[0];
}
void Modbus_device::InvertUint16(unsigned short *dBuf, unsigned short *srcBuf) {
    int i;
    unsigned short tmp[4];
    tmp[0] = 0;
    for (i = 0; i< 16; i++)
    {
        if (srcBuf[0] & (1 << i))
            tmp[0] |= 1 << (15 - i);
    }
    dBuf[0] = tmp[0];
}
unsigned short Modbus_device::CRC16_MODBUS(unsigned char *puchMsg, unsigned int usDataLen) {
    unsigned short wCRCin = 0xFFFF;
    unsigned short wCPoly = 0x8005;
    unsigned char wChar = 0;

    while (usDataLen--)
    {
        wChar = *(puchMsg++);
        InvertUint8(&wChar, &wChar);
        wCRCin ^= (wChar << 8);
        for (int i = 0; i < 8; i++)
        {
            if (wCRCin & 0x8000)
                wCRCin = (wCRCin << 1) ^ wCPoly;
            else
                wCRCin = wCRCin << 1;
        }
    }
    InvertUint16(&wCRCin, &wCRCin);
    return (wCRCin);
}
void Modbus_device::set_rd_cmd(unsigned char *rd_cmd, unsigned int id) {
    ;
}
