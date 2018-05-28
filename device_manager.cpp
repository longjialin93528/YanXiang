//
// Created by long on 2018/5/25.
//
#include "device_manager.h"
device_manager::device_manager() {
    addDevice_ptr=NULL;
}
device_manager::device_manager(char *tbname) {
    addDevice_ptr=new sqlcon_add_device(tbname);
}
device_manager::~device_manager() {
    if(addDevice_ptr!=NULL)
    {
        delete addDevice_ptr;
    }
}
Base_device* device_manager::chooseToCreate(MYSQL_ROW row) {
    Base_device * ptr_baseDevice=NULL;
    if(strcmp(row[1],"MODBUS")==0)
    {
        int id= static_cast<int>(row[0]);
        ptr_baseDevice=new Modbus_device(id,row[3]);
        return ptr_baseDevice;
    }
    /*这里要写入多种判断情形，因为设备不止一种，有不同的构造函数*/
}
void device_manager::addDeviceToList() {
    addDevice_ptr->connect_sql();
    char sql_search[200];
    /*这里是选出设备数据库中所有记录*/
    sprintf(sql_search,"select id,type,location,path from %s",addDevice_ptr->get_tbname());
    MYSQL_RES * reasult;
    MYSQL_ROW row;
    int res=mysql_query(addDevice_ptr->get_conn(),sql_search);
    if(!res)
    {
        cout<<"search success."<<endl;
        if((reasult=mysql_store_result(addDevice_ptr->get_conn()))==NULL)
        {
            fprintf(stderr,"can't store search reasult int reasult set.");
            exit(1);
        }
        else
        {
            while((row=mysql_fetch_row(reasult))!=NULL)/*开始遍历每一行设备*/
            {
                int tempnum= static_cast<int>(row[0]);
                if(find_Device.find(tempnum)!=find_Device.end())
                {
                    continue;
                }
                else
                {
                    find_Device.insert(pair<int,int>(tempnum,1));//这里的1用于下面run函数的判断，判断是否是新添加设备
                    Base_device * ptr_Device=chooseToCreate(row);
                    device_list.push_back(ptr_Device);
                }
            }

        }

    } else{
        cout<<"search failed."<<endl;
        exit(1);
    }
}
void device_manager::run() {
    while(1)
    {
        addDeviceToList();
        sleep(1);
        for(int i=0;i<device_list.size();i++)
        {
            if(find_Device[device_list[i]->get_deviceID()]==1)//如果一个设备刚添加进设备列表，那么其find_Device中对应的<key,value>中的value值一定是1，因为
            {
                find_Device[device_list[i]->get_deviceID()]=2;//新设备识别过一次后，将其value值置为2
                device_list[i]->run();
                device_list[i]->insert();
            }
            else
            {
                device_list[i]->run();
                device_list[i]->update();
            }
            sleep(1);
        }
    }
}
