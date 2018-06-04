//
// Created by long on 2018/5/30.
//

#include "sqlcon_dido.h"
sqlcon_dido::sqlcon_dido() {
    table_name=NULL;
}
sqlcon_dido::sqlcon_dido(char *ht, char *usr, char *pad, char *name, char *tbname) {
    sqlcon_base(ht,usr,pad,name);
    table_name=new char[strlen(tbname)+1];
    strcpy(table_name,tbname);
    table_name[strlen(tbname)]='\0';
}
sqlcon_dido::sqlcon_dido(char *tbname) {
    table_name=new char[strlen(tbname)+1];
    strcpy(table_name,tbname);
    table_name[strlen(tbname)]='\0';
}
sqlcon_dido::~sqlcon_dido() {
    if(table_name!=NULL)
    {
        delete table_name;
    }
}
void sqlcon_dido::insert_sql(didodata *data) {
    connect_sql();
    char sql_insert[300];
    sprintf(sql_insert,"insert into %s(id,address,di1,di2,di3,di4,di5,di6,di7,di8)values('%d','%d','%d','%d','%d','%d','%d','%d','%d','%d')",table_name,data->id,data->address,data->di1,data->di2,data->di3,data->di4,data->di5,data->di6,data->di7,data->di8);
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
void sqlcon_dido::update_sql(unsigned int id, didodata data) {
    connect_sql();
    char sql_update[300];
    sprintf(sql_update,"update %s set di1=%d,di2=%d,di3=%d,di4=%d,di5=%d,di6=%d,di7=%d,di8=%d where id=%d",table_name,data.di1,data.di2,data.di3,data.di4,data.di5,data.di6,data.di7,data.di8,id);
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
didodata sqlcon_dido::search_sql(unsigned int id) {
    connect_sql();
    didodata id_reasult;
    id_reasult.id=id;
    id_reasult.address=id;
    /*对于数据库查询搜索到的结果集进行操作详见以下网址介绍*/
    /* https://www.cnblogs.com/uolo/p/6115448.html */
    /* http://www.w3school.com.cn/sql/sql_select.asp */
    char sql_search[300];
    sprintf(sql_search,"select di1,di2,di3,di4,di5,di6,di7,di8 from %s where id=%d",table_name,id);
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
                id_reasult.di1=(unsigned int)atoi(row[0]);//row[0]结果是字符串，用atof函数进行转换
                id_reasult.di2=(unsigned int)atoi(row[1]);
                id_reasult.di3=(unsigned int)atoi(row[2]);
                id_reasult.di4=(unsigned int)atoi(row[3]);
                id_reasult.di5=(unsigned int)atoi(row[4]);
                id_reasult.di6=(unsigned int)atoi(row[5]);
                id_reasult.di7=(unsigned int)atoi(row[6]);
                id_reasult.di8=(unsigned int)atoi(row[7]);
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
void sqlcon_dido::delete_sql(unsigned int id) {
    connect_sql();
    char sql_delete[100];
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