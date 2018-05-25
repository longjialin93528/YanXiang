//
// Created by long on 2018/5/25.
//

#ifndef YANXIANG_DEVICE_MANAGER_H
#define YANXIANG_DEVICE_MANAGER_H

#include "sqlcon_add_device.h"
#include "sqlcon_modbus.h"
#include "device_modbus.h"
#include <vector>
using namespace std;
class device_manager
{
private:
    sqlcon_add_device * addDevice_ptr;
    vector<Base_device *> device_list;
public:
    device_manager();
    explicit device_manager(char * tbname);
    ~device_manager();
};
#endif //YANXIANG_DEVICE_MANAGER_H
