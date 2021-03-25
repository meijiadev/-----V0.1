#include "STC8G.H"
#include "GUI.h"
#include "main.h"
#include "delay.h"
#include "AIP650.h"
#include "EEPROM.h"

//ͨ��extern���ԺϷ�ʹ���Ѿ�������ⲿ����
extern u8 DISPLAY_CODE[19];
extern u8 Freq_Parm; //Ƶ��

//extern u8  VOI_M;
//extern u8  VOI;                           //����������־

u8 menu = 0;	  //�˵�
u8 menu_flag = 0; //�˵���־
u16 Pass = 0;	  //ͨ������
u16 Alarm = 0;	  //��������

u8 flash_flag = 0; //��˸��־
u8 flash_M = 0;	   //��˸����
//---������-----------------------------------------
u8 LMD_1;

//--------��������-------------
u8 mima1 = 0;
u8 mima2 = 0;
u8 mima3 = 0;
u8 mima4 = 0;
//--------��������-------------
u8 mima5 = 1;
u8 mima6 = 2;
u8 mima7 = 3;
u8 mima8 = 4;

u8 PA_flag;		  //����λ����־
u8 freq_flag = 0; //Ƶ��/������ʾ��־
u8 voice = 0;	  //�������ر�־

/********************************
����������UI����
��ڲ�������
�� �� ֵ����
*********************************/
void meun_UI()
{
	switch (menu)
	{
	case 0:							 //���Խ���
		AiP650_DisPlayFour_1(Alarm); //��������
		PA_flag = 0;
		Freq_disp();
		break;
	case 1:
		password_UI();
		break;
	case 2:
		LMD_XZ();
		PA_flag = 0;
		break;
	case 3:
		password_UI();
		break;
	default:
		break;
	}
}

/********************************
�����������������
��ڲ�������
�� �� ֵ����
*********************************/
void password_UI()
{

	flash_M++;
	if (flash_M < 120)
	{
		flash_flag = 1;
	}
	if (flash_M > 120)
	{
		flash_flag = 0;
	}
	if (flash_M == 240)
	{
		flash_M = 0;
	}

	//-----------------------------------
	if (PA_flag != 0)
	{
		AiP650_Set_1(0x68, DISPLAY_CODE[mima5]);
	}
	if (PA_flag != 1)
	{
		AiP650_Set_1(0x6A, DISPLAY_CODE[mima6]);
	}
	if (PA_flag != 2)
	{
		AiP650_Set_1(0x6C, DISPLAY_CODE[mima7]);
	}
	if (PA_flag != 3)
	{
		AiP650_Set_1(0x6E, DISPLAY_CODE[mima8]);
	}
	//-----------------------------------
	switch (PA_flag)
	{
	case 0:

		switch (flash_flag)
		{
		case 0:
			AiP650_Set_1(0x68, DISPLAY_CODE[mima5]);
			break;
		case 1:
			AiP650_Set_1(0x68, DISPLAY_CODE[mima5] | 0x80);
			break;
		default:
			break;
		}
		break;
	case 1:

		switch (flash_flag)
		{
		case 0:
			AiP650_Set_1(0x6A, DISPLAY_CODE[mima6]);
			break;
		case 1:
			//						 AiP650_Set_1(0x6A,0x40);
			AiP650_Set_1(0x6A, DISPLAY_CODE[mima6] | 0x80);
			break;
		default:
			break;
		}
		break;

	case 2:
		switch (flash_flag)
		{
		case 0:
			AiP650_Set_1(0x6C, DISPLAY_CODE[mima7]);
			break;
		case 1:
			//						 AiP650_Set_1(0x6C,0x40);
			AiP650_Set_1(0x6C, DISPLAY_CODE[mima7] | 0x80);
			break;
		default:
			break;
		}
		break;
	case 3:
		switch (flash_flag)
		{
		case 0:
			AiP650_Set_1(0x6E, DISPLAY_CODE[mima8]);
			break;
		case 1:
			//						 AiP650_Set_1(0x6E,0x40);
			AiP650_Set_1(0x6E, DISPLAY_CODE[mima8] | 0x80);
			break;
		default:
			break;
		}
		break;
	}
}

