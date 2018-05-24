//
// Created by long on 2018/5/21.
//

#ifndef YANXIANG_SQLCON_MODBUS_H
#define YANXIANG_SQLCON_MODBUS_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "sqlcon_base.h"
#include "value_type.h"
using namespace std;
class sqlcon_modbus:public sqlcon_base
{
private:
    char *host;
    char *user;
    char *pd;
    char *dbname;
public:
    sqlcon_modbus();
    sqlcon_modbus(char * ht,char * usr,char * pad,char * name);
    ~sqlcon_modbus();
    void connect_sql(MYSQL * conn,char * host,char * user,char * pd,char * tbname);
    void connect_sql();
    /*search函数要考虑多种搜索条件,例如只给id，查温度，湿度，或者查温度或者湿度的情况*/
    /*此时暂时写根据id查温湿度的情形*/
    search_id_reasult search_sql(unsigned int id);
    void insert_sql(modbusdata *data);
    void update_sql(unsigned int id,double temperature,double humidity);
    void delete_sql(unsigned int id);
};
#endif //YANXIANG_SQLCON_MODBUS_H
