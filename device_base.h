//
// Created by long on 2018/5/18.
//

#ifndef YANXIANG_DEVICE_BASE_H
#define YANXIANG_DEVICE_BASE_H

#include "value_type.h"
#include <iostream>
class Base_device
{
protected:
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
    virtual void run()=0;//纯虚函数，必须实现
    virtual void insert()=0;
    virtual void update()=0;
};

#endif //YANXIANG_DEVICE_BASE_H
