#ifndef __ADC_H
#define __ADC_H





//此枚举定义不允许用户修改
typedef enum
{
	ADC_P10 = 0,
	ADC_P11,
	ADC_P12,
	ADC_P13,
	ADC_P14,
	ADC_P15,
	ADC_P16,
	ADC_P17,

	ADC_P00,
	ADC_P01,
	ADC_P02,
	ADC_P03,
	ADC_P04,
	ADC_P05,
	ADC_P06,
	ADC_POWR = 0x0f, //内部AD 1.19V
} ADCN_enum;

//此枚举定义不允许用户修改
typedef enum
{
	ADC_SYSclk_DIV_2 = 0,
	ADC_SYSclk_DIV_4,
	ADC_SYSclk_DIV_6,
	ADC_SYSclk_DIV_8,
	ADC_SYSclk_DIV_10,
	ADC_SYSclk_DIV_12,
	ADC_SYSclk_DIV_14,
	ADC_SYSclk_DIV_16,
	ADC_SYSclk_DIV_18,
	ADC_SYSclk_DIV_20,
	ADC_SYSclk_DIV_22,
	ADC_SYSclk_DIV_24,
	ADC_SYSclk_DIV_26,
	ADC_SYSclk_DIV_28,
	ADC_SYSclk_DIV_30,
	ADC_SYSclk_DIV_32,
} ADC_SPEED_enum;

//此枚举定义不允许用户修改
typedef enum // 枚举ADC通道
{
	ADC_10BIT = 0, //10位分辨率
	ADC_9BIT,	   //9位分辨率
	ADC_8BIT,	   //8位分辨率

} ADCRES_enum;

void adc_init(ADC_SPEED_enum speed);
int adc_once(ADCN_enum adcn, ADCRES_enum resolution);
void ADC();
void offLED();
#endif