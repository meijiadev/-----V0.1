#ifndef __GUI_H
#define __GUI_H

//#include  "main.h"

void meun_UI();            //菜单显示
void password_UI();        //密码菜单
void ADD_UI();             //+键操作
void RED_UI();					   //-键操作
void MM_AIP650();          //密码判断显示
void ENT_UI();             //确认键操作
void PASS_DB();            //密码判断
void LMD_XZ();             //灵敏度显示
void Freq_disp();          //频率操作
extern u8 Scan_Key(void);                                 // 按键扫描
void KEY_CL();                                            //按键处理
#endif