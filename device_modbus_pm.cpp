//
// Created by long on 2018/5/30.
//

#include "device_modbus_pm.h"
#include<fcntl.h>
#include<termios.h>
#include<cstdio>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
Modbus_device_pm::Modbus_device_pm() {
    PM2=0;
    PM10=0;
    set_deviceType(MODBUS_PM);
    ptr_sqlcon_modbus_pm=NULL;
}
Modbus_device_pm::Modbus_device_pm(unsigned int id, char *path) {
    /*借用基类的构造函数同时赋值id与address*/
    set_deviceID(id);
    set_deviceType(MODBUS_PM);

    /*创建modbus连接数据库对象，由于在modbus_device构造类里，所以给其直接传入modbus数据库表名字mb_sensor*/
    ptr_sqlcon_modbus_pm=new sqlcon_modbus_pm("mbpm_sensor");

    PM2=0;
    PM10=0;
    rd_cmd=new unsigned char[8];

    //这里是孙文峰的函数
    set_rd_cmd(rd_cmd,id);

    /*深度copy地址值*/
    device_path=new char[strlen(path)+1];
    strcpy(device_path,path);
    device_path[strlen(path)]='\0';
}
Modbus_device_pm::~Modbus_device_pm() {
    if(ptr_sqlcon_modbus_pm!=NULL)
    {
        delete ptr_sqlcon_modbus_pm;
    }
}
/*私有函数的声明，主要服务于内部函数的实现*/
void Modbus_device_pm::set_rd_cmd(unsigned char *rd_cmd, unsigned int id) {
    char tmp[5];
    sprintf(tmp,"%02x", id);
    sscanf(tmp, "%02x", &rd_cmd[0]);

    rd_cmd[1] = 0x03;
    rd_cmd[2] = 0x00;
    rd_cmd[3] = 0x00;
    rd_cmd[4] = 0x00;
    rd_cmd[5] = 0x02;

    int result = CRC16_MODBUS((unsigned char *)rd_cmd, 6);

    char tmp1[10];

    sprintf(tmp1, "%04x", result);

    sscanf(tmp1, "%02x", &rd_cmd[6]);
    sscanf(tmp1+2, "%02x", &rd_cmd[7]);
    char ch;
    ch=rd_cmd[7];
    rd_cmd[7]=rd_cmd[6];
    rd_cmd[6]=ch;
}
/*私有函数的声明，主要服务于内部函数的实现*/
unsigned int Modbus_device_pm::my_pow(int n) {
    unsigned int res=1;
    for(int i=0;i<n;i++)
    {
        res=res*2;
    }
    return res;
}
unsigned int Modbus_device_pm::get_hec(int *str) {
    unsigned int sum=0;
    for(int i=0;i<16;i++)
    {
        sum+=str[i]*my_pow(15-i);
    }
    return sum;
}
/*可供外部调用的共有函数声明*/
unsigned int Modbus_device_pm::get_PM2(char a, char b) {
    unsigned int PM2=0;
    int c[16]={0};
    int i;
    unsigned char flag=0x01;
    for(i=15;i>=8;i--)
    {
        if(flag&b)
        {
            c[i]=1;
        }
        flag=flag<<1;
    }
    flag=0x01;
    for(i=7;i>=0;i--)
    {
        if(flag&a)
        {
            c[i]=1;
        }
        flag=flag<<1;
    }
    PM2=get_hec(c);
    return PM2;
}
unsigned int Modbus_device_pm::get_PM10(char a, char b) {
    unsigned int PM10=0;
    int c[16]={0};
    int i;
    unsigned char flag=0x01;
    for(i=15;i>=8;i--)
    {
        if(flag&b)
        {
            c[i]=1;
        }
        flag=flag<<1;
    }
    flag=0x01;
    for(i=7;i>=0;i--)
    {
        if(flag&a)
        {
            c[i]=1;
        }
        flag=flag<<1;
    }
    PM10=get_hec(c);
    return PM10;
}
void Modbus_device_pm::update() {
    unsigned int id=get_deviceID();
    ptr_sqlcon_modbus_pm->update_sql(id,PM2,PM10);
}
void Modbus_device_pm::insert() {
    modbusPMdata data;
    data.id=get_deviceID();
    data.address=get_deviceID();
    data.PM2=PM2;
    data.PM10=PM10;
    ptr_sqlcon_modbus_pm->insert_sql(&data);
}
void Modbus_device_pm::show_PM2() {
    std::cout<<"Modbus PM Device "<<get_deviceID()<<" PM2.5 is "<<PM2<<endl;
}
void Modbus_device_pm::show_PM10() {
    std::cout<<"Modbus PM Device "<<get_deviceID()<<" PM10 is "<<PM10<<endl;
}
void Modbus_device_pm::run() {
    /*串口打开部分*/
    int fd;
    fd=open(device_path,O_RDWR|O_NOCTTY|O_NDELAY);
    if(-1==fd)
    {
        perror(device_path);
    }

    /*串口参数设置部分*/
    struct termios options;//串口配置结构体
    tcgetattr(fd,&options);//获取串口原来的参数设置
    bzero(&options,sizeof(options));

    options.c_cflag |=B4800 | CLOCAL | CREAD;//波特率 本地连接 接受使能
    options.c_cflag |=CS8;//数据位8位
    options.c_cflag &=~CSTOPB;//停止位1位
    options.c_cflag &=~PARENB;//

    tcflush(fd,TCIFLUSH);
    if((tcsetattr(fd,TCSANOW,&options))!=0)
    {
        printf("Com set error!\n");
        return ;
    }

    char buf[9];
    memset(buf,0,9);
    ssize_t wr_num=write(fd,rd_cmd,8);
    sleep(1);
    ssize_t rd_num=read(fd,buf,9);
    PM2=get_PM2(buf[3],buf[4]);
    PM10=get_PM10(buf[5],buf[6]);
    close(fd);
}