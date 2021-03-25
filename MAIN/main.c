#include "STC8G.H"
#include "intrins.h"
#include "main.h"
//#include	"GPIO.h"
#include "delay.h"
#include "AIP650.h"
#include "PWM.h"
#include "GUI.h"
#include "EEPROM.h"
#include "adc.h"

extern u8 menu; //�˵�

/********************************
����������IO�ڳ�ʼ��
��ڲ�������
����ֵ����
*********************************/

void IO_init(void)
{
	P0M1 &= 0x00;
	P0M0 &= 0x00; //����P0Ϊ׼˫���
	P1M1 &= 0x00;
	P1M0 &= 0x00; //����P1Ϊ׼˫���
	P2M1 &= 0x00;
	P2M0 &= 0x00; //����P2Ϊ׼˫���
	P3M1 &= 0x00;
	P3M0 &= 0x00; //����P3Ϊ׼˫���
	P4M1 &= 0x00;
	P4M0 &= 0x00; //����P4Ϊ׼˫���
	P5M1 &= 0x00;
	P5M0 &= 0x00; //����P5Ϊ׼˫���
	P6M1 &= 0x00;
	P6M0 &= 0x00; //����P6Ϊ׼˫���
	P7M1 &= 0x00;
	P7M0 &= 0x00; //����P7Ϊ׼˫���
}

/********************************
����������������
��ڲ�������
����ֵ����
*********************************/
void main()
{
	IO_init();
	Light_Level_Set(6);
	Light_Level_Set_1(6);
	EEPROM_init();
	adc_init(ADC_SYSclk_DIV_2); //��ʼ��ADC,P1.0ͨ�� ��ADCʱ��Ƶ�ʣ�SYSclk/2
	menu = 0;
	while (1)
	{
		meun_UI();
		KEY_CL();         
		Fore_XS();        
		IR_Fore();
		ADC();
		//Delay_ms(1000);
	}
}