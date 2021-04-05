#include "STC8G.h"
#include "main.h"
#include "IR.h"
#include "uart.h"
#include "AIP650.h"
#include "ADC.h"

u8 IR_ON=0;           //���⿪�ر�־
extern u16 PEOPLE_NUMBER;         //������
u8 IR_ONM = 0;      //���⿪�ؼ���
    
/**
 * @brief  �������
 * @note   
 * @retval None
 */
void IRCheck()
{
  
  // ��һ�������⵽���˲��ұ�־λ�ǹرյ�
  if ((IR1==0||IR2==0)&&IR_ON==0)
  {
   UartSend((u8)IR2);     //���˽��밲����
   IR_ON=1;  //�Է���ͬһ���˵�����¶�ν���ѭ��
   PEOPLE_NUMBER++;
  }

  if(IR1==1&&IR2==1&&IR_ON==1)
  {
    UartSend((u8)IR2);
    IR_ONM++;
    if (IR_ONM>120)
    {
      IR_ONM=0;
      IR_ON=0;//��δ��⵽��ʱ����һֱ���뵽���������
      //UartSend((u8)IR2);  //�뿪������  
    }
  }
}

