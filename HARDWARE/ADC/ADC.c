#include "STC8G.H"
#include <string.h>
#include <stdio.h>
#include <intrins.h>
#include "ADC.h"
#include "main.h"
#include "AIP650.h"
#include "uart.h"


extern u8 IR_ON;                  //是否有人进入
extern u16 ALARM_NUMBER;         //报警人数
extern u8 voiceFlag;            //声音开关
extern u8 dB;                  //灵敏度
bit    isCountAN=0;           //是否已经计算本次报警人数
u8 alarmLine=60;   

/*
*@brief      ADC初始化
*@param      adcn       选择ADC通道
*@param      speed      ADC时钟频率
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

/*
 *  @brief     ADC转换一次
 * @param      adcn            选择ADC通道
 * @param     resolution      分辨率
 * @return    转换结果
 * Sample usage: adc_convert(ADC_P10, ADC_10BIT);
 */
int adc_once(ADCN_enum adcn, ADCRES_enum resolution)
{
	u16 adc_value;
	ADC_CONTR &=0xf0;         //清除ADCCHS(3:0) 
	ADC_CONTR |=adcn;         //选择ADC模拟通道 
	ADC_CONTR|=0x40;         //开始ADC转换，转换完成后硬件自动将此位清零
	_nop_();
	_nop_();
	_nop_();
	while (!(ADC_CONTR & 0x20));				// 查询 ADC 完成标志
	ADC_CONTR &= ~0x20; // 清完成标志
	adc_value=(ADC_RES<<8)|ADC_RESL;
	adc_value >>= resolution; //取多少位
	return adc_value;
}


/************************************************** 
  功能描述: //ADC处理
	入口参数：
  说    明：                        
**************************************************/
void ADC()
{
	if (IR_ON==1)
	{
	//u16 ADCResult0 ;
	u16 ADC_Data0 ;
    //float temp;
	ADC_Data0 = adc_once(ADC_P10, ADC_10BIT); //采集一次ADC，精度10位 
    //temp=(float)4900/(float)1024;
	//ADCResult0=(u16)(temp*(float)AD_Data0);  计算输出电压  
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
		//当人走了之后将所有参数复位
		isCountAN=0;
		offLED();
		BUZZ=1;        //关闭蜂鸣器
	}  
}

/*
 功能描述：熄灭所有的LED灯
*/
void offLED(){
	LED1=1;
	LED2=1;
    LED3=1;
    LED4=1;
	LED5=1;
	LED6=1;
}
