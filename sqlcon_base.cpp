//
// Created by long on 2018/5/24.
//

#include "sqlcon_base.h"
#include <iostream>
sqlcon_base::sqlcon_base() {
    conn=new MYSQL();
    mysql_init(conn);

    char ht[]="localhost";
    char usr[]="root";
    char pad[]="123456";
    char name[]="yxdb";

    host=new char[10];
    strcpy(host,ht);
    host[9]='\0';

    user=new char[5];
    strcpy(user,usr);
    user[4]='\0';

    pd=new char[7];
    strcpy(pd,pad);
    pd[6]='\0';

    dbname=new char[5];
    strcpy(dbname,name);
    dbname[4]='\0';
}
sqlcon_base::sqlcon_base(char *ht, char *usr, char *pad, char *name) {
    conn=new MYSQL();
    mysql_init(conn);

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
sqlcon_base::~sqlcon_base() {
    if(conn!= NULL){
        delete conn;
    }
    if(host!=NULL)
    {
        delete host;
    }
    if(user!=NULL)
    {
        delete user;
    }
    if(pd!=NULL)
    {
        delete pd;
    }
    if(dbname!=NULL)
    {
        delete dbname;
    }
}
MYSQL* sqlcon_base::get_conn() {
    return conn;
}
void sqlcon_base::connect_sql() {
    if(mysql_real_connect(conn,host,user,pd,dbname,0,NULL,0))
    {
        cout<<"connect success."<<endl;
    }
    else
    {
        cout<<"connect failed."<<endl;
    }
}