#include "STC8G.H"
#include "GUI.h"
#include "main.h"
#include "delay.h"
#include "AIP650.h"
#include "EEPROM.h"

//通过extern可以合法使用已经定义的外部变量
extern u8 DISPLAY_CODE[19];
extern u8 Freq_Parm; //频率

//extern u8  VOI_M;
//extern u8  VOI;                           //按键操作标志

u8 menu = 0;	  //菜单
u8 menu_flag = 0; //菜单标志
u16 Pass = 0;	  //通过次数
u16 Alarm = 0;	  //报警次数

u8 flash_flag = 0; //闪烁标志
u8 flash_M = 0;	   //闪烁计数
//---灵敏度-----------------------------------------
u8 LMD_1;

//--------保存密码-------------
u8 mima1 = 0;
u8 mima2 = 0;
u8 mima3 = 0;
u8 mima4 = 0;
//--------输入密码-------------
u8 mima5 = 1;
u8 mima6 = 2;
u8 mima7 = 3;
u8 mima8 = 4;

u8 PA_flag;		  //密码位数标志
u8 freq_flag = 0; //频率/声音显示标志
u8 voice = 0;	  //声音开关标志

/********************************
功能描述：UI界面
入口参数：无
返 回 值：无
*********************************/
void meun_UI()
{
	switch (menu)
	{
	case 0:							 //测试界面
		AiP650_DisPlayFour_1(Alarm); //报警次数
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
功能描述：密码界面
入口参数：无
返 回 值：无
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
  功能描述: 加按钮处理
	入口参数：
  说    明：                        
**************************************************/
void ADD_UI()
{
	switch (menu)
	{
		//---频率调节---------------------------------
	case 0:
		freq_flag = 1; //显示标志
		Freq_Parm++;
		if (Freq_Parm > 9)
			Freq_Parm = 1;

		break;
		//---密码调节---------------------------------
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
		//---灵敏度调节---------------------------------
	case 2:
		LMD_1++;
		if (LMD_1 > 99)
			LMD_1 = 1;
		break;
		//---密码调节---------------------------------
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
  功能描述: 减按钮处理
	入口参数：
  说    明：                        
**************************************************/
void RED_UI()
{
	switch (menu)
	{
		//---声音开关---------------------------------
	case 0:
		voice++;
		if (voice > 1)
			voice = 0;
		break;
		//---密码调节---------------------------------
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
		//---灵敏度调节---------------------------------
	case 2:
		LMD_1--;
		if (LMD_1 == 255)
			LMD_1 = 99;
		break;
		//---密码调节---------------------------------
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
  功能描述: 确定按钮处理
	入口参数：
  说    明：                        
**************************************************/
void ENT_UI()
{

	switch (menu)
	{
		//-----密码确认-------------------------------
	case 1:
		PASS_DB();
		break;
		//-----灵敏度确认-------------------------------
	case 2:
		menu = 3;
		menu_flag = 2;
		break;
		//-----修改密码确认-------------------------------
	case 3:

		menu = 0;
		menu_flag = 0;
		break;

	default:
		break;
	}
}

/************************************************** 
  功能描述: 密码对比
	入口参数：
  说    明：                        
**************************************************/
void PASS_DB()
{

	//-----超级密码判断---------------------------------------------------
	if (mima5 == 8 && mima6 == 8 && mima7 == 8 && mima8 == 8)
	{

		AiP650_Set_1(0x68, DISPLAY_CODE[13]);
		MM_AIP650();
		delay_ms(800);
		//			  CD_flag=4;ID1=0;
		mima5 = 1;
		mima6 = 2;
		mima7 = 3;
		mima8 = 4; //密码显示数字重置
	}
	//-----密码判断正确---------------------------------------------------
	else if (mima5 == mima1 && mima6 == mima2 && mima7 == mima3 && mima8 == mima4)
	{

		AiP650_Set_1(0x68, DISPLAY_CODE[13]);
		MM_AIP650();

		delay_ms(800);
		menu = 2;
		menu_flag = 1; //进入灵敏度设置
	}
	//-----密码判断错误---------------------------------------------------
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
		mima8 = 4; //密码显示数字重置
	}
}

/************************************************** 
  功能描述: 密码确认显示信息
	入口参数：
  说    明：                        
**************************************************/
void MM_AIP650()
{
	AiP650_Set_1(0x6A, DISPLAY_CODE[0]);
	AiP650_Set_1(0x6C, DISPLAY_CODE[0]);
	AiP650_Set_1(0x6E, DISPLAY_CODE[0]);
}

/************************************************** 
  功能描述: 灵敏度显示
	入口参数：
  说    明：                        
**************************************************/
void LMD_XZ()
{
	AiP650_Set_1(0x68, DISPLAY_CODE[1]);
	AiP650_Set_1(0x6A, DISPLAY_CODE[10]);
	AiP650_Set_1(0x6C, DISPLAY_CODE[LMD_1 % 100 / 10]);
	AiP650_Set_1(0x6E, DISPLAY_CODE[LMD_1 % 10]);
}

/************************************************** 
  功能描述: 频率设置显示
	入口参数：
  说    明：                        
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
				{AiP650_DisPlayFour(Pass);}		                     //通过次数
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

//----按键扫描---使用按钮时开启------------------------------
//按钮地址： A-0x47,B-0x4F,C-0x57,D-0x5F,E-0x67,F-0x6F,G-0x77
//
//---------------------------------------------

u8 Scan_Key(void)
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
 * 按键处理---使用按钮时开启
 * */
void KEY_CL()
{
  u8 KEY;
  KEY = Scan_Key();
  switch (KEY)
  {
    //K1   菜单键	----------------------------------------------------
  case 0x47:
    if (menu == 0 && menu_flag == 0)
    {
      menu = 1;
      PA_flag = 3;
    } //主界面进入密码界面
    if (menu == 1 || menu == 3)
    {
      PA_flag++;
      if (PA_flag > 3)
        PA_flag = 0;
    }
    delay_ms(300);
    break;

    //K2    设置+	-------------------------------------
  case 0x4F:
    ADD_UI();
    freq_flag = 1;
    delay_ms(300);
    break;
    //K3    设置-		----------------------------------------
  case 0x57:
    RED_UI();
    delay_ms(300);
    LED3 = 0;
    break;
    //K4    确认	----------------------------------------
  case 0x5F: //K2
    ENT_UI();
    delay_ms(300);
    break;
  default:
    freq_flag = 0;
    break;
  }
}
