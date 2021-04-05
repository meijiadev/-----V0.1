#include "STC8G.H"
#include "EEPROM.h"
#include "main.h"
#include "uart.h"

bit flag_eeprom1 = 1; //掉电存储的标志位

u16 PEOPLE_NUMBER=0;      //经过人数
u8  PEOPLE_NUMBER_H;     //经过人数的高八位
u8  PEOPLE_NUMBER_L;     //经过人数的低八位

u16 ALARM_NUMBER=0;       //报警人数
u8  ALARM_NUMBER_H;     //报警人数的高八位
u8  ALARM_NUMBER_L;    //报警人数的低八位



//----密码数据--------------------
extern u8 mima1;
extern u8 mima2;
extern u8 mima3;
extern u8 mima4;
extern u8 dB;
extern u8 Freq_Parm;
extern u8 alarmLine;



/************************************************** 
  功能描述: 操作函数
	入口参数：
  说    明：                        
**************************************************/
void IapIdle()
{
	IAP_CONTR = 0;	  //关闭IAP功能
	IAP_CMD = 0;	  //清除命令寄存器
	IAP_TRIG = 0;	  //清除触发寄存器
	IAP_ADDRH = 0x80; //装地址设置到非IAP区域
	IAP_ADDRL = 0;
}
/************************************************** 
  功能描述: 读取一个字节函数
	入口参数：
  说    明：                        
**************************************************/
u8 IapReadByte(u16 addr)
{
	u8 dat;
	IAP_CONTR = ENABLE_IAP;
	IAP_TPS = 24; //设置擦写等待参数24MHZ  8G芯片增加
	IAP_CMD = CMD_READ;
	IAP_ADDRL = addr;
	IAP_ADDRH = addr >> 8;
	IAP_TRIG = 0x5a;
	IAP_TRIG = 0xa5;
	_nop_();
	_nop_();
	_nop_();
	dat = IAP_DATA;
	IapIdle();
	return dat;
}
/************************************************** 
  功能描述: 写入一个字节函数
	入口参数：addr 
  说    明：                        
**************************************************/
void IapProgramByte(u16 addr, u8 dat)
{
	IAP_CONTR = ENABLE_IAP;
	IAP_TPS = 24; //设置擦写等待参数24MHZ  8G芯片增加
	IAP_CMD = CMD_PROGRAM;
	IAP_ADDRL = addr;
	IAP_ADDRH = addr >> 8;
	IAP_DATA = dat;
	IAP_TRIG = 0x5a;
	IAP_TRIG = 0xa5;
	_nop_();
	_nop_();
	_nop_();
	IapIdle();
}
/************************************************** 
  功能描述: 擦除一个字节函数
	入口参数：
  说    明：                        
**************************************************/
void IapEraseSector(u16 addr)
{
	IAP_CONTR = ENABLE_IAP;
	IAP_TPS = 24; //设置擦写等待参数24MHZ  8G芯片增加
	IAP_CMD = CMD_ERASE;
	IAP_ADDRL = addr;
	IAP_ADDRH = addr >> 8;
	IAP_TRIG = 0x5a;
	IAP_TRIG = 0xa5;
	_nop_();
	_nop_();
	_nop_();
	IapIdle();
}

/************************************************** 
  功能描述: EEPROM初始化
	入口参数：
  说    明：                        
**************************************************/
void EEPROM_init()
{
	mima1 = IapReadByte(0x01);
	mima2 = IapReadByte(0x02);
	mima3 = IapReadByte(0x03);
	mima4 = IapReadByte(0x04);
	dB = IapReadByte(0x05);
	Freq_Parm=IapReadByte(0x201);    
	if (dB>100)
	    dB=80;
	alarmLine=60+(99-dB);
	if (Freq_Parm > 9)
		Freq_Parm = 2;
	if (mima1 >9)
	{
		mima1 = 1;
		mima2 = 2;
		mima3 = 3;
		mima4 = 4;
		savePassword(); //掉电存储
	}

}

/**
 * @brief 保存密码
 * @note   
 * @retval None
 */
void savePassword()
{
	IapEraseSector(SECTION_1);			 //擦除0x01地址中的数据	  一定要先擦除再写进  同一地址
	IapProgramByte(0x01, mima1); //擦除完成就可以写入了
	IapProgramByte(0x02, mima2);
	IapProgramByte(0x03, mima3);
	IapProgramByte(0x04, mima4);
	IapProgramByte(0x05, dB);
}

/**
 * @brief  保存频率
 * @note   
 * @retval None
 */
void saveFreq(u8 dat){
    IapEraseSector(SECTION_2);
	IapProgramByte(0x201,dat);
}

// /**
//  * @brief  保存经过的总人数(暂不需要)
//  * @note   
//  * @retval None
//  */
// void savePeopleNumber(){
// 	PEOPLE_NUMBER_L=PEOPLE_NUMBER;
// 	PEOPLE_NUMBER_H=PEOPLE_NUMBER>>8;
// 	IapEraseSector(SECTION_2);
// 	IapProgramByte(PEOPLE_NUM_H_ADDR,PEOPLE_NUMBER_H);
// 	IapProgramByte(PEOPLE_NUM_L_ADDR,PEOPLE_NUMBER_L);
// }


// /**
//  * @brief  掉电检测初始化
//  * @note   
//  * @retval None
//  */
// void brownoutDetectInit(){
	
//     CMPCR2 =0x00;
// 	CMPCR1 =0x80;               //使能比较器模块
// 	CMPCR1 |=0x01;               //使能比较器下降边沿中断
// 	CMPCR1 &=~0x08;              //P3.7为CMP+输入脚
// 	CMPCR1 &=~0x04;              //内部 1.19V参考信号源为CMP-输入脚
// 	CMPCR1 |=0x02;              //使能比较器输出
// 	EA=1;                       //全局中断打开
// 	UartSend(0x00);
// }

// void CMP_Isr()interrupt 21{
// 	CMPCR1 &=~0x40;                             //清除中断标志
// 	UartSend(0x11);

// }


/************************EEPROM结束**********************************/
