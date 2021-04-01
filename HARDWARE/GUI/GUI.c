#include "STC8G.H"
#include "GUI.h"
#include "main.h"
#include "delay.h"
#include "AIP650.h"
#include "EEPROM.h"
#include "uart.h"

//通过extern可以合法使用已经定义的外部变量
extern u8 DISPLAY_CODE[19];
extern u8 Freq_Parm;	  //频率
extern u16 ALARM_NUMBER;  //报警人数
extern u16 PEOPLE_NUMBER; //经过人数
u8 menuFlag = 0;		  //菜单标志      0:未点击按键前的样子  1：输入密码    2:灵敏度调节   4:密码重置
u8 psDigits = 0;		  //正在修改的密码位数
u8 flash_flag = 0;		  //闪烁标志
u8 flash_M = 0;			  //闪烁计数
u8 freqFlag = 0;		  //显示频率

u8 dB; //灵敏度
//--------保存EEPROM中的密码-------------
u8 mima1 = 0;
u8 mima2 = 0;
u8 mima3 = 0;
u8 mima4 = 0;
//--------输入密码-------------
u8 mima5 = 1;
u8 mima6 = 2;
u8 mima7 = 3;
u8 mima8 = 4;

/**
 * @brief  菜单UI
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
			//显示频率
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
 * @brief  密码显示页
 * @note   
 * @retval None
 */
void passwordUI()
{
	/***********数码管点闪烁标志-start***********/
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
		case 1: //当flage变成1时 点亮数字旁的点
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
 * @brief  增加键的点击事件处理函数
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
		//---密码调节---------------------------------
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
		//---灵敏度调节---------------------------------
	case 2:
		dB++;
		if (dB > 100)
			dB = 1;
		break;
		//---频率调节---------------------------------
	case 3:
		Freq_Parm++;
		if (Freq_Parm > 9)
			Freq_Parm = 1;
		break;
	case 4:
		//密码重置
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
 * @brief  减少按键的处理事件
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
		//密码重置
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
 * @brief  确定按键的处理事件
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
 * @brief  密码校验
 * @note   
 * @retval None
 */
void passwordCheck()
{
	UartSend(mima1);
	UartSend(mima2);
	UartSend(mima3);
	UartSend(mima4);
	//-----超级密码判断成功进入密码重置环节---------------------------------------------------
	if (mima5 == 8 && mima6 == 8 && mima7 == 8 && mima8 == 8)
	{
		delay_ms(800);
		menuFlag = 4; //进入密码重置环节
		//CD_flag=4;ID1=0;
		mima5 = 1;
		mima6 = 1;
		mima7 = 1;
		mima8 = 1; //密码显示数字重置
		psDigits = 0;
	} //-----密码判断正确---------------------------------------------------
	else if (mima5 == mima1 && mima6 == mima2 && mima7 == mima3 && mima8 == mima4)
	{

		AiP650_Set_1(0x68, DISPLAY_CODE[13]);
		checkResult();
		delay_ms(800);
		menuFlag = 2; //进入灵敏度设置
	}
	else
	{
		//密码校验错误
		AiP650_Set_1(0x68, DISPLAY_CODE[15]);
		checkResult();
		delay_ms(800);
		menuFlag = 1;
		mima5 = 1;
		mima6 = 2;
		mima7 = 3;
		mima8 = 4; //密码显示数字重置
		psDigits = 0;
	}
}
/**
 * @brief  重置密码
 * @note   
 * @retval None
 */
void resetPassword()
{
	mima1 = mima5;
	mima2 = mima6;
	mima3 = mima7;
	mima4 = mima8;
	//保存密码
	saveeepro();
	Delay_ms(300);
	menuFlag = 0; //密码修改完成 回到首页
	mima5 = 1;
	mima6 = 2;
	mima7 = 3;
	mima8 = 4;
}

/**
 * @brief  校验结果的UI显示
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
 * @brief 灵敏度显示
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
 * @brief   按键扫描---使用按钮时开启
 * @note   按钮地址： A-0x47,B-0x4F,C-0x57,D-0x5F,E-0x67,F-0x6F,G-0x77
 * @retval 
 */
u8 Scan_Key()
{
	u8 i;
	u8 rekey;
	I2CStart();
	I2CWrByte(0x49); //读按键命令
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
 * @brief  按键监听事件
 * @note   
 * @retval None
 */
void KEY_CL()
{
	u8 KEY;
	KEY = Scan_Key();
	switch (KEY)
	{
		//K1   菜单键	----------------------------------------------------
	case 0x47:
		menuFlag++;
		if (menuFlag > 4)
		{
			menuFlag = 0;
		}
		delay_ms(300);
		break;
		//K2    设置+	-------------------------------------
	case 0x4F:
		add();
		freqFlag=1;
		delay_ms(300);
		break;
		//K3    设置-		----------------------------------------
	case 0x57:
		reduce();
		delay_ms(300);
		break;
		//K4    确认	----------------------------------------
	case 0x5F: //K2
		enter();
		delay_ms(300);
		break;
	default:
	    freqFlag=0;
		break;
	}
}