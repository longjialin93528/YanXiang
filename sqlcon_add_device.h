//
// Created by long on 2018/5/24.
//

#ifndef YANXIANG_SQLCON_ADD_DEVICE_H
#define YANXIANG_SQLCON_ADD_DEVICE_H

#include <iostream>
#include "sqlcon_base.h"
#include "value_type.h"
class sqlcon_add_device:public sqlcon_base
{
private:
    char * table_name;
public:
    sqlcon_add_device();
    sqlcon_add_device(char * tbname);
    ~sqlcon_add_device();
    void connect_sql();
    devicedata search_sql(unsigned int id);
    void insert_sql(devicedata *data);
    void update_sql(unsigned int id,char * location,double humidity);
    void delete_sql(unsigned int id);
};
#endif //YANXIANG_SQLCON_ADD_DEVICE_H
