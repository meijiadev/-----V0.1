#ifndef DELAY_H
#define EDLAY_H
#include  "main.h"


void delaylow(u8 time);	 //红外专用 延时
void delay2us(u16 us);   //2us倍数延时
void delay4us(u16 us);   //4us倍数延时
void delay_ms(u16 ms);   //毫秒延时

void T_Delay_us(u16 n);

#endif
