#include "STC8G.H"
#include "GUI.h"
#include "main.h"
#include "delay.h"
#include "AIP650.h"
#include "EEPROM.h"
#include "uart.h"

//ͨ��extern���ԺϷ�ʹ���Ѿ�������ⲿ����
extern u8 DISPLAY_CODE[19];
extern u8 Freq_Parm;	  //Ƶ��
extern u16 ALARM_NUMBER;  //��������
extern u16 PEOPLE_NUMBER; //��������
u8 menuFlag = 0;		  //�˵���־      0:δ�������ǰ������  1����������    2:�����ȵ���   4:��������
u8 psDigits = 0;		  //�����޸ĵ�����λ��
u8 flash_flag = 0;		  //��˸��־
u8 flash_M = 0;			  //��˸����
u8 freqFlag = 0;		  //��ʾƵ��

u8 dB; //������
//--------����EEPROM�е�����-------------
u8 mima1 = 0;
u8 mima2 = 0;
u8 mima3 = 0;
u8 mima4 = 0;
//--------��������-------------
u8 mima5 = 1;
u8 mima6 = 2;
u8 mima7 = 3;
u8 mima8 = 4;

/**
 * @brief  �˵�UI
 * @note   
 * @retval None
 */
void menuUI()
{
	switch (menuFlag)
	{
	case 0:
		psDigits = 0;
		if (freqFlag == 1)
		{
			//��ʾƵ��
			AiP650_Set(0x68, DISPLAY_CODE[16]); //F
			AiP650_Set(0x6A, DISPLAY_CODE[10]);
			AiP650_Set(0x6C, DISPLAY_CODE[Freq_Parm % 100 / 10]);
			AiP650_Set(0x6E, DISPLAY_CODE[Freq_Parm % 10]);
			delay_ms(2000);
		}
		else
		{
			AiP650_DisPlayFour(PEOPLE_NUMBER);
			AiP650_DisPlayFour_1(ALARM_NUMBER);
		}
		break;
	case 1:
		passwordUI();
		break;
	case 2:
		dBShow();
		psDigits = 0;
		break;
	case 3:
		break;
	case 4:
		passwordUI();
		break;
	default:
		break;
	}
}

/**
 * @brief  ������ʾҳ
 * @note   
 * @retval None
 */
void passwordUI()
{
	/***********����ܵ���˸��־-start***********/
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
	/****************-end*******************/

	AiP650_Set_1(0x68, DISPLAY_CODE[mima5]);
	AiP650_Set_1(0x6A, DISPLAY_CODE[mima6]);
	AiP650_Set_1(0x6C, DISPLAY_CODE[mima7]);
	AiP650_Set_1(0x6E, DISPLAY_CODE[mima8]);
	switch (psDigits)
	{
	case 0:
		switch (flash_flag)
		{
		case 0:
			AiP650_Set_1(0x68, DISPLAY_CODE[mima5]);
			break;
		case 1: //��flage���1ʱ ���������Եĵ�
			AiP650_Set_1(0x68, DISPLAY_CODE[mima5] | 0x80);
			break;
		default:
			break;
		}
		break;
		break;
	case 1:
		switch (flash_flag)
		{
		case 0:
			AiP650_Set_1(0x6A, DISPLAY_CODE[mima6]);
			break;
		case 1:
			AiP650_Set_1(0x6A, DISPLAY_CODE[mima6] | 0x80);
			break;
		default:
			break;
		}
		break;
		break;
	case 2:
		switch (flash_flag)
		{
		case 0:
			AiP650_Set_1(0x6C, DISPLAY_CODE[mima7]);
			break;
		case 1:
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
			AiP650_Set_1(0x6E, DISPLAY_CODE[mima8] | 0x80);
			break;
		default:
			break;
		}
		break;

	default:
		break;
	}
}

/**
 * @brief  ���Ӽ��ĵ���¼�������
 * @note   
 * @retval None
 */
