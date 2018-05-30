//
// Created by long on 2018/5/30.
//

#include "device_dido.h"
#include<fcntl.h>
#include<termios.h>
#include<cstdio>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
Modbus_device_dido::Modbus_device_dido() {
    di1=0;
    di2=0;
    di3=0;
    di4=0;
    di5=0;
    di6=0;
    di7=0;
    di8=0;
    device_path=NULL;
    rd_cmd=NULL;
    ptr_sqlcon_dido=NULL;
}
Modbus_device_dido::Modbus_device_dido(unsigned int id, char *path) {
    /*借用基类的构造函数同时赋值id与address*/
    set_deviceID(id);
    set_deviceType(DIDO);

    /*创建modbus连接数据库对象，由于在modbus_device构造类里，所以给其直接传入modbus数据库表名字mb_sensor*/
    ptr_sqlcon_dido=new sqlcon_dido("dido_sensor");
    di1=0;
    di2=0;
    di3=0;
    di4=0;
    di5=0;
    di6=0;
    di7=0;
    di8=0;

    //这里是孙文峰的函数
    set_rd_cmd(rd_cmd,id);

    /*深度copy地址值*/
    device_path=new char[strlen(path)+1];
    strcpy(device_path,path);
    device_path[strlen(path)]='\0';
}
Modbus_device_dido::~Modbus_device_dido() {
    if(rd_cmd!= NULL)
    {
        delete rd_cmd;
    }
    if(device_path!=NULL)
    {
        delete device_path;
    }
    if(ptr_sqlcon_dido!=NULL)
    {
        delete ptr_sqlcon_dido;
    }
}
/*私有函数的声明，主要服务于内部函数的实现*/
void Modbus_device_dido::InvertUint8(unsigned char *dBuf, unsigned char *srcBuf) {
    int i;
    unsigned char tmp[4];
    tmp[0] = 0;
    for (i = 0; i< 8; i++)
    {
        if (srcBuf[0] & (1 << i))
            tmp[0] |= 1 << (7 - i);
    }
    dBuf[0] = tmp[0];
}
void Modbus_device_dido::InvertUint16(unsigned short *dBuf, unsigned short *srcBuf) {
    int i;
    unsigned short tmp[4];
    tmp[0] = 0;
    for (i = 0; i< 16; i++)
    {
        if (srcBuf[0] & (1 << i))
            tmp[0] |= 1 << (15 - i);
    }
    dBuf[0] = tmp[0];
}
unsigned short Modbus_device_dido::CRC16_MODBUS(unsigned char *puchMsg, unsigned int usDataLen) {
    unsigned short wCRCin = 0xFFFF;
    unsigned short wCPoly = 0x8005;
    unsigned char wChar = 0;

    while (usDataLen--)
    {
        wChar = *(puchMsg++);
        InvertUint8(&wChar, &wChar);
        wCRCin ^= (wChar << 8);
        for (int i = 0; i < 8; i++)
        {
            if (wCRCin & 0x8000)
                wCRCin = (wCRCin << 1) ^ wCPoly;
            else
                wCRCin = wCRCin << 1;
        }
    }
    InvertUint16(&wCRCin, &wCRCin);
    return (wCRCin);
}
void Modbus_device_dido::set_rd_cmd(unsigned char *rd_cmd, unsigned int id) {
    char tmp[5];
    sprintf(tmp,"%02x", id);
//	cout << tmp << endl;

    sscanf(tmp, "%02x", &rd_cmd[0]);

    //printf("%02x\n", rd_cmd[0]);

    rd_cmd[1] = 0x01;
    rd_cmd[2] = 0x00;
    rd_cmd[3] = 0x00;
    rd_cmd[4] = 0x00;
    rd_cmd[5] = 0x08;

    int result = CRC16_MODBUS((unsigned char *)rd_cmd, 6);

    char tmp1[10];
    //cout << result << endl;
    sprintf(tmp1, "%04x", result);
    //cout << tmp1 << endl;

    sscanf(tmp1, "%02x", &rd_cmd[6]);
    sscanf(tmp1+2, "%02x", &rd_cmd[7]);
    char ch;
    ch=rd_cmd[7];
    rd_cmd[7]=rd_cmd[6];
    rd_cmd[6]=ch;
}
/*可供外部调用的共有函数声明*/
void Modbus_device_dido::update() {
    unsigned int id=get_deviceID();
    didodata res;
    res.id=get_deviceID();
    res.address=get_deviceID();
    res.di1=di1;
    res.di2=di2;
    res.di3=di3;
    res.di4=di4;
    res.di5=di5;
    res.di6=di6;
    res.di7=di7;
    res.di8=di8;
    ptr_sqlcon_dido->update_sql(id,res);
}
void Modbus_device_dido::insert() {
    didodata res;
    res.id=get_deviceID();
    res.address=get_deviceID();
    res.di1=di1;
    res.di2=di2;
    res.di3=di3;
    res.di4=di4;
    res.di5=di5;
    res.di6=di6;
    res.di7=di7;
    res.di8=di8;
    ptr_sqlcon_dido->insert_sql(&res);
}
didodata Modbus_device_dido::get_dido(char a) {
    didodata res;
    res.id=deviceID;
    res.address=deviceID;
    unsigned char flag=0x01;
    if(a&flag)
    {
        res.di1=1;
    }
    else
    {
        res.di1=0;
    }
    flag=flag<<1;
    if(a&flag)
    {
        res.di2=1;
    }
    else
    {
        res.di2=0;
    }
    flag=flag<<1;
    if(a&flag)
    {
        res.di3=1;
    }
    else
    {
        res.di3=0;
    }
    flag=flag<<1;
    if(a&flag)
    {
        res.di4=1;
    }
    else
    {
        res.di4=0;
    }
    flag=flag<<1;
    if(a&flag)
    {
        res.di5=1;
    }
    else
    {
        res.di5=0;
    }
    flag=flag<<1;
    if(a&flag)
    {
        res.di6=1;
    }
    else
    {
        res.di6=0;
    }
    flag=flag<<1;
    if(a&flag)
    {
        res.di7=1;
    }
    else
    {
        res.di7=0;
    }
    flag=flag<<1;
    if(a&flag)
    {
        res.di8=1;
    }
    else
    {
        res.di8=0;
    }
    return res;
}
void Modbus_device_dido::show_dido() {
    cout<<"Modbus DIDO Device "<<get_deviceID()<<"com1 is "<<di1<<endl;
    cout<<"Modbus DIDO Device "<<get_deviceID()<<"com2 is "<<di2<<endl;
    cout<<"Modbus DIDO Device "<<get_deviceID()<<"com3 is "<<di3<<endl;
    cout<<"Modbus DIDO Device "<<get_deviceID()<<"com4 is "<<di4<<endl;
    cout<<"Modbus DIDO Device "<<get_deviceID()<<"com5 is "<<di5<<endl;
    cout<<"Modbus DIDO Device "<<get_deviceID()<<"com6 is "<<di6<<endl;
    cout<<"Modbus DIDO Device "<<get_deviceID()<<"com7 is "<<di7<<endl;
    cout<<"Modbus DIDO Device "<<get_deviceID()<<"com8 is "<<di8<<endl;
}
void Modbus_device_dido::run() {
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

    options.c_cflag |=B9600 | CLOCAL | CREAD;//波特率 本地连接 接受使能
    options.c_cflag |=CS8;//数据位8位
    options.c_cflag &=~CSTOPB;//停止位1位
    options.c_cflag &=~PARENB;//

    tcflush(fd,TCIFLUSH);
    if((tcsetattr(fd,TCSANOW,&options))!=0)
    {
        printf("Com set error!\n");
        return ;
    }
    char buf[6];
    memset(buf,0,6);
    ssize_t wr_num=write(fd,rd_cmd,8);
    sleep(1);
    ssize_t rd_num=read(fd,buf,6);
    didodata res=get_dido(buf[3]);
    di1=res.di1;
    di2=res.di2;
    di3=res.di3;
    di4=res.di4;
    di5=res.di5;
    di6=res.di6;
    di7=res.di7;
    di8=res.di8;
    close(fd);
}