//
// Created by long on 2018/5/21.
//

#ifndef YANXIANG_SQLCON_BASE_H
#define YANXIANG_SQLCON_BASE_H
/*编译时加  `mysql_config --cflags --libs`   */
#include <mysql/mysql.h>
using namespace std;
class sqlcon_base
{
protected:
    MYSQL * conn;
public:
    sqlcon_base(){
        conn=new MYSQL();
        mysql_init(conn);
    };
    virtual ~sqlcon_base(){
        if(conn!= NULL){
            delete conn;
        }
    };
    virtual void * search_sql(void * data)=0;
    virtual void insert_sql(void *data)=0;
    virtual void update_sql(void *data)=0;
};
#endif //YANXIANG_SQLCON_BASE_H
