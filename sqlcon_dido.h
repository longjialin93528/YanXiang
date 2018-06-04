//
// Created by long on 2018/5/30.
//

#ifndef YANXIANG_SQLCON_DIDO_H
#define YANXIANG_SQLCON_DIDO_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "sqlcon_base.h"
#include "value_type.h"
using namespace std;
class sqlcon_dido:public sqlcon_base
{
private:
    char *table_name;
public:
    sqlcon_dido();
    sqlcon_dido(char * ht,char * usr,char * pad,char * name,char *tbname);
    sqlcon_dido(char *tbname);
    ~sqlcon_dido();
    /*search函数可以重载以满足不同搜索条件*/
    didodata search_sql(unsigned int id);
    void insert_sql(didodata * data);
    void update_sql(unsigned int id, didodata data);
    void delete_sql(unsigned int id);
};
#endif //YANXIANG_SQLCON_DIDO_H
