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
    device_type charToenum(char *str);
    char * enumTochar(device_type type);
public:
    sqlcon_add_device();
    explicit sqlcon_add_device(char * tbname);
    ~sqlcon_add_device();
    char * get_tbname();
    devicedata search_sql(unsigned int id);
    void insert_sql(devicedata *data,int n);
    void update_sql(unsigned int id,char * type,char * location,char * path);
    void delete_sql(unsigned int id);
};
#endif //YANXIANG_SQLCON_ADD_DEVICE_H
