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

#define SECTION_1    0x00                  //����1��ַ
#define SECTION_2    0x200                 //����2��ַ


#define PEOPLE_NUM_H_ADDR   0x201           //���������߰�λ
#define PEOPLE_NUM_L_ADDR   0x202           //���������ĵͰ�λ
#define ALARM_NUM_H_ADDR    0x203           //���������ĸ߰�λ
#define ALARM_NUM_L_ADDR    0x204           //���������ĵͰ�λ

//#define IAP_ADDRESS  0X0000	               //�ڲ�EEPROM��ַ


void EEPROM_init();                        //��ʼ��
void IapEraseSector(u16 addr);             //����һ���ֽں���
void IapProgramByte(u16 addr,u8 dat);      //д��һ���ֽں���
u8 IapReadByte(u16 addr);                  //��ȡһ���ֽں���
void IapIdle();                            //��������
//bit flag_eeprom1=1;                      //����洢�ı�־λ
void saveeepro();                          //��������
void saveFreq(u8 dat);                           //����Ƶ��
void savePeopleNumber();                   //���澭�������ͱ�������
void brownoutDetectInit();                 //�������ʼ��


#endif