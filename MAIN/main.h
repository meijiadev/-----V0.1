#ifndef MAIN_H
#define MAIN_H

//#include "STC8G.H"

//----���ݶ���------------------------------------------------
#define u8 unsigned char
#define u16 unsigned int
//#define u32 unsigned long

//----Ƶ�ʶ���------------------------------------------------
//#define MAIN_Fosc		24000000	                 //������ʱ��
//#define T_MS   8                               //��ʱʱ�䳣������λms   8
//#define T1TMS    (T_MS*MAIN_Fosc/100000000)  //1Tģʽ��
//#define T12TMS   (T_MS*MAIN_Fosc/1000/12)      //12Tģʽ��

//----���Ŷ���------------------------------------------------
//sbit Freq_KEY      =P6^4;     	               //Ƶ�ʼ̵���
//sbit IR_OUT        =P3^3;                      //�������źŷ���
//sbit SW1           =P2^5;                      //�ɽӵ�
//sbit LCDK          =P6^3;                      //LCD���⿪��
//sbit RS485_EN      =P3^4;                      //485����ѡ��

sbit LED1 = P0 ^ 5;
sbit LED2 = P0 ^ 6;
sbit LED3 = P0 ^ 7;
sbit LED4 = P1 ^ 4;
sbit LED5 = P1 ^ 5;
sbit LED6 = P1 ^ 6;

#endif