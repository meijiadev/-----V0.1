#ifndef __AIP650_H_
#define __AIP650_H_

#include  "main.h"	 
#include <intrins.h> 

//--AIP650_1------------------------------------------------
sbit CLK              = P4^3;				   //AiP650��CLK�ź�
sbit DIO              = P4^2;				   //AiP650��SDA�ź�

//--AIP650_2------------------------------------------------
sbit CLK1             = P3^7;				      //AiP650��CLK�ź�
sbit DIO1             = P4^1;				      //AiP650��SDA�ź�


#define CLK_H  CLK = 1			  //CLK�ߵ�ƽ
#define CLK_L  CLK = 0			  //CLK�͵�ƽ
#define DIO_H  DIO = 1			  //SDA�ߵ�ƽ
#define DIO_L  DIO = 0			  //SDA�͵�ƽ


#define CLK1_H  CLK1 = 1			  //CLK1�ߵ�ƽ
#define CLK1_L  CLK1 = 0			  //CLK1�͵�ƽ
#define DIO1_H  DIO1 = 1			  //SDA1�ߵ�ƽ
#define DIO1_L  DIO1 = 0			  //SDA1�͵�ƽ




extern void Delay_us(u16 x);     //��ʱus
extern void Delay_ms(u16 x);	 //��ʱus

void AiP650_Set(u8 add,u8 dat);                           //�������ʾ
void AiP650_Set_1(u8 add,u8 dat);                          //�������ʾ

extern void AiP650_DisPlay(u8 DIG_Bit, u8 Display_num);	  //��ʾһλ����
extern void AiP650_DisPlay_1(u8 DIG_Bit, u8 Display_num);	
extern void AiP650_DisPlayFourNum(u16 Display_num);		    //��ʾһ����λ��(��λ�ԣ�
extern void AiP650_DisPlayFour_1(u16 Display_num);
extern void AiP650_DisPlayFour(u16 Display_num);          //��ʾһ����λ����ȫ�ԣ�
extern void Light_Level_Set(u8 Level);					          //�������ȵȼ�
extern void Light_Level_Set_1(u8 Level);					        //�������ȵȼ� 1-8��
extern void AiP650_CLR();								                  //����

void I2CStart(void);              //I2C����
void I2Cask(void);               // I2CӦ��
void I2CWrByte(u8 oneByte);      //I2Cд��
void I2CStop(void);              //I2Cֹͣ



void MM_XS();                                             //��������

void Bri_TJ();                                            //��������ȵ���

void IR_DISP();


#endif 