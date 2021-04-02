#ifndef __EEPROM_H
#define __EEPROM_H

#include "main.h"
#include <intrins.H>

//#define uint unsigned int  //宏定义无符号整型

/************************EEPROM配置**********************************/

#define CMD_IDLE     0	                   //EEPROM无操作
#define CMD_READ     1	                   //读取字节
#define CMD_PROGRAM  2	                   //写入字节
#define CMD_ERASE    3	                   //擦除字节
#define ENABLE_IAP   0X80	                 //编程周期由晶振决定（如果<12MHZ选用此项）吧 0x80 =1000 0000

#define SECTION_1    0x00                  //扇区1地址
#define SECTION_2    0x200                 //扇区2地址


#define PEOPLE_NUM_H_ADDR   0x201           //经过人数高八位
#define PEOPLE_NUM_L_ADDR   0x202           //经过人数的低八位
#define ALARM_NUM_H_ADDR    0x203           //报警人数的高八位
#define ALARM_NUM_L_ADDR    0x204           //报警人数的低八位

//#define IAP_ADDRESS  0X0000	               //内部EEPROM地址


void EEPROM_init();                        //初始化
void IapEraseSector(u16 addr);             //擦除一个字节函数
void IapProgramByte(u16 addr,u8 dat);      //写入一个字节函数
u8 IapReadByte(u16 addr);                  //读取一个字节函数
void IapIdle();                            //操作函数
//bit flag_eeprom1=1;                      //掉电存储的标志位
void saveeepro();                          //保存密码
void saveFreq(u8 dat);                           //保存频率
void savePeopleNumber();                   //保存经过人数和报警人数
void brownoutDetectInit();                 //掉电检测初始化


#endif