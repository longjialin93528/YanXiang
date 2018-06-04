//
// Created by long on 2018/5/25.
//

#ifndef YANXIANG_DEVICE_MANAGER_H
#define YANXIANG_DEVICE_MANAGER_H

#include "sqlcon_add_device.h"
#include "sqlcon_modbus_th.h"
#include "device_modbus_th.h"
#include "sqlcon_modbus_pm.h"
#include "device_modbus_pm.h"
#include "sqlcon_dido.h"
#include "device_dido.h"
#include <unistd.h>
#include <unordered_map>
#include <vector>
using namespace std;
class device_manager
{
private:
    sqlcon_add_device * addDevice_ptr;
    unordered_map<int,int> find_Device;
    vector<Base_device *> device_list;
    Base_device * chooseToCreate(MYSQL_ROW row);//依据查询设备数据库得到的设备类型，执行对应设备的构造函数
public:
    device_manager();
    explicit device_manager(char * tbname);
    ~device_manager();
    void addDeviceToList();//查询设备数据库,并将新设备更新到设备列表中
    void run();//run里首先执行上面的addDeviceToList函数（更新设备vector），然后遍历vector(执行对应的insert(新设备)或者update(已添加过的设备))
};
#endif //YANXIANG_DEVICE_MANAGER_H
