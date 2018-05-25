//
// Created by long on 2018/5/18.
//
#include "device_modbus.h"
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
Modbus_device::Modbus_device() {
    temperature=0.0;
    humidity=0.0;
    set_deviceType(MODBUS);
    rd_cmd=NULL;
    device_path=NULL;
}
Modbus_device::Modbus_device(unsigned int id,char *path) {
    /*借用基类的构造函数同时赋值id与address*/
    set_deviceID(id);
    set_deviceType(MODBUS);

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
Modbus_device::~Modbus_device() {
    if(rd_cmd!= NULL)
    {
        delete rd_cmd;
    }
    if(device_path!=NULL)
    {
        delete device_path;
    }
}
/*私有函数的声明，主要服务于内部函数的实现*/
bool Modbus_device::is_fullone(char a) {
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
double Modbus_device::func(int *a, int n) {
    int i;
    double res=0.0;
    for(i=0;i<n;i++)
    {
        res+=pow(2*a[i],n-i-1);
    }
    return res/10;
}
void Modbus_device::InvertUint8(unsigned char *dBuf, unsigned char *srcBuf) {
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
void Modbus_device::InvertUint16(unsigned short *dBuf, unsigned short *srcBuf) {
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
unsigned short Modbus_device::CRC16_MODBUS(unsigned char *puchMsg, unsigned int usDataLen) {
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
void Modbus_device::set_rd_cmd(unsigned char *rd_cmd, unsigned int id) {
    char tmp[5];
    sprintf(tmp,"%02x", id);
//	cout << tmp << endl;

    sscanf(tmp, "%02x", &rd_cmd[0]);

    //printf("%02x\n", rd_cmd[0]);

    rd_cmd[1] = 0x03;
    rd_cmd[2] = 0x00;
    rd_cmd[3] = 0x00;
    rd_cmd[4] = 0x00;
    rd_cmd[5] = 0x02;

    int result = CRC16_MODBUS((unsigned char *)rd_cmd, 6);

    char tmp1[10];
    cout << result << endl;
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
double Modbus_device::get_temperature(char a,char b) {
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
double Modbus_device::get_humidity(char a, char b) {
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
void Modbus_device::set_rd_cmd() {
    rd_cmd=new unsigned char[8];
    rd_cmd[0]=0x01;
    rd_cmd[1]=0x03;
    rd_cmd[2]=0x00;
    rd_cmd[3]=0x00;
    rd_cmd[4]=0x00;
    rd_cmd[5]=0x02;
    rd_cmd[6]=0xc4;
    rd_cmd[7]=0x0b;
}
void Modbus_device::show_temperature() {
    std::cout<<"Modbus Device "<<get_deviceID()<<" temperature is "<<temperature<<std::endl;
}
void Modbus_device::show_humidity() {
    std::cout<<"Modbus Device "<<get_deviceID()<<" humidity is "<<humidity<<std::endl;
}
void Modbus_device::run() {
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
    set_rd_cmd();

    ssize_t wr_num=write(fd,rd_cmd,8);
    sleep(1);
    ssize_t rd_num=read(fd,buf,9);
    temperature=get_temperature(buf[5],buf[6]);
    humidity=get_humidity(buf[3],buf[4]);
    close(fd);
}