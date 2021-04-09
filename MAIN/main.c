#include "STC8G.H"
#include "intrins.h"
#include "main.h"
//#include	"GPIO.h"
#include "delay.h"
#include "AIP650.h"
#include "PWM.h"
#include "GUI.h"
#include "EEPROM.h"
#include "ADC.h"
#include "uart.h"
#include "IR.h"

extern u8 menuFlag; //菜单


/**
 * @brief  IO口初始化
 * @note   
 * @retval None
 */
void IO_init(void)
{
	P0M1 &= 0x00;
	P0M0 &= 0x00; //设置P0为准双向口
	P1M1 &= 0x00;
	P1M0 &= 0x00; //设置P1为准双向口
	P2M1 &= 0x00;
	P2M0 &= 0x00; //设置P2为准双向口
	P3M1 &= 0x00;
	P3M0 &= 0x00; //设置P3为准双向口
	P4M1 &= 0x00;
	P4M0 &= 0x00; //设置P4为准双向口
	P5M1 &= 0x00;
	P5M0 &= 0x00; //设置P5为准双向口
	P6M1 &= 0x00;
	P6M0 &= 0x00; //设置P6为准双向口
	P7M1 &= 0x00;
	P7M0 &= 0x00; //设置P7为准双向口
}


/**
 * @brief  主函数
 * @note   
 * @retval None
 */
void main()
{
	IO_init();
	Light_Level_Set(6);
	Light_Level_Set_1(6);
	EEPROM_init();
	adc_init(ADC_SYSclk_DIV_2); //初始化ADC,P1.0通道 ，ADC时钟频率：SYSclk/2
	menuFlag = 0;
	UartInit();
	delay_ms(10000);
	initHardware();
	delay_ms(5000);
	while (1)
	{
		menuUI();
		KEY_CL();        
		if (menuFlag==0)
		{
		IRCheck();
		Fore_XS();        
		IR_Fore();
		ADC();
		}
	}

}

/**
 * @brief  初始化硬件
 * @note   
 * @retval None
 */
void initHardware(){
	u16 i;
	for ( i = 0; i < 2; i++)
	{
	LED1=0;
	delay_ms(800);
	LED1=1;
	LED2=0;
	delay_ms(800);
	LED2=1;
	LED3=0;
	delay_ms(800);
	LED3=1;
	LED4=0;
	delay_ms(800);
	LED4=1;
	LED5=0;
	delay_ms(800);
	LED5=1;
	LED6=0;
	delay_ms(800);
	LED6=1;	
	}
	BUZZ=0;
	delay_ms(800);
	BUZZ=1;

}