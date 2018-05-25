//
// Created by long on 2018/5/18.
//

#ifndef YANXIANG_VALUE_TYPE_H
#define YANXIANG_VALUE_TYPE_H
enum device_type
{
    REST=0,
    OPC_UA,
    MODBUS,
    DIDO,
    MQTT,
    ISA100,
    BACNET,
    ULE,
    BLE,
    ENOCEAN,
    NONE
};
typedef struct modbusdata
{
    unsigned int id;
    unsigned int address;
    double temperature;
    double humidity;
}modbusdata;
typedef struct devicedata
{
    unsigned int id;
    device_type type;
    char * path;
    char * devicelocation;//底层设备安装地点
}devicedata;
#endif //YANXIANG_VALUE_TYPE_H