void add()
{
	switch (menuFlag)
	{
	case 0:
	    freqFlag=1;
		Freq_Parm++;
		if (Freq_Parm > 9)
			Freq_Parm = 1;
		break;
		//---�������---------------------------------
	case 1:
		switch (psDigits)
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
		dB++;
		if (dB > 100)
			dB = 1;
		break;
		//---Ƶ�ʵ���---------------------------------
	case 3:
		Freq_Parm++;
		if (Freq_Parm > 9)
			Freq_Parm = 1;
		break;
	case 4:
		//��������
		switch (psDigits)
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

/**
 * @brief  ���ٰ����Ĵ����¼�
 * @note   
 * @retval None
 */
void reduce()
{
	switch (menuFlag)
	{
	case 0:
		break;
	case 1:
		switch (psDigits)
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
	case 2:
		dB--;
		if (dB == 255)
			dB = 99;
		break;
	case 3:
		break;
	case 4:
		//��������
		switch (psDigits)
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
		break;
	default:
		break;
	}
}

/**
 * @brief  ȷ�������Ĵ����¼�
 * @note   
 * @retval None
 */
void enter()
{
	switch (menuFlag)
	{
	case 0:
		break;
	case 1:
		if (psDigits == 3)
		{
			passwordCheck();
		}
		else
		{
			psDigits++;
		}
		break;
	case 2:
	    menuFlag=0;
		saveeepro();
		break;
	case 3:
		break;
	case 4:
		if (psDigits == 3)
		{
			resetPassword();
		}
		else
		{
			psDigits++;
		}
		break;
	default:
		break;
	}
}

/**
 * @brief  ����У��
 * @note   
 * @retval None
 */
void passwordCheck()
{
	UartSend(mima1);
	UartSend(mima2);
	UartSend(mima3);
	UartSend(mima4);
	//-----���������жϳɹ������������û���---------------------------------------------------
	if (mima5 == 8 && mima6 == 8 && mima7 == 8 && mima8 == 8)
	{
		delay_ms(800);
		menuFlag = 4; //�����������û���
		//CD_flag=4;ID1=0;
		mima5 = 1;
		mima6 = 1;
		mima7 = 1;
		mima8 = 1; //������ʾ��������
		psDigits = 0;
	} //-----�����ж���ȷ---------------------------------------------------
	else if (mima5 == mima1 && mima6 == mima2 && mima7 == mima3 && mima8 == mima4)
	{

		AiP650_Set_1(0x68, DISPLAY_CODE[13]);
		checkResult();
		delay_ms(800);
		menuFlag = 2; //��������������
	}
	else
	{
		//����У�����
		AiP650_Set_1(0x68, DISPLAY_CODE[15]);
		checkResult();
		delay_ms(800);
		menuFlag = 1;
		mima5 = 1;
		mima6 = 2;
		mima7 = 3;
		mima8 = 4; //������ʾ��������
		psDigits = 0;
	}
}
/**
 * @brief  ��������
 * @note   
 * @retval None
 */
void resetPassword()
{
	mima1 = mima5;
	mima2 = mima6;
	mima3 = mima7;
	mima4 = mima8;
	//��������
	saveeepro();
	Delay_ms(300);
	menuFlag = 0; //�����޸���� �ص���ҳ
	mima5 = 1;
	mima6 = 2;
	mima7 = 3;
	mima8 = 4;
}

/**
 * @brief  У������UI��ʾ
 * @note   
 * @retval None
 */
void checkResult()
{
	AiP650_Set_1(0x6A, DISPLAY_CODE[0]);
	AiP650_Set_1(0x6C, DISPLAY_CODE[0]);
	AiP650_Set_1(0x6E, DISPLAY_CODE[0]);
}

/**
 * @brief ��������ʾ
 * @note   
 * @retval None
 */
void dBShow()
{
	AiP650_Set_1(0x68, DISPLAY_CODE[1]);
	AiP650_Set_1(0x6A, DISPLAY_CODE[10]);
	AiP650_Set_1(0x6c, DISPLAY_CODE[dB % 100 / 10]);
	AiP650_Set_1(0x6e, DISPLAY_CODE[dB % 10]);
}



/**
 * @brief   ����ɨ��---ʹ�ð�ťʱ����
 * @note   ��ť��ַ�� A-0x47,B-0x4F,C-0x57,D-0x5F,E-0x67,F-0x6F,G-0x77
 * @retval 
 */
u8 Scan_Key()
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
 * @brief  ���������¼�
 * @note   
 * @retval None
 */
void KEY_CL()
{
	u8 KEY;
	KEY = Scan_Key();
	switch (KEY)
	{
		//K1   �˵���	----------------------------------------------------
	case 0x47:
		menuFlag++;
		if (menuFlag > 4)
		{
			menuFlag = 0;
		}
		delay_ms(300);
		break;
		//K2    ����+	-------------------------------------
	case 0x4F:
		add();
		freqFlag=1;
		delay_ms(300);
		break;
		//K3    ����-		----------------------------------------
	case 0x57:
		reduce();
		delay_ms(300);
		break;
		//K4    ȷ��	----------------------------------------
	case 0x5F: //K2
		enter();
		delay_ms(300);
		break;
	default:
	    freqFlag=0;
		break;
	}
}