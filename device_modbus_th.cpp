//
// Created by long on 2018/6/4.
//

#include "device_modbus_th.h"
#include<fcntl.h>
#include<termios.h>
#include<cstdio>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include <cmath>
using namespace std;
Modbus_device_th::Modbus_device_th() {
    temperature=0.0;
    humidity=0.0;
    set_deviceType(MODBUS_TH);
    ptr_sqlcon_modbus=NULL;
}
Modbus_device_th::Modbus_device_th(unsigned int id,char *path) {
    /*借用基类的构造函数同时赋值id与address*/
    set_deviceID(id);
    set_deviceType(MODBUS_TH);

    /*创建modbus连接数据库对象，由于在modbus_device构造类里，所以给其直接传入modbus数据库表名字mb_sensor*/
    ptr_sqlcon_modbus=new sqlcon_modbus_th("mb_sensor");

    temperature=0.0;
    humidity=0.0;
    rd_cmd=new unsigned char[8];

    //这里是孙文峰的函数
    set_rd_cmd(rd_cmd,id);

    /*深度copy地址值*/
    device_path=new char[strlen(path)+1];
    strcpy(device_path,path);
    device_path[strlen(path)]='\0';
}
Modbus_device_th::~Modbus_device_th() {
    if(ptr_sqlcon_modbus!=NULL)
    {
        delete ptr_sqlcon_modbus;
    }
}
/*私有函数的声明，主要服务于内部函数的实现*/
bool Modbus_device_th::is_fullone(char a) {
    unsigned char flag=0x01;
    bool res=1;
    int i;
    for(i=7;i>=0;i--)
    {
        if(!(flag&a))
        {
            res=0;
            return  res;
        }
        flag=flag<<1;
    }
    return res;
}
double Modbus_device_th::func(int *a, int n) {
    int i;
    double res=0.0;
    for(i=0;i<n;i++)
    {
        res+=pow(2*a[i],n-i-1);
    }
    return res/10;
}
void Modbus_device_th::set_rd_cmd(unsigned char *rd_cmd, unsigned int id) {
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
/*可供外部调用的共有函数声明*/
double Modbus_device_th::get_temperature(char a,char b) {
    double temperature=0.0;
    int c[9]={0};
    int i;
    unsigned char flag=0x01;
    if(is_fullone(a))
    {
        for(i=8;i>=1;i--)//小于0补码取反的过程
        {
            if(flag&b)
            {
                c[i]=0;
            }
            else
            {
                c[i]=1;
            }
            flag=flag<<1;
        }
        c[8]=c[8]+1;
        for(i=8;i>=0;i--)//加一的过程
        {
            if(c[i]>=2)
            {
                c[i-1]=c[i-1]+1;
                c[i]=c[i]%2;
            }
        }
        temperature=-func(c,9);
    }
    else
    {
        for(i=0;i<8;i++)
        {
            if(flag&b)
            {
                c[i]=1;
            }
            flag=flag<<1;
        }
        temperature=func(c,9);
    }
    return temperature;
}
double Modbus_device_th::get_humidity(char a, char b) {
    int i;
    int c[16]={0};
    unsigned char flag=0x01;
    for(i=15;i>7;i--)
    {
        if(flag&b)
        {
            c[i]=1;
        }
        flag=flag<<1;
    }
    flag=0x01;
    double humidity=0.0;
    for(i=7;i>=0;i--)
    {
        if(flag&a)
        {
            c[i]=1;
        }
        flag=flag<<1;
    }
    humidity=func(c,16);
    return humidity;
}
void Modbus_device_th::update() {
    unsigned int id=get_deviceID();
    ptr_sqlcon_modbus->update_sql(id,temperature,humidity);
}
void Modbus_device_th::insert() {
    modbusdata data;
    data.id=get_deviceID();
    data.address=get_deviceID();
    data.temperature=temperature;
    data.humidity=humidity;
    ptr_sqlcon_modbus->insert_sql(&data);
}
void Modbus_device_th::show_temperature() {
    std::cout<<"Modbus Device "<<get_deviceID()<<" temperature is "<<temperature<<std::endl;
}
void Modbus_device_th::show_humidity() {
    std::cout<<"Modbus Device "<<get_deviceID()<<" humidity is "<<humidity<<std::endl;
}
void Modbus_device_th::run() {
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
    temperature=get_temperature(buf[5],buf[6]);
    humidity=get_humidity(buf[3],buf[4]);
    close(fd);
}