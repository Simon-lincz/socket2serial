#ifndef SERIAL_MODULE_H
#define SERIAL_MODULE_H

#include <stdio.h> /*标准输入输出定义*/ 
#include <stdlib.h>/*标准函数库定义*/ 
#include <unistd.h>/*Unix标准函数定义*/ 
#include <sys/types.h> /*linux系统的基本系统数据类型定义*/
#include <sys/signal.h>
#include <sys/stat.h> 
#include <fcntl.h> /*文件控制定义*/ 
#include <termios.h> /*PPSIX终端控制定义*/ 
#include <errno.h> /*错误号定义*/
#include <limits.h> 
#include <string.h>


int openPort(int index);
//int setPara(int serialfd,int speed=2,int databits=8,int stopbits=1,int parity=0);
int setPara(int serialfd,int speed,int databits,int stopbits,int parity);
int nwrite(int serialfd,const char *data,int datalength);
void closePort(int serialfd); 
int BaudRate( int baudrate);
int _BaudRate(int baudrate);
int GetBaudRate(); 
#endif
