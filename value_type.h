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
typedef struct search_id_reasult
{
    double temperature;
    double humidity;
}search_id_reasult;
typedef struct modbusdata
{
    unsigned int id;
    unsigned int address;
    search_id_reasult res;
}modbusdata;

#endif //YANXIANG_VALUE_TYPE_H
