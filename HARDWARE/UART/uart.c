#include "STC8G.H"
#include "uart.h"
#include "main.h"

//----频率定义------------------------------------------------
#define MAIN_Fosc		24000000	                 //定义主时钟
#define BRT (65536-MAIN_Fosc/115200/4)     //波特率初值

u8  wptr;
u8  rptr;
bit busy;          //位标量 只表示一位 0或者1
u8  buffer[16];
/* 
  功能描述：串口1初始化
 */
 void UartInit(){
     SCON=0x50;               //串口控制寄存器  --0011 0000 选择模式0（同步移位串行方式）
     T2L=BRT;            
     T2H=BRT>>8;
     AUXR=0x15;          //辅助寄存器 0001 0011 ：串口1模式0的波特率不加倍 ，波特率发射器选择定时器2作为发射器
     wptr=0x00;
     rptr=0x00;
     busy=0;
    
 }
/*
 功能描述：往串口发送一个字节
 参数说明：要发送的数据
*/
 void UartSend(u8 dat){
     while (busy);
     busy=1;
     SBUF=dat;     
 }

/*
  功能描述：往串口发送一个字符串
  参数说明：字符指针
*/
 void UartSendStr(u8 *p){
    while (*p)
    {
        UartSend(*p++);
    }
 }


void UartInterrupt() interrupt 4 using 1{
    if (TI)
    {
        TI=0;
        busy=0;
    }

    if (RI)
    {
        RI=0;
        buffer[wptr++]=SBUF;
        wptr &=0x0f;
        
    }

}


 