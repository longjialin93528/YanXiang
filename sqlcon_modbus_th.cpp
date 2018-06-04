//
// Created by long on 2018/6/4.
//

#include "sqlcon_modbus_th.h"
sqlcon_modbus_th::sqlcon_modbus_th() {
    table_name=NULL;
}
sqlcon_modbus_th::sqlcon_modbus_th(char *ht, char *usr, char *pad, char *name,char * tbname) {
    sqlcon_base(ht,usr,pad,name);
    table_name=new char[strlen(tbname)+1];
    strcpy(table_name,tbname);
    table_name[strlen(tbname)]='\0';
}
sqlcon_modbus_th::sqlcon_modbus_th(char *tbname) {
    table_name=new char[strlen(tbname)+1];
    strcpy(table_name,tbname);
    table_name[strlen(tbname)]='\0';
}
sqlcon_modbus_th::~sqlcon_modbus_th() {
    if(table_name!=NULL)
    {
        delete table_name;
    }
}
void sqlcon_modbus_th::insert_sql(modbusdata *data) {
    connect_sql();
    char sql_insert[250];
    sprintf(sql_insert,"insert into %s(id,address,temperature,humidity)values('%d','%d','%lf','%lf')",table_name,data->id,data->address,data->temperature,data->humidity);
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
void sqlcon_modbus_th::update_sql(unsigned int id,double temperature,double humidity) {
    connect_sql();
    char sql_update[200];
    sprintf(sql_update,"update %s set temperature=%lf,humidity=%lf where id=%d",table_name,temperature,humidity,id);
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
modbusdata sqlcon_modbus_th::search_sql(unsigned int id) {
    connect_sql();
    modbusdata id_reasult;
    id_reasult.id=id;
    id_reasult.address=id;
    /*对于数据库查询搜索到的结果集进行操作详见以下网址介绍*/
    /* https://www.cnblogs.com/uolo/p/6115448.html */
    /* http://www.w3school.com.cn/sql/sql_select.asp */
    char sql_search[200];
    sprintf(sql_search,"select temperature,humidity from %s where id=%d",table_name,id);
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
            mysql_close(conn);
            return id_reasult;
        }
    }
    else
    {
        cout<<"sqlcon_modbus search failed."<<endl;
        exit(1);
    }
}
void sqlcon_modbus_th::delete_sql(unsigned int id) {
    connect_sql();
    char sql_delete[200];
    sprintf(sql_delete,"delete from %s where id=%d",table_name,id);
    int res=mysql_query(conn,sql_delete);
    if(!res)
    {
        cout<<"delete success."<<endl;
    }
    else
    {
        cout<<"delete failed."<<endl;
    }
    mysql_close(conn);
}