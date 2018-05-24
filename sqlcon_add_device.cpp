//
// Created by long on 2018/5/24.
//

#include "sqlcon_add_device.h"
sqlcon_add_device::sqlcon_add_device() {
    char name[]="device_info";
    table_name=new char[strlen(name)+1];
    strcpy(table_name,name);
    table_name[strlen(name)]='\0';
}
sqlcon_add_device::sqlcon_add_device(char *tbname) {
    table_name=new char[strlen(tbname)+1];
    strcpy(table_name,tbname);
    table_name[strlen(tbname)]='\0';
}
sqlcon_add_device::~sqlcon_add_device() {
    if(table_name!=NULL)
    {
        delete table_name;
    }
}
void sqlcon_add_device::connect_sql() {
    if(mysql_real_connect(conn,host,user,pd,dbname,0,NULL,0))
    {
        cout<<"connect success."<<endl;
    }
    else
    {
        cout<<"connect failed."<<endl;
    }
}
