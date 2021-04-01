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
	// PEOPLE_NUMBER_H=IapReadByte(PEOPLE_NUM_H_ADDR);
	// PEOPLE_NUMBER_L=IapReadByte(PEOPLE_NUM_L_ADDR);
	// PEOPLE_NUMBER=PEOPLE_NUMBER_H<<8;
	// PEOPLE_NUMBER|=PEOPLE_NUMBER_L;
	// ALARM_NUMBER_H=IapReadByte(ALARM_NUM_H_ADDR);
	// ALARM_NUMBER_L=IapReadByte(ALARM_NUM_L_ADDR);
	// ALARM_NUMBER=ALARM_NUMBER_H<<8;               
	// ALARM_NUMBER|=ALARM_NUMBER_L;     
	mima1 = IapReadByte(0x01);
	mima2 = IapReadByte(0x02);
	mima3 = IapReadByte(0x03);
	mima4 = IapReadByte(0x04);
	dB = IapReadByte(0x05);

	if (mima1 == 255)
	{
		mima1 = 1;
		mima2 = 2;
		mima3 = 3;
		mima4 = 4;
		saveeepro(); //����洢
	}
	if (dB == 255)
	{
		dB = 60;
	}

	/*	
	  TAHH=TAHH_H*256+TAHH_L;
	
   if(TAHH==65535)
		{
			  TAHH=373;
			  TAHH_L=TAHH;
				TAHH_H=(TAHH>>8);		
			  dist_m1=0;
				saveeepro();                       //����洢
		}
*/
}

/**
 * @brief ����洢����������
 * @note   
 * @retval None
 */
void saveeepro()
{
	IapEraseSector(SECTION_1);			 //����0x01��ַ�е�����	  һ��Ҫ�Ȳ�����д��  ͬһ��ַ
	IapProgramByte(0x01, mima1); //������ɾͿ���д����
	IapProgramByte(0x02, mima2);
	IapProgramByte(0x03, mima3);
	IapProgramByte(0x04, mima4);
	IapProgramByte(0x05, dB);
}

/**
 * @brief  ���澭����������
 * @note   
 * @retval None
 */
void savePeopleNumber(){
	PEOPLE_NUMBER_L=PEOPLE_NUMBER;
	PEOPLE_NUMBER_H=PEOPLE_NUMBER>>8;
	IapEraseSector(SECTION_2);
	IapProgramByte(PEOPLE_NUM_H_ADDR,PEOPLE_NUMBER_H);
	IapProgramByte(PEOPLE_NUM_L_ADDR,PEOPLE_NUMBER_L);
}






/************************EEPROM����**********************************/
