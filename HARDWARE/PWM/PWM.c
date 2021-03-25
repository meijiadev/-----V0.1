#include "STC8G.H"
#include "PWM.h"
#include "main.h"

u8 Freq_Parm = 2;
u8 Freq_KEY;

void Fore_XS()
{
	//	  PWMSET= 0x00;                                //使能PWM模块
	P2M1 = 0x00;
	P2M0 = 0x03; //设置P20.P21为推挽输出
	PWM15_PWM2_Enable();
	P_SW2 = 0x80;
	PWM2CKS = 0x00; // PWM时钟为系统时钟
	switch (Freq_Parm)
	{
		//----6.5KHZ---------------------------------240000
	case 1:
		PWM2C = 0xE64;	  //设置PWM周期为0800H个PWM时钟
		PWM20T2 = 0x0720; //PWM0在计数值为700H地方输出高电平
		PWM20T1 = 0x0ABE; //PWM0在计数值为100H地方输出低电平

		PWM21T2 = 0x0000; //PWM1在计数值为0080H地方输出高电平
		PWM21T1 = 0x0390; //PWM1在计数值为0780H地方输出低电平
		Freq_KEY = 0;
		break;
		//----6.8KHZ---------------------------------
	case 2:
		PWM2C = 0xDC6;
		PWM20T2 = 0x06D9;
		PWM20T1 = 0x0A4F;
		PWM21T2 = 0x0000;
		PWM21T1 = 0x0370;
		Freq_KEY = 1;
		break;
		//----7.1KHZ---------------------------------
	case 3:
		PWM2C = 0xD31;
		PWM20T2 = 0x0699;
		PWM20T1 = 0x09F0;
		PWM21T2 = 0x0000;
		PWM21T1 = 0x034A;
		break;
		//----7.4KHZ---------------------------------
	case 4:
		PWM2C = 0xCA6;
		PWM20T2 = 0x0649;
		PWM20T1 = 0x0980;
		PWM21T2 = 0x0000;
		PWM21T1 = 0x032A;
		break;
		//----7.7KHZ---------------------------------
	case 5:
		PWM2C = 0xC26;
		PWM20T2 = 0x0619;
		PWM20T1 = 0x0920;
		PWM21T2 = 0x0000;
		PWM21T1 = 0x030A;
		break;
		//----8.0KHZ---------------------------------
	case 6:
		PWM2C = 0xBB5;
		PWM20T2 = 0x05E0;
		PWM20T1 = 0x08CA;
		PWM21T2 = 0x0000;
		PWM21T1 = 0x02F0;
		Freq_KEY = 0;
		break;
		//----8.3KHZ---------------------------------
	case 7:
		PWM2C = 0xB4B;
		PWM20T2 = 0x05AE;
		PWM20T1 = 0x086A;
		PWM21T2 = 0x0000;
		PWM21T1 = 0x02D0;
		break;
		//----8.6KHZ---------------------------------
	case 8:
		PWM2C = 0xAE4;
		PWM20T2 = 0x058E;
		PWM20T1 = 0x083A;
		PWM21T2 = 0x0000;
		PWM21T1 = 0x02C0;

		break;
		//----8.9KHZ---------------------------------
	case 9:
		PWM2C = 0xA85;
		PWM20T2 = 0x054E;
		PWM20T1 = 0x07F0;
		PWM21T2 = 0x0000;
		PWM21T1 = 0x02B0;
		Freq_KEY = 0;
		break;
	}
	PWM20CR = 0x80; //使能PWM0输出
	PWM21CR = 0x80; //使能PWM1输出
	P_SW2 = 0x00;
}

//----红外发射----------------
void IR_Fore()
{
	P3M1 = 0x00;
	P3M0 = 0x08;		 //设置P33为推挽输出
	PWM15_PWM3_Enable(); //使能PWM模块
	P_SW2 = 0x80;
	PWM3CKS = 0x00; // PWM时钟为系统时钟
	PWM3C = 0x1880;	  //设置PWM周期为0800H个PWM时钟
	PWM33T1 = 0x0100; //PWM3在计数值为700H地方输出低电平
	PWM33T2 = 0x0CFF; //PWM3在计数值为100H地方输出高电平
	PWM33CR = 0x80;	  //使能PWM0输出
	P_SW2 = 0x00;
	PWMCFG23 = 0x11;
}
