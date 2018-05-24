//
// Created by long on 2018/5/18.
//

#ifndef YANXIANG_DEVICE_BASE_H
#define YANXIANG_DEVICE_BASE_H

#include "value_type.h"
#include <iostream>
class Base_device
{
private:
    unsigned int deviceID;
    device_type deviceType;
    unsigned int deviceAddress;
public:
    Base_device();
    Base_device(unsigned int id);
    virtual ~Base_device();
    unsigned int get_deviceID();
    void set_deviceID(unsigned int id);
    device_type get_deviceType();
    void set_deviceType(device_type type);
    unsigned int get_deviceAddress();
};

#endif //YANXIANG_DEVICE_BASE_H
