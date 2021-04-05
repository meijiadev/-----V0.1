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
extern u8 alarmLine;
u8 menuFlag = 0;   //菜单标志      0:未点击按键前的样子  1：输入密码    2:灵敏度调节   4:密码重置
u8 psDigits = 0;   //正在修改的密码位数
u8 flash_flag = 0; //闪烁标志
u8 flash_M = 0;	   //闪烁计数
u8 voiceFlag = 0;  // 蜂鸣器开关 0：开 1：关
u8 longPress = 0;  //0:短按  1：进入长按准备环节  2：已经进入长按环节
u8 isPressed;	   //点击后松开的按键
u8 pressCounts;	   //按钮长按的计数
// u8 longPressed;    //已经进入长按环节

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
		if (longPress==0)
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
		//显示频率
		AiP650_Set_1(0x68, DISPLAY_CODE[16]); //F
		AiP650_Set_1(0x6A, DISPLAY_CODE[10]);
		AiP650_Set_1(0x6C, DISPLAY_CODE[Freq_Parm % 100 / 10]);
		AiP650_Set_1(0x6E, DISPLAY_CODE[Freq_Parm % 10]);
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
		menuFlag = 3;
		UartSend(Freq_Parm);
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
		if (voiceFlag == 0)
		{
			voiceFlag = 1;
			LED6 = 0;
			delay_ms(1000);
			LED6 = 1;
		}
		else
		{
			voiceFlag = 0;
			BUZZ = 0;
			AiP650_Set_1(0x6E, DISPLAY_CODE[ALARM_NUMBER % 10] | 0x80);
			delay_ms(800);
			AiP650_Set_1(0x6E, DISPLAY_CODE[ALARM_NUMBER % 10]);
			BUZZ = 1;
		}
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
		Freq_Parm--;
		if (Freq_Parm == 255)
			Freq_Parm = 9;
		break;
	case 4:
		//密码重置
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
		passwordCheck();
		break;
	case 2:
		menuFlag = 0;
		alarmLine = 60 + (99 - dB);
		savePassword();
		break;
	case 3:
		menuFlag = 0;
		saveFreq(Freq_Parm);
		break;
	case 4:
		resetPassword();
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
	savePassword();
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
 * @brief  重置所有参数
 * @note   
 * @retval None
 */
void reset()
{
	Freq_Parm = 2;
	dB = 90;
	mima1 = 1;
	mima2 = 2;
	mima3 = 3;
	mima4 = 4;
	savePassword();
	saveFreq(Freq_Parm);
	ALARM_NUMBER = 0;
	PEOPLE_NUMBER = 0;
	BUZZ = 0;
	delay_ms(600);
	BUZZ = 1;
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
		//K1 菜单键
	case 0x47:
		if (menuFlag == 0)
		{
			menuFlag = 1;
		}
		else if (menuFlag == 1 || menuFlag == 4) //当菜单层在输入密码和重设密码时，按菜单键执行换位操作
		{
			psDigits++;
			if (psDigits > 3)
			{
				psDigits = 0;
			}
		}
		isPressed = KEY;
		delay_ms(300);
		break;
		//K2  设置+
	case 0x4F:
		add();
		isPressed = KEY;
		//freqFlag=1;
		delay_ms(300);
		break;
		//K3  设置-
	case 0x57:
		reduce();
		isPressed = KEY;
		delay_ms(300);
		break;
		//K4  确认
	case 0x5F: //K2
		isPressed = KEY;
		switch (longPress)
		{
		case 0:       //第一次点击
			pressCounts = 0;
			longPress = 1;
			delay_ms(500);
			break;
		case 1:      //进入长按环节
			if (pressCounts == 10)
			{
				//长按3s
				if (longPress == 1)
				{
					longPress = 2; //进入长按环节，避免重复执行长按的操作
				}
			}
			else
			{
				delay_ms(300);
				pressCounts++;
				AiP650_DisPlayFour(8888);
			    AiP650_DisPlayFour_1(8888);
			}
			break;
		case 2: 
		     //长按三秒后
			//重置所有参数
			reset();
			break;
		default:
			break;
		}
		break;
	default: //松开按键和未执行按键操作时
		longPress = 0;
		pressCounts = 0;
		if (isPressed == 0x5F)
		{
			AiP650_DisPlayFour(PEOPLE_NUMBER);
			enter();
			delay_ms(300);
			isPressed = 0;
		}
		break;
	}
}