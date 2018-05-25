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
char* sqlcon_add_device::enumTochar(device_type type) {
    /*因为devicedata结构体里设备类型是自定义的enum类型，无法存入数据库，最好转换成字符串存入数据库*/
    char *dtype;
    switch (type)
    {
        case REST:
            char temp[]="REST";
            dtype=new char[5];
            strcpy(dtype,temp);
            dtype[4]='\0';
        case OPC_UA:
            char temp1[]="OPC_UA";
            dtype=new char[7];
            strcpy(dtype,temp1);
            dtype[6]='\0';
        case MODBUS:
            char temp2[]="MODBUS";
            dtype=new char[7];
            strcpy(dtype,temp2);
            dtype[6]='\0';
        case DIDO:
            char temp3[]="DIDO";
            dtype=new char[5];
            strcpy(dtype,temp3);
            dtype[4]='\0';
        case MQTT:
            char temp4[]="MQTT";
            dtype=new char[5];
            strcpy(dtype,temp4);
            dtype[4]='\0';
        case ISA100:
            char temp5[]="ISA100";
            dtype=new char[7];
            strcpy(dtype,temp5);
            dtype[6]='\0';
        case BACNET:
            char temp6[]="BACNET";
            dtype=new char[7];
            strcpy(dtype,temp6);
            dtype[6]='\0';
        case ULE:
            char temp7[]="ULE";
            dtype=new char[4];
            strcpy(dtype,temp7);
            dtype[3]='\0';
        case BLE:
            char temp8[]="BLE";
            dtype=new char[4];
            strcpy(dtype,temp8);
            dtype[3]='\0';
        case ENOCEAN:
            char temp9[]="ENOCEAN";
            dtype=new char[8];
            strcpy(dtype,temp9);
            dtype[7]='\0';
        default:
            char temp10[]="NONE";
            dtype=new char[5];
            strcpy(dtype,temp10);
            dtype[4]='\0';
    }
    return dtype;
}
device_type sqlcon_add_device::charToenum(char *str) {
    if(strcmp(str,"REST")==0)
        return REST;
    if(strcmp(str,"OPC_UA")==0)
        return OPC_UA;
    if(strcmp(str,"MODBUS")==0)
        return MODBUS;
    if(strcmp(str,"DIDO")==0)
        return DIDO;
    if(strcmp(str,"MQTT")==0)
        return MQTT;
    if(strcmp(str,"ISA100")==0)
        return ISA100;
    if(strcmp(str,"BACNET")==0)
        return BACNET;
    if(strcmp(str,"ULE")==0)
        return ULE;
    if(strcmp(str,"BLE")==0)
        return BLE;
    if(strcmp(str,"ENOCEAN")==0)
        return ENOCEAN;
    if(strcmp(str,"NONE")==0)
        return NONE ;
    return NONE;
}
void sqlcon_add_device::insert_sql(devicedata *data,int n) {
    connect_sql();
    for(int i=0;i<n;i++)
    {
        char * dtype=enumTochar(data->type);
        char sql_insert[250];
        sprintf(sql_insert,"insert into %s(id,type,location,path)values('%d',%s,%s,%s)",table_name,data[i].id,dtype,data[i].devicelocation,data[i].path);
        int res=mysql_query(conn,sql_insert);
        if(!res)
        {
            cout<<"insert success."<<endl;
        }
        else
        {
            cout<<"insert failed."<<endl;
        }
    }
    mysql_close(conn);
}
devicedata sqlcon_add_device::search_sql(unsigned int id) {
    connect_sql();
    devicedata data;
    data.id=id;
    char sql_search[200];
    sprintf(sql_search,"select type,location,path from %s where id=%d",table_name,id);
    MYSQL_RES * reasult;
    MYSQL_ROW row;
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
                data.type=charToenum(row[0]);
                data.devicelocation=row[1];
                data.path=row[2];
            }
            return data;
        }

    } else{
        cout<<"search failed."<<endl;
        exit(1);
    }
}
void sqlcon_add_device::update_sql(unsigned int id, char *type, char *location, char *path) {
    connect_sql();
    char sql_update[200];
    sprintf(sql_update,"update %s set type=%s,location=%s,path=%s where id=%d",table_name,type,location,path,id);
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
void sqlcon_add_device::delete_sql(unsigned int id) {
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
}