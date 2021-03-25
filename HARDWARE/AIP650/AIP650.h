#ifndef __AIP650_H_
#define __AIP650_H_

#include  "main.h"	 
#include <intrins.h> 

//--AIP650_1------------------------------------------------
sbit CLK              = P4^3;				   //AiP650的CLK信号
sbit DIO              = P4^2;				   //AiP650的SDA信号

//--AIP650_2------------------------------------------------
sbit CLK1             = P3^7;				      //AiP650的CLK信号
sbit DIO1             = P4^1;				      //AiP650的SDA信号


#define CLK_H  CLK = 1			  //CLK高电平
#define CLK_L  CLK = 0			  //CLK低电平
#define DIO_H  DIO = 1			  //SDA高电平
#define DIO_L  DIO = 0			  //SDA低电平


#define CLK1_H  CLK1 = 1			  //CLK1高电平
#define CLK1_L  CLK1 = 0			  //CLK1低电平
#define DIO1_H  DIO1 = 1			  //SDA1高电平
#define DIO1_L  DIO1 = 0			  //SDA1低电平




extern void Delay_us(u16 x);     //延时us
extern void Delay_ms(u16 x);	 //延时us

void AiP650_Set(u8 add,u8 dat);                           //数码管显示
void AiP650_Set_1(u8 add,u8 dat);                          //数码管显示

extern void AiP650_DisPlay(u8 DIG_Bit, u8 Display_num);	  //显示一位数字
extern void AiP650_DisPlay_1(u8 DIG_Bit, u8 Display_num);	
extern void AiP650_DisPlayFourNum(u16 Display_num);		    //显示一个四位数(按位显）
extern void AiP650_DisPlayFour_1(u16 Display_num);
extern void AiP650_DisPlayFour(u16 Display_num);          //显示一个四位数（全显）
extern void Light_Level_Set(u8 Level);					          //设置亮度等级
extern void Light_Level_Set_1(u8 Level);					        //设置亮度等级 1-8级
extern void AiP650_CLR();								                  //清屏

void I2CStart(void);              //I2C启动
void I2Cask(void);               // I2C应答
void I2CWrByte(u8 oneByte);      //I2C写入
void I2CStop(void);              //I2C停止



void MM_XS();                                             //密码输入

void Bri_TJ();                                            //数码管亮度调节

void IR_DISP();


#endif 