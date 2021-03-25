#ifndef MAIN_H
#define MAIN_H

//#include "STC8G.H"

//----数据定义------------------------------------------------
#define u8 unsigned char
#define u16 unsigned int
//#define u32 unsigned long

//----频率定义------------------------------------------------
//#define MAIN_Fosc		24000000	                 //定义主时钟
//#define T_MS   8                               //定时时间常量，单位ms   8
//#define T1TMS    (T_MS*MAIN_Fosc/100000000)  //1T模式下
//#define T12TMS   (T_MS*MAIN_Fosc/1000/12)      //12T模式下

//----引脚定义------------------------------------------------
//sbit Freq_KEY      =P6^4;     	               //频率继电器
//sbit IR_OUT        =P3^3;                      //红外检测信号发送
//sbit SW1           =P2^5;                      //干接点
//sbit LCDK          =P6^3;                      //LCD背光开关
//sbit RS485_EN      =P3^4;                      //485方向选择

sbit LED1 = P0 ^ 5;
sbit LED2 = P0 ^ 6;
sbit LED3 = P0 ^ 7;
sbit LED4 = P1 ^ 4;
sbit LED5 = P1 ^ 5;
sbit LED6 = P1 ^ 6;

#endif