/************************************************** 
  ��������: �Ӱ�ť����
	��ڲ�����
  ˵    ����                        
**************************************************/
void ADD_UI()
{
	switch (menu)
	{
		//---Ƶ�ʵ���---------------------------------
	case 0:
		freq_flag = 1; //��ʾ��־
		Freq_Parm++;
		if (Freq_Parm > 9)
			Freq_Parm = 1;

		break;
		//---�������---------------------------------
	case 1:
		switch (PA_flag)
		{
		case 0:
			mima5++;
			if (mima5 > 9)
				mima5 = 0;
			break;
		case 1:
			mima6++;
			if (mima6 > 9)
				mima6 = 0;
			break;
		case 2:
			mima7++;
			if (mima7 > 9)
				mima7 = 0;
			break;
		case 3:
			mima8++;
			if (mima8 > 9)
				mima8 = 0;
			break;
		}
		break;
		//---�����ȵ���---------------------------------
	case 2:
		LMD_1++;
		if (LMD_1 > 99)
			LMD_1 = 1;
		break;
		//---�������---------------------------------
	case 3:
		switch (PA_flag)
		{
		case 0:
			mima5++;
			if (mima5 > 9)
				mima5 = 0;
			break;
		case 1:
			mima6++;
			if (mima6 > 9)
				mima6 = 0;
			break;
		case 2:
			mima7++;
			if (mima7 > 9)
				mima7 = 0;
			break;
		case 3:
			mima8++;
			if (mima8 > 9)
				mima8 = 0;
			break;
		}
		break;

	default:
		break;
	}
}

/************************************************** 
  ��������: ����ť����
	��ڲ�����
  ˵    ����                        
**************************************************/
void RED_UI()
{
	switch (menu)
	{
		//---��������---------------------------------
	case 0:
		voice++;
		if (voice > 1)
			voice = 0;
		break;
		//---�������---------------------------------
	case 1:
		switch (PA_flag)
		{
		case 0:
			mima5--;
			if (mima5 == 255)
				mima5 = 9;
			break;
		case 1:
			mima6--;
			if (mima6 == 255)
				mima6 = 9;
			break;
		case 2:
			mima7--;
			if (mima7 == 255)
				mima7 = 9;
			break;
		case 3:
			mima8--;
			if (mima8 == 255)
				mima8 = 9;
			break;
		}
		break;
		//---�����ȵ���---------------------------------
	case 2:
		LMD_1--;
		if (LMD_1 == 255)
			LMD_1 = 99;
		break;
		//---�������---------------------------------
	case 3:
		switch (PA_flag)
		{
		case 0:
			mima5--;
			if (mima5 == 255)
				mima5 = 9;
			break;
		case 1:
			mima6--;
			if (mima6 == 255)
				mima6 = 9;
			break;
		case 2:
			mima7--;
			if (mima7 == 255)
				mima7 = 9;
			break;
		case 3:
			mima8--;
			if (mima8 == 255)
				mima8 = 9;
			break;
		}
		break;
	default:
		break;
	}
}

/************************************************** 
  ��������: ȷ����ť����
	��ڲ�����
  ˵    ����                        
**************************************************/
void ENT_UI()
{

	switch (menu)
	{
		//-----����ȷ��-------------------------------
	case 1:
		PASS_DB();
		break;
		//-----������ȷ��-------------------------------
	case 2:
		menu = 3;
		menu_flag = 2;
		break;
		//-----�޸�����ȷ��-------------------------------
	case 3:

		menu = 0;
		menu_flag = 0;
		break;

	default:
		break;
	}
}

/************************************************** 
  ��������: ����Ա�
	��ڲ�����
  ˵    ����                        
**************************************************/
void PASS_DB()
{

	//-----���������ж�---------------------------------------------------
	if (mima5 == 8 && mima6 == 8 && mima7 == 8 && mima8 == 8)
	{

		AiP650_Set_1(0x68, DISPLAY_CODE[13]);
		MM_AIP650();
		delay_ms(800);
		//			  CD_flag=4;ID1=0;
		mima5 = 1;
		mima6 = 2;
		mima7 = 3;
		mima8 = 4; //������ʾ��������
	}
	//-----�����ж���ȷ---------------------------------------------------
	else if (mima5 == mima1 && mima6 == mima2 && mima7 == mima3 && mima8 == mima4)
	{

		AiP650_Set_1(0x68, DISPLAY_CODE[13]);
		MM_AIP650();

		delay_ms(800);
		menu = 2;
		menu_flag = 1; //��������������
	}
	//-----�����жϴ���---------------------------------------------------
	else
	{

		AiP650_Set_1(0x68, DISPLAY_CODE[15]);
		MM_AIP650();
		delay_ms(800);
		menu = 1;
		menu_flag = 0;
		mima5 = 1;
		mima6 = 2;
		mima7 = 3;
		mima8 = 4; //������ʾ��������
	}
}

