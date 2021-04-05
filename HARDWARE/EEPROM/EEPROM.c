#include "STC8G.H"
#include "EEPROM.h"
#include "main.h"
#include "uart.h"

bit flag_eeprom1 = 1; //����洢�ı�־λ

u16 PEOPLE_NUMBER=0;      //��������
u8  PEOPLE_NUMBER_H;     //���������ĸ߰�λ
u8  PEOPLE_NUMBER_L;     //���������ĵͰ�λ

u16 ALARM_NUMBER=0;       //��������
u8  ALARM_NUMBER_H;     //���������ĸ߰�λ
u8  ALARM_NUMBER_L;    //���������ĵͰ�λ



//----��������--------------------
extern u8 mima1;
extern u8 mima2;
extern u8 mima3;
extern u8 mima4;
extern u8 dB;
extern u8 Freq_Parm;
extern u8 alarmLine;



/************************************************** 
  ��������: ��������
	��ڲ�����
  ˵    ����                        
**************************************************/
void IapIdle()
{
	IAP_CONTR = 0;	  //�ر�IAP����
	IAP_CMD = 0;	  //�������Ĵ���
	IAP_TRIG = 0;	  //��������Ĵ���
	IAP_ADDRH = 0x80; //װ��ַ���õ���IAP����
	IAP_ADDRL = 0;
}
/************************************************** 
  ��������: ��ȡһ���ֽں���
	��ڲ�����
  ˵    ����                        
**************************************************/
u8 IapReadByte(u16 addr)
{
	u8 dat;
	IAP_CONTR = ENABLE_IAP;
	IAP_TPS = 24; //���ò�д�ȴ�����24MHZ  8GоƬ����
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
  ��������: д��һ���ֽں���
	��ڲ�����addr 
  ˵    ����                        
**************************************************/
void IapProgramByte(u16 addr, u8 dat)
{
	IAP_CONTR = ENABLE_IAP;
	IAP_TPS = 24; //���ò�д�ȴ�����24MHZ  8GоƬ����
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
  ��������: ����һ���ֽں���
	��ڲ�����
  ˵    ����                        
**************************************************/
void IapEraseSector(u16 addr)
{
	IAP_CONTR = ENABLE_IAP;
	IAP_TPS = 24; //���ò�д�ȴ�����24MHZ  8GоƬ����
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
  ��������: EEPROM��ʼ��
	��ڲ�����
  ˵    ����                        
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
		savePassword(); //����洢
	}

}

/**
 * @brief ��������
 * @note   
 * @retval None
 */
void savePassword()
{
	IapEraseSector(SECTION_1);			 //����0x01��ַ�е�����	  һ��Ҫ�Ȳ�����д��  ͬһ��ַ
	IapProgramByte(0x01, mima1); //������ɾͿ���д����
	IapProgramByte(0x02, mima2);
	IapProgramByte(0x03, mima3);
	IapProgramByte(0x04, mima4);
	IapProgramByte(0x05, dB);
}

/**
 * @brief  ����Ƶ��
 * @note   
 * @retval None
 */
void saveFreq(u8 dat){
    IapEraseSector(SECTION_2);
	IapProgramByte(0x201,dat);
}

// /**
//  * @brief  ���澭����������(�ݲ���Ҫ)
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
//  * @brief  �������ʼ��
//  * @note   
//  * @retval None
//  */
// void brownoutDetectInit(){
	
//     CMPCR2 =0x00;
// 	CMPCR1 =0x80;               //ʹ�ܱȽ���ģ��
// 	CMPCR1 |=0x01;               //ʹ�ܱȽ����½������ж�
// 	CMPCR1 &=~0x08;              //P3.7ΪCMP+�����
// 	CMPCR1 &=~0x04;              //�ڲ� 1.19V�ο��ź�ԴΪCMP-�����
// 	CMPCR1 |=0x02;              //ʹ�ܱȽ������
// 	EA=1;                       //ȫ���жϴ�
// 	UartSend(0x00);
// }

// void CMP_Isr()interrupt 21{
// 	CMPCR1 &=~0x40;                             //����жϱ�־
// 	UartSend(0x11);

// }


/************************EEPROM����**********************************/
