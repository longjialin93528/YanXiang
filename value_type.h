//
// Created by long on 2018/5/18.
//

#ifndef YANXIANG_VALUE_TYPE_H
#define YANXIANG_VALUE_TYPE_H

#include <cstdlib>
enum device_type
{
    REST=0,
    OPC_UA,
    MODBUS_TH,
    DIDO,
    MQTT,
    ISA100,
    BACNET,
    ULE,
    BLE,
    ENOCEAN,
    NONE,
    MODBUS_PM
};
typedef struct modbusdata
{
    unsigned int id;
    unsigned int address;
    double temperature;
    double humidity;
}modbusdata;
typedef struct modbusPMdata
{
    unsigned int id;
    unsigned int address;
    unsigned int PM2;
    unsigned int PM10;
}modbusPMdata;
typedef struct didodata
{
    unsigned int id;
    unsigned int address;
    unsigned int di1;
    unsigned int di2;
    unsigned int di3;
    unsigned int di4;
    unsigned int di5;
    unsigned int di6;
    unsigned int di7;
    unsigned int di8;
};
typedef struct devicedata
{
    unsigned int id;
    device_type type;
    char * path;
    char * devicelocation;//底层设备安装地点
    devicedata(int id,device_type type,char * path,char *location):id(id),type(type),path(path),devicelocation(location){};
    devicedata():id(0),type(NONE),path(NULL),devicelocation(NULL){};
}devicedata;
#endif //YANXIANG_VALUE_TYPE_H
