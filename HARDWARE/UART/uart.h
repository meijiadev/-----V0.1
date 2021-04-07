#ifndef _UART_H_
#define _UART_H_


void UartInit();
void UartSend(u8 dat);        //发送一个字节
void UartSendStr(u8 *p);      //发送一个字符串
void UartSendu16(u16 dat);