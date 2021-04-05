#include "STC8G.h"
#include "main.h"
#include "IR.h"
#include "uart.h"
#include "AIP650.h"
#include "ADC.h"

u8 IR_ON=0;           //红外开关标志
extern u16 PEOPLE_NUMBER;         //人数量
u8 IR_ONM = 0;      //红外开关计数
    
/**
 * @brief  红外接收
 * @note   
 * @retval None
 */
void IRCheck()
{
  
  // 有一个红外检测到有人并且标志位是关闭的
  if ((IR1==0||IR2==0)&&IR_ON==0)
  {
   UartSend((u8)IR2);     //有人进入安检门
   IR_ON=1;  //以防在同一个人的情况下多次进入循环
   PEOPLE_NUMBER++;
  }

  if(IR1==1&&IR2==1&&IR_ON==1)
  {
    UartSend((u8)IR2);
    IR_ONM++;
    if (IR_ONM>120)
    {
      IR_ONM=0;
      IR_ON=0;//当未检测到人时不会一直进入到此条件语句
      //UartSend((u8)IR2);  //离开安检门  
    }
  }
}

