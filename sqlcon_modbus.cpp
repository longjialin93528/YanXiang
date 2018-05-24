//
// Created by long on 2018/5/21.
//
#include "sqlcon_modbus.h"
sqlcon_modbus::sqlcon_modbus() {
    host=NULL;
    user=NULL;
    pd=NULL;
    dbname=NULL;
}
sqlcon_modbus::sqlcon_modbus(char *ht, char *usr, char *pad, char *name) {
    size_t len;
    /*深度复制*/
    len=strlen(ht);
    host=new char[len+1];
    strcpy(host,ht);
    host[len]='\0';
    /*深度复制*/
    len=strlen(usr);
    user=new char[len+1];
    strcpy(user,usr);
    host[len]='\0';
    /*深度复制*/
    len=strlen(pad);
    pd=new char[len+1];
    strcpy(pd,pad);
    pd[len]='\0';
    /*深度复制*/
    len=strlen(name);
    dbname=new char[len+1];
    strcpy(dbname,name);
    dbname[len]='\0';
}
sqlcon_modbus::~sqlcon_modbus() {
    if(host!=NULL)
    {
        delete[] host;
    }
    if(user!=NULL)
    {
        delete[] user;
    }
    if(pd!=NULL)
    {
        delete[] pd;
    }
    if(dbname!=NULL)
    {
        delete[] dbname;
    }
}
void sqlcon_modbus::connect_sql(MYSQL *conn, char *host, char *user, char *pd, char *dbname) {
    if(mysql_real_connect(conn,host,user,pd,dbname,0,NULL,0))
    {
        cout<<"connect success."<<endl;
    }
    else
    {
        cout<<"connect failed."<<endl;
    }
}
void sqlcon_modbus::connect_sql() {
    if(mysql_real_connect(conn,"localhost","root","123456","yxdb",0,NULL,0))
    {
        cout<<"connect success."<<endl;
    }
    else
    {
        cout<<"connect failed."<<endl;
    }
}
void sqlcon_modbus::insert_sql(modbusdata *data) {
    connect_sql();
    char sql_insert[200];
    sprintf(sql_insert,"insert into mb_sensor(id,address,devicetype,temperature,humidity)values('%d','%d','MODBUS','%lf','%lf')",data->id,data->address,data->temperature,data->humidity);
    int res=mysql_query(conn,sql_insert);
    if(!res)
    {
        cout<<"insert success."<<endl;
    }
    else
    {
        cout<<"insert failed."<<endl;
    }
    mysql_close(conn);
}
void sqlcon_modbus::update_sql(unsigned int id,double temperature,double humidity) {
    connect_sql();
    char sql_update[200];
    sprintf(sql_update,"update mb_sensor set temperature=%lf,humidity=%lf where id=%d",temperature,humidity,id);
    int res=mysql_query(conn,sql_update);
    if(!res)
    {
        cout<<"update success."<<endl;
    }
    else
    {
        cout<<"update failed."<<endl;
    }
    mysql_close(conn);
}
search_id_reasult sqlcon_modbus::search_sql(unsigned int id) {
    connect_sql();
    search_id_reasult id_reasult;
    /*对于数据库查询搜索到的结果集进行操作详见以下网址介绍*/
    /* https://www.cnblogs.com/uolo/p/6115448.html */
    /* http://www.w3school.com.cn/sql/sql_select.asp */
    char sql_search[200];
    sprintf(sql_search,"select temperature,humidity from mb_sensor where id=%d",id);
    MYSQL_RES * reasult;//查询到的结果集
    MYSQL_ROW row;//结果集中的一行
    int res=mysql_query(conn,sql_search);
    if(!res)
    {
        cout<<"search success."<<endl;
        if((reasult=mysql_store_result(conn))==NULL)
        {
            fprintf(stderr,"can't store search reasult int reasult set.");
            exit(1);
        }
        else
        {
            while((row=mysql_fetch_row(reasult))!=NULL)/*一个id查询到的结果只有一行，没有很多行*/
            {
                id_reasult.temperature=atof(row[0]);//row[0]结果是字符串，用atof函数进行转换
                id_reasult.humidity=atof(row[1]);
            }
            return id_reasult;
        }
    }
    else
    {
        cout<<"search failed."<<endl;
        exit(1);
    }
}
void sqlcon_modbus::delete_sql(unsigned int id) {
    connect_sql();
    char sql_delete[200];
    sprintf(sql_delete,"delete from mb_sensor where id=%d",id);
    int res=mysql_query(conn,sql_delete);
    if(!res)
    {
        cout<<"delete success."<<endl;
    }
    else
    {
        cout<<"delete failed."<<endl;
    }
}