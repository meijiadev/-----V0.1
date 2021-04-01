#include "STC8G.H"
#include "main.h"
#include "AIP650.h"
#include "delay.h"
//#include  "uart.h"
#include <stdio.h>
#include "EEPROM.h"
#include "GUI.h"

u8 data Bri_bit; //数码管亮度调节

extern u8 menu;      //菜单
extern u8 menu_flag; //菜单标志
extern u8 PA_flag;   //密码位数标志
extern u8 freq_flag; //频率/声音显示标志

//数码管0-9显示代码
//--------------------------------0----1----2----3---4----5----6----7----8----9----10---11---12---13---14---15---16---17---18
//                                0    1    2    3   4    5    6    7    8    9    -    A    b    c    d    e    f     h
u8 DISPLAY_CODE[19] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x40, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x76, 0x00};
//数码管位数                      1    2    3    4
u8 DIG_BIT_CODE[4] = {0x68, 0x6a, 0x6c, 0x6e};
//8段显示亮度等级                 1    2    3    4    5    6    7   8
u8 Light_Level_CODE[8] = {0x11, 0x21, 0x31, 0x41, 0x51, 0x61, 0x71, 0x01};

//----IIC_1开始信号-----------------------------------
void I2CStart(void)
{
  CLK_H;
  DIO_H;
  Delay_us(5);
  DIO_L;
}

//----IIC_2开始信号-----------------------------------
void I2CStart_1(void)
{
  CLK1_H;
  DIO1_H;
  Delay_us(5);
  DIO1_L;
}

//----ACK_1信号-----------------------------------
void I2Cask(void)
{
  u8 timeout = 1;  
  CLK_H;
  Delay_us(5);
  CLK_L;
  while ((DIO) && (timeout <= 100))
  {
    timeout++;
  }
  Delay_us(5);
  CLK1_L;
}

//----ACK_2信号-----------------------------------
void I2Cask_1(void)
{
  u8 timeout = 1;
  CLK1_H;
  Delay_us(5);
  CLK1_L;
  while ((DIO1) && (timeout <= 100))
  {
    timeout++;
  }
  Delay_us(5);
  CLK1_L;
}

//----停止信号------------------------------------
void I2CStop(void)
{
  CLK_H;
  DIO_L;
  Delay_us(5);
  DIO_H;
}

//----停止信号------------------------------------
void I2CStop_1(void)
{
  CLK1_H;
  DIO1_L;
  Delay_us(5);
  DIO1_H;
}

//----写一个字节高位在前，低位在后-----------------
void I2CWrByte(u8 oneByte)
{
  u8 i;
  CLK_L;
  Delay_us(1);
  for (i = 0; i < 8; i++)
  {
    oneByte = oneByte << 1;
    DIO = CY;
    CLK_L;
    Delay_us(5);
    CLK_H;
    Delay_us(5);
    CLK_L;
  }
}

//----写一个字节高位在前，低位在后-----------------
void I2CWrByte_1(u8 oneByte)
{
  u8 i;
  CLK1_L;
  Delay_us(1);
  for (i = 0; i < 8; i++)
  {
    oneByte = oneByte << 1;
    DIO1 = CY;
    CLK1_L;
    Delay_us(5);
    CLK1_H;
    Delay_us(5);
    CLK1_L;
  }
}

/************************************************** 
  功能描述: //后4位数码管显示
	入口参数：
  说    明：                        
**************************************************/
void AiP650_Set(u8 add, u8 dat) //数码管显示
{
  //写显存必须从高地址开始写
  I2CStart();
  I2CWrByte(add); //第一个显存地址
  I2Cask();
  I2CWrByte(dat);
  I2Cask();
  I2CStop();
}


/**
 * @brief  前4位数码管显示
 * @note   每次点亮其中数字
 * @param  add: 
 * @param  dat: 
 * @retval None
 */
void AiP650_Set_1(u8 add, u8 dat) //数码管显示
{
  //写显存必须从高地址开始写
  I2CStart_1();
  I2CWrByte_1(add); //第一个显存地址
  I2Cask_1();
  I2CWrByte_1(dat);
  I2Cask_1();
  I2CStop_1();
}


/**
 * @brief  后4位数码管全显 显示一个四位数 （0-9999）带点
 * @note   
 * @param  Display_num: 
 * @retval None
 */
void AiP650_DisPlayFour(u16 Display_num)
{
  u8 Temp[4];

  Temp[0] = Display_num % 10000 / 1000;
  Temp[1] = Display_num % 1000 / 100;
  Temp[2] = Display_num % 100 / 10;
  Temp[3] = Display_num % 10;

  AiP650_Set(0x68, DISPLAY_CODE[Temp[0]]);
  AiP650_Set(0x6A, DISPLAY_CODE[Temp[1]]);
  AiP650_Set(0x6C, DISPLAY_CODE[Temp[2]]); //加点	  AiP650_Set(0x6C,DISPLAY_CODE[Temp[2]]|0x80);
  AiP650_Set(0x6E, DISPLAY_CODE[Temp[3]]);
}


/**
 * @brief  前4位数码管全显 显示一个四位数 （0-9999）
 * @note   
 * @param  Display_num: 
 * @retval None
 */
void AiP650_DisPlayFour_1(u16 Display_num)
{
  u8 Temp[4];
  Temp[0] = Display_num % 10000 / 1000;
  Temp[1] = Display_num % 1000 / 100;
  Temp[2] = Display_num % 100 / 10;
  Temp[3] = Display_num % 10;

  AiP650_Set_1(0x68, DISPLAY_CODE[Temp[0]]);
  AiP650_Set_1(0x6A, DISPLAY_CODE[Temp[1]]);
  AiP650_Set_1(0x6C, DISPLAY_CODE[Temp[2]]); //加点	  AiP650_Set(0x6C,DISPLAY_CODE[Temp[2]]|0x80);

  AiP650_Set_1(0x6E, DISPLAY_CODE[Temp[3]]); //SW1=0;}
}

/************************************************** 
  功能描述: //设置后4位数码管亮度等级 1-8级
	入口参数：
  说    明：                        
**************************************************/
void Light_Level_Set(u8 Level)
{
  AiP650_Set(0x48, Light_Level_CODE[Level - 1]);
}

/************************************************** 
  功能描述: //设置前4位数码管亮度等级 1-8级
	入口参数：
  说    明：                        
**************************************************/
void Light_Level_Set_1(u8 Level)
{
  AiP650_Set_1(0x48, Light_Level_CODE[Level - 1]);
}


