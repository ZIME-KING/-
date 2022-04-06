/*
 * software_Time.c
 *
 *  Created on: 2020年9月10日
 *      Author: champion
 */
#include "../main.h"
#include "../inc_user/software_Time.h"

 TIME_TYPE_ST Task_1;
 TIME_TYPE_ST Task_5;
 TIME_TYPE_ST Task_50;
 TIME_TYPE_ST Task_100;
 TIME_TYPE_ST Task_200;
 TIME_TYPE_ST Task_500;
 TIME_TYPE_ST Task_1000;

 //__attribute__机制在main之前运行一次 set_time
 
 //static attribute((constructor)) void SetTime();



//设定间隔时间
void SetTime(){
	Task_1.TimeInter     = 1;//设定间隔时间
	Task_5.TimeInter      = 5;
	Task_50.TimeInter    = 50;
	Task_100.TimeInter   = 100;
	Task_200.TimeInter   = 200;
	Task_500.TimeInter   = 500;
	Task_1000.TimeInter  = 1000;
}
void GetTime(TIME_TYPE_ST *TimeType)
{
    TimeType->TimeStart = Get_Sys_time();//获取起始时间
}
 
uint8_t CompareTime(TIME_TYPE_ST *TimeType)//每隔1毫秒，计数器就会增加1
{
    return ((Get_Sys_time()-TimeType->TimeStart) >= TimeType->TimeInter);
}
