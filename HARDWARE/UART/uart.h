#ifndef _UART_H_
#define _UART_H_


void UartInit();
void UartSend(u8 dat);        //����һ���ֽ�
void UartSendStr(u8 *p);      //����һ���ַ���
void UartSendu16(u16 dat);