#include "STC8.H"
#include "delay.h"
#include <intrins.h>

/*
24MHz主频下 
在示波器下看
一个语句的时间大概是 0.8us
*/

/***********************
功能描述：2微秒	延时
入口参数：无
返回值：无
//此函数是以2us的倍数增加
//t  2us的倍数
************************/
/*
void delay2us(u16 us)
 {
  u16 i;
  u8 m;
  for(i=0;i<us;i++)
  for(m=0;m<3;m++);
 }
*/

/***********************
功能描述：4微秒	延时
入口参数：无
返回值：无
//此函数是以4us的倍数增加
//t  4us的倍数
************************/
/*
void delay4us(u16 us)
 {
  u16 i;
  u8 m;
  for(i=0;i<us;i++)
  for(m=0;m<5;m++);
 }  
*/

/***********************
功能描述：1毫秒 延时
入口参数：无
返回值：无
//ms 1ms的倍数
************************/
/*
void delay1ms(u16 ms)
{
 u16 m;
 for(m=0;m<ms;m++)
 delay4us(250);
} 
*/

void delay_ms(unsigned int ms)
{
	unsigned int a;
	while (ms)
	{
		a = 1800;
		while (a--)
			;
		ms--;
	}
	return;
}

/***********************
功能描述：微秒	延时
入口参数：无
返回值：无
************************/

void Delay_us(u16 x) //us延时
{
	for (; x > 0; x--)
	{
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
	}
}

/*
void T_Delay_us(u16 n)
{
  unsigned int i;
  while(n--)
  {
    i=11;
  while(i--);
  }
}
*/

/**************************************
功能描述：延时函数
入口参数：uint16 x ，该值为1时，延时1ms
返回值：无
***************************************/
/*
void delay_ms(u16 x) 
{  
	uint16 j,i;   
	for(j=0;j<x;j++)   
	{    
		for(i=0;i<1100;i++);   
	}  
}
*/

/***********************
功能描述：红外专用 延时
入口参数：无
返回值：无
************************/
/*
void delaylow(u8 time)		   //红外专用 延时
{
 u8 i,j;
 for(i=0;i<time;i++)
  for(j=0;j<100;j++);
}
*/
