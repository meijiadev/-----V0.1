#ifndef __GUI_H
#define __GUI_H

//#include  "main.h"

void menuUI();            //菜单显示
void passwordUI();        //密码菜单
void add();             //+键操作
void reduce();					   //-键操作
void enter();             //确认键操作
void checkResult();         //密码校验结果
void passwordCheck();            //密码判断
void resetPassword();       //重置密码
void dBShow();             //灵敏度显示
void Freq_disp();          //频率操作
  u8 Scan_Key();                                 // 按键扫描
void KEY_CL();                                            //按键处理
#endif