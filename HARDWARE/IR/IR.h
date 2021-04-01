#ifndef _IR_H_
#define _IR_H_
#include "main.h"

/*-------------------红外计数器IO定义-------------------*/
sbit IR1           =P4^0;           //红外检测1
sbit IR2           =P5^4;           //红外检测2



void IRCheck();
