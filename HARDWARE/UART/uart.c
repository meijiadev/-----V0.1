#include "STC8G.H"
#include "uart.h"
#include "main.h"

//----Ƶ�ʶ���------------------------------------------------
#define MAIN_Fosc		24000000	                 //������ʱ��
#define BRT (65536-MAIN_Fosc/115200/4)     //�����ʳ�ֵ

u8  wptr;
u8  rptr;
bit busy;          //λ���� ֻ��ʾһλ 0����1
u8  buffer[16];
/* 
  ��������������1��ʼ��
 */
 void UartInit(){
     SCON=0x50;               //���ڿ��ƼĴ���  --0011 0000 ѡ��ģʽ0��ͬ����λ���з�ʽ��
     T2L=BRT;            
     T2H=BRT>>8;
     AUXR=0x15;          //�����Ĵ��� 0001 0011 ������1ģʽ0�Ĳ����ʲ��ӱ� �������ʷ�����ѡ��ʱ��2��Ϊ������
     wptr=0x00;
     rptr=0x00;
     busy=0;
    
 }
/*
 ���������������ڷ���һ���ֽ�
 ����˵����Ҫ���͵�����
*/
 void UartSend(u8 dat){
     while (busy);
     busy=1;
     SBUF=dat;     
 }

/*
  ���������������ڷ���һ���ַ���
  ����˵�����ַ�ָ��
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


 