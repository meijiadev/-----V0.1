#include "STC8G.H"
#include <string.h>
#include <stdio.h>
#include <intrins.h>
#include "adc.h"
#include "main.h"
#include "AIP650.h"

u16 ADC_Data0 = 0;


/*
*@brief      ADC初始化
*@param      adcn            选择ADC通道
*@param      speed      		ADC时钟频率
*@return     void
* Sample usage:   adc_init(ADC_P10,ADC_SYSclk_DIV_2);//初始化P1.0为ADC功能,ADC时钟频率：SYSclk/2
*/
void adc_init(ADC_SPEED_enum speed)
{
	P_SW2 |= 0x80;
	ADCTIM=0x3f;
	P_SW2 &=0x7f;
	ADC_CONTR|=1<<7 ;        //打开ADC电源   建议在空闲模式和掉电模式前关闭电源
	ADC_CONTR &=0xf0;       // 清除ADC_CHS 
    ADCCFG|=speed&0x0f;      //设置 ADC时钟频率 默认 0000 SYSclk/2/1 
	ADCCFG|=0x20;            //ADCCFG:1101 1110  设置右对齐 
	
}

//*
//  @brief      ADC转换一次
//  @param      adcn            选择ADC通道
//  @param      resolution      分辨率
//  @return     void
//  Sample usage:               adc_convert(ADC_P10, ADC_10BIT);
//*
int adc_once(ADCN_enum adcn, ADCRES_enum resolution)
{
	u16 adc_value;
	ADC_CONTR &=0xf0;         //清除ADCCHS(3:0) 
	ADC_CONTR |=adcn;         //选择ADC模拟通道 
	ADC_CONTR|=0x40;         //开始ADC转换，转换完成后硬件自动将此位清零
	_nop_();
	_nop_();
	while (!(ADC_CONTR & 0x20));				// 查询 ADC 完成标志
	ADC_CONTR &= ~0x20; // 清完成标志
	// adc_value = ADC_RES;  //存储 ADC 的 10 位结果的高 2 位
	// adc_value <<= 8;
	// adc_value |= ADC_RESL;  //存储 ADC 的 10 位结果的低 8 位
	_nop_();
	adc_value=(ADC_RES<<8)|ADC_RESL;
	adc_value >>= resolution; //取多少位
	return adc_value;
}

void closAdc()
{
	ADC_CONTR=0;
}

/************************************************** 
  功能描述: //ADC处理
	入口参数：
  说    明：                        
**************************************************/
void ADC()
{
	
	u16 ADCResult0 ;
    float temp;
	ADC_Data0 = adc_once(ADC_P10, ADC_10BIT); //采集一次ADC，精度10位 
    temp=(float)4900/(float)1024;
	AiP650_DisPlayFour_1(ADC_Data0);
	ADCResult0=(u16)(temp*(float)ADC_Data0);
	AiP650_DisPlayFour(ADCResult0); 
}
