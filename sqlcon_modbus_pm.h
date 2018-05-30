//
// Created by long on 2018/5/30.
//

#ifndef YANXIANG_SQLCON_MODBUS_PM_H
#define YANXIANG_SQLCON_MODBUS_PM_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "sqlcon_base.h"
#include "value_type.h"
using namespace std;
class sqlcon_modbus_pm:public sqlcon_base
{
private:
    char *table_name;
public:
    sqlcon_modbus_pm();
    sqlcon_modbus_pm(char * ht,char * usr,char * pad,char * name,char *tbname);
    sqlcon_modbus_pm(char *tbname);
    ~sqlcon_modbus_pm();
    void connect_sql();
    /*search函数要考虑多种搜索条件,例如只给id，查PM2.5，PM10，或者查PM2.5及PM10的情况*/
    /*此时暂时写根据id查两种值的情形*/
    modbusPMdata search_sql(unsigned int id);
    void insert_sql(modbusPMdata *data);
    void update_sql(unsigned int id, unsigned int PM2 , unsigned int PM10);
    void delete_sql(unsigned int id);
};
#endif //YANXIANG_SQLCON_MODBUS_PM_H
