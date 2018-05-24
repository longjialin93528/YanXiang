//
// Created by long on 2018/5/21.
//

#ifndef YANXIANG_SQLCON_BASE_H
#define YANXIANG_SQLCON_BASE_H
/*编译时加  `mysql_config --cflags --libs`   */
#include <mysql/mysql.h>
#include <cstring>
using namespace std;
class sqlcon_base
{
protected:
    MYSQL * conn;
    char *host;
    char *user;
    char *pd;
    char *dbname;
public:
    sqlcon_base();
    sqlcon_base(char *ht, char *usr, char *pad, char *name);
    virtual ~sqlcon_base();
    virtual void * search_sql(void * data)=0;
    virtual void insert_sql(void *data)=0;
    virtual void update_sql(void *data)=0;
};
#endif //YANXIANG_SQLCON_BASE_H
