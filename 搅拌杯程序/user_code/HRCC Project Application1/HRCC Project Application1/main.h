#ifndef __MAIN_H
#define __MAIN_H

#include <hic.h>
#include "Inc_user\user_function.h"
#include "Inc_user\software_Time.h"
#include "Inc_user\key.h"
#include "inc_user\scan_LED.h"
#include <math.h>
#define CLRWDT()   {__Asm CWDT;}        //宏定义清狗指令

unsigned long Get_Sys_time();

extern unsigned char display_buf[18];

extern unsigned char buzzer_flag;


extern unsigned char temperature;//温度值 0~99
extern unsigned char Vbat_val;   //电量%  0~99

#endif