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

#endif //YANXIANG_VALUE_TYPE_H
