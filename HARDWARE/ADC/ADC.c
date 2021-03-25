#include "STC8G.H"
#include <string.h>
#include <stdio.h>
#include <intrins.h>
#include "adc.h"
#include "main.h"
#include "AIP650.h"

u16 ADC_Data0 = 0;


/*
*@brief      ADC��ʼ��
*@param      adcn            ѡ��ADCͨ��
*@param      speed      		ADCʱ��Ƶ��
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

//*
//  @brief      ADCת��һ��
//  @param      adcn            ѡ��ADCͨ��
//  @param      resolution      �ֱ���
//  @return     void
//  Sample usage:               adc_convert(ADC_P10, ADC_10BIT);
//*
int adc_once(ADCN_enum adcn, ADCRES_enum resolution)
{
	u16 adc_value;
	ADC_CONTR &=0xf0;         //���ADCCHS(3:0) 
	ADC_CONTR |=adcn;         //ѡ��ADCģ��ͨ�� 
	ADC_CONTR|=0x40;         //��ʼADCת����ת����ɺ�Ӳ���Զ�����λ����
	_nop_();
	_nop_();
	while (!(ADC_CONTR & 0x20));				// ��ѯ ADC ��ɱ�־
	ADC_CONTR &= ~0x20; // ����ɱ�־
	// adc_value = ADC_RES;  //�洢 ADC �� 10 λ����ĸ� 2 λ
	// adc_value <<= 8;
	// adc_value |= ADC_RESL;  //�洢 ADC �� 10 λ����ĵ� 8 λ
	_nop_();
	adc_value=(ADC_RES<<8)|ADC_RESL;
	adc_value >>= resolution; //ȡ����λ
	return adc_value;
}

void closAdc()
{
	ADC_CONTR=0;
}

/************************************************** 
  ��������: //ADC����
	��ڲ�����
  ˵    ����                        
**************************************************/
void ADC()
{
	
	u16 ADCResult0 ;
    float temp;
	ADC_Data0 = adc_once(ADC_P10, ADC_10BIT); //�ɼ�һ��ADC������10λ 
    temp=(float)4900/(float)1024;
	AiP650_DisPlayFour_1(ADC_Data0);
	ADCResult0=(u16)(temp*(float)ADC_Data0);
	AiP650_DisPlayFour(ADCResult0); 
}
