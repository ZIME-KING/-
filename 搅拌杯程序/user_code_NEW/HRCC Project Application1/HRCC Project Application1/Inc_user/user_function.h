#ifndef __USER_FUNCTION_H_
#define __USER_FUNCTION_H_


void Uart_Init();
void ADC_init() ;
void ADC_dis_init();

//void Get_ADC_Val(*unsigned int Vbat_val,*unsigned int Temp_val);
void Send_test();
void User_Get_measure_Val();
extern float vcc_val;

extern float RV;
extern float RT;
extern float Tmp;


#endif