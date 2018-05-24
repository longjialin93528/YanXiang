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
    device_type type;
    double temperature;
    double humidity;
}modbusdata;
typedef struct search_id_reasult
{
    double temperature;
    double humidity;
}search_id_reasult;
#endif //YANXIANG_VALUE_TYPE_H
