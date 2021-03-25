#include "STC8G.H"
#include "PWM.h"
#include "main.h"

u8 Freq_Parm = 2;
u8 Freq_KEY;

void Fore_XS()
{
	//	  PWMSET= 0x00;                                //ʹ��PWMģ��
	P2M1 = 0x00;
	P2M0 = 0x03; //����P20.P21Ϊ�������
	PWM15_PWM2_Enable();
	P_SW2 = 0x80;
	PWM2CKS = 0x00; // PWMʱ��Ϊϵͳʱ��
	switch (Freq_Parm)
	{
		//----6.5KHZ---------------------------------240000
	case 1:
		PWM2C = 0xE64;	  //����PWM����Ϊ0800H��PWMʱ��
		PWM20T2 = 0x0720; //PWM0�ڼ���ֵΪ700H�ط�����ߵ�ƽ
		PWM20T1 = 0x0ABE; //PWM0�ڼ���ֵΪ100H�ط�����͵�ƽ

		PWM21T2 = 0x0000; //PWM1�ڼ���ֵΪ0080H�ط�����ߵ�ƽ
		PWM21T1 = 0x0390; //PWM1�ڼ���ֵΪ0780H�ط�����͵�ƽ
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
	PWM20CR = 0x80; //ʹ��PWM0���
	PWM21CR = 0x80; //ʹ��PWM1���
	P_SW2 = 0x00;
}

//----���ⷢ��----------------
void IR_Fore()
{
	P3M1 = 0x00;
	P3M0 = 0x08;		 //����P33Ϊ�������
	PWM15_PWM3_Enable(); //ʹ��PWMģ��
	P_SW2 = 0x80;
	PWM3CKS = 0x00; // PWMʱ��Ϊϵͳʱ��
	PWM3C = 0x1880;	  //����PWM����Ϊ0800H��PWMʱ��
	PWM33T1 = 0x0100; //PWM3�ڼ���ֵΪ700H�ط�����͵�ƽ
	PWM33T2 = 0x0CFF; //PWM3�ڼ���ֵΪ100H�ط�����ߵ�ƽ
	PWM33CR = 0x80;	  //ʹ��PWM0���
	P_SW2 = 0x00;
	PWMCFG23 = 0x11;
}
