#include "STC8G.H"
#include <string.h>
#include <stdio.h>
#include <intrins.h>
#include "ADC.h"
#include "main.h"
#include "AIP650.h"
#include "uart.h"


extern u8 IR_ON;                  //�Ƿ����˽���
extern u16 ALARM_NUMBER;         //��������
extern u8 voiceFlag;            //��������
extern u8 dB;                  //������
bit    isCountAN=0;           //�Ƿ��Ѿ����㱾�α�������
u8 alarmLine=60;   

/*
*@brief      ADC��ʼ��
*@param      adcn       ѡ��ADCͨ��
*@param      speed      ADCʱ��Ƶ��
*@return     void
* Sample usage:   adc_init(ADC_P10,ADC_SYSclk_DIV_2);//��ʼ��P1.0ΪADC����,ADCʱ��Ƶ�ʣ�SYSclk/2
*/
void adc_init(ADC_SPEED_enum speed)
{
	P_SW2 |= 0x80;
	ADCTIM=0x3f;
	P_SW2 &=0x7f;
	ADC_CONTR|=1<<7 ;        //��ADC��Դ   �����ڿ���ģʽ�͵���ģʽǰ�رյ�Դ
	ADC_CONTR &=0xf0;       // ���ADC_CHS 
    ADCCFG|=speed&0x0f;      //���� ADCʱ��Ƶ�� Ĭ�� 0000 SYSclk/2/1 
	ADCCFG|=0x20;            //ADCCFG:1101 1110  �����Ҷ��� 	
}

/*
 *  @brief     ADCת��һ��
 * @param      adcn            ѡ��ADCͨ��
 * @param     resolution      �ֱ���
 * @return    ת�����
 * Sample usage: adc_convert(ADC_P10, ADC_10BIT);
 */
int adc_once(ADCN_enum adcn, ADCRES_enum resolution)
{
	u16 adc_value;
	ADC_CONTR &=0xf0;         //���ADCCHS(3:0) 
	ADC_CONTR |=adcn;         //ѡ��ADCģ��ͨ�� 
	ADC_CONTR|=0x40;         //��ʼADCת����ת����ɺ�Ӳ���Զ�����λ����
	_nop_();
	_nop_();
	_nop_();
	while (!(ADC_CONTR & 0x20));				// ��ѯ ADC ��ɱ�־
	ADC_CONTR &= ~0x20; // ����ɱ�־
	adc_value=(ADC_RES<<8)|ADC_RESL;
	adc_value >>= resolution; //ȡ����λ
	return adc_value;
}


/************************************************** 
  ��������: //ADC����
	��ڲ�����
  ˵    ����                        
**************************************************/
void ADC()
{
	if (IR_ON==1)
	{
	//u16 ADCResult0 ;
	u16 ADC_Data0 ;
    //float temp;
	ADC_Data0 = adc_once(ADC_P10, ADC_10BIT); //�ɼ�һ��ADC������10λ 
    //temp=(float)4900/(float)1024;
	//ADCResult0=(u16)(temp*(float)AD_Data0);  ���������ѹ  
	if (ADC_Data0>alarmLine)
	{
		if (isCountAN==0)
		{
			isCountAN=1;
			ALARM_NUMBER++;
		}
	}
	UartSend(ADC_Data0);
	if(ADC_Data0>alarmLine&&ADC_Data0<200)
	{
	 LED1=0;
	 if (voiceFlag==0)
	 BUZZ=0;
	}else if (ADC_Data0>200&&ADC_Data0<400)
	{
	 LED1=0;
	 LED2=0; 
	 if (voiceFlag==0)
	 BUZZ=0;
	}else if (ADC_Data0>400&&ADC_Data0<600)
	{
	 LED1=0;
	 LED2=0;
	 LED3=0;
	 if (voiceFlag==0)
	 BUZZ=0;
	}else if (ADC_Data0>600&&ADC_Data0<800)
	{
	 LED1=0;
	 LED2=0;
	 LED3=0;
	 LED4=0;
	 if (voiceFlag==0)
	 BUZZ=0;
	}else if (ADC_Data0>800&&ADC_Data0<1000)
	{
	 LED1=0;
	 LED2=0;
	 LED3=0;
	 LED4=0;
	 LED5=0;	
	 if (voiceFlag==0)
	 BUZZ=0;
	}else if (ADC_Data0>1000)
	{
	 LED1=0;
	 LED2=0;
	 LED3=0;
	 LED4=0;
	 LED5=0;
	 LED6=0;
	 if (voiceFlag==0)
	 BUZZ=0;
	}	
	}else if (IR_ON==0)
	{
		//��������֮�����в�����λ
		isCountAN=0;
		offLED();
		BUZZ=1;        //�رշ�����
	}  
}

/*
 ����������Ϩ�����е�LED��
*/
void offLED(){
	LED1=1;
	LED2=1;
    LED3=1;
    LED4=1;
	LED5=1;
	LED6=1;
}
