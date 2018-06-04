//
// Created by long on 2018/6/4.
//

#ifndef YANXIANG_SQLCON_MODBUS_TH_H
#define YANXIANG_SQLCON_MODBUS_TH_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "sqlcon_base.h"
#include "value_type.h"
using namespace std;
class sqlcon_modbus_th:public sqlcon_base
{
private:
    char *table_name;
public:
    sqlcon_modbus_th();
    sqlcon_modbus_th(char * ht,char * usr,char * pad,char * name,char *tbname);
    sqlcon_modbus_th(char *tbname);
    ~sqlcon_modbus_th();
    /*search函数要考虑多种搜索条件,例如只给id，查温度，湿度，或者查温度或者湿度的情况*/
    /*此时暂时写根据id查温湿度的情形*/
    modbusdata search_sql(unsigned int id);
    void insert_sql(modbusdata *data);
    void update_sql(unsigned int id,double temperature,double humidity);
    void delete_sql(unsigned int id);
};
#endif //YANXIANG_SQLCON_MODBUS_TH_H
