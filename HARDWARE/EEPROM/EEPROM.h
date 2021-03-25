#ifndef __EEPROM_H
#define __EEPROM_H

#include "main.h"
#include <intrins.H>

//#define uint unsigned int  //�궨���޷�������

/************************EEPROM����**********************************/

#define CMD_IDLE     0	                   //EEPROM�޲���
#define CMD_READ     1	                   //��ȡ�ֽ�
#define CMD_PROGRAM  2	                   //д���ֽ�
#define CMD_ERASE    3	                   //�����ֽ�
#define ENABLE_IAP   0X80	                 //��������ɾ�����������<12MHZѡ�ô���� 0x80 =1000 0000
//#define IAP_ADDRESS  0X0000	               //�ڲ�EEPROM��ַ


void EEPROM_init();                        //��ʼ��
void IapEraseSector(u16 addr);             //����һ���ֽں���
void IapProgramByte(u16 addr,u8 dat);      //д��һ���ֽں���
u8 IapReadByte(u16 addr);                  //��ȡһ���ֽں���
void IapIdle();                            //��������
//bit flag_eeprom1=1;                      //����洢�ı�־λ
void saveeepro();                          //����洢

#endif