/************************************************** 
  ��������: ����ȷ����ʾ��Ϣ
	��ڲ�����
  ˵    ����                        
**************************************************/
void MM_AIP650()
{
	AiP650_Set_1(0x6A, DISPLAY_CODE[0]);
	AiP650_Set_1(0x6C, DISPLAY_CODE[0]);
	AiP650_Set_1(0x6E, DISPLAY_CODE[0]);
}

/************************************************** 
  ��������: ��������ʾ
	��ڲ�����
  ˵    ����                        
**************************************************/
void LMD_XZ()
{
	AiP650_Set_1(0x68, DISPLAY_CODE[1]);
	AiP650_Set_1(0x6A, DISPLAY_CODE[10]);
	AiP650_Set_1(0x6C, DISPLAY_CODE[LMD_1 % 100 / 10]);
	AiP650_Set_1(0x6E, DISPLAY_CODE[LMD_1 % 10]);
}

/************************************************** 
  ��������: Ƶ��������ʾ
	��ڲ�����
  ˵    ����                        
**************************************************/
void Freq_disp()
{
	switch (freq_flag)
	{
	case 0:
		/*				
      	if(voice==1)
				{					
	        AiP650_Set(0x68,DISPLAY_CODE[Pass%10000/1000]);   
	        AiP650_Set(0x6A,DISPLAY_CODE[Pass%1000/100]);
	        AiP650_Set(0x6C,DISPLAY_CODE[Pass%100/10]); 
		      AiP650_Set(0x6E,DISPLAY_CODE[Pass%10]|0x80); 
				}
				else 
				{AiP650_DisPlayFour(Pass);}		                     //ͨ������
*/
		break;
	case 1:
		AiP650_Set(0x68, DISPLAY_CODE[16]); //F
		AiP650_Set(0x6A, DISPLAY_CODE[10]);
		AiP650_Set(0x6C, DISPLAY_CODE[Freq_Parm % 100 / 10]);
		AiP650_Set(0x6E, DISPLAY_CODE[Freq_Parm % 10]);
		delay_ms(1000);
		break;
	default:
		break;
	}
}

//----����ɨ��---ʹ�ð�ťʱ����------------------------------
//��ť��ַ�� A-0x47,B-0x4F,C-0x57,D-0x5F,E-0x67,F-0x6F,G-0x77
//
//---------------------------------------------

u8 Scan_Key(void)
{
  u8 i;
  u8 rekey;
  I2CStart();
  I2CWrByte(0x49); //����������
  I2Cask();
  for (i = 0; i < 8; i++)
  {
    CLK_H;
    rekey = rekey << 1;
    if (DIO)
    {
      rekey++;
    }
    Delay_us(10);
    CLK_L;
  }
  I2Cask();
  I2CStop();
  return (rekey);
}

/**
 * ��������---ʹ�ð�ťʱ����
 * */
void KEY_CL()
{
  u8 KEY;
  KEY = Scan_Key();
  switch (KEY)
  {
    //K1   �˵���	----------------------------------------------------
  case 0x47:
    if (menu == 0 && menu_flag == 0)
    {
      menu = 1;
      PA_flag = 3;
    } //����������������
    if (menu == 1 || menu == 3)
    {
      PA_flag++;
      if (PA_flag > 3)
        PA_flag = 0;
    }
    delay_ms(300);
    break;

    //K2    ����+	-------------------------------------
  case 0x4F:
    ADD_UI();
    freq_flag = 1;
    delay_ms(300);
    break;
    //K3    ����-		----------------------------------------
  case 0x57:
    RED_UI();
    delay_ms(300);
    LED3 = 0;
    break;
    //K4    ȷ��	----------------------------------------
  case 0x5F: //K2
    ENT_UI();
    delay_ms(300);
    break;
  default:
    freq_flag = 0;
    break;
  }
}
