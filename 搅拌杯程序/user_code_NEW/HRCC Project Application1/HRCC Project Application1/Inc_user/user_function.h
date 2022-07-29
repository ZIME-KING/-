#ifndef __USER_FUNCTION_H_
#define __USER_FUNCTION_H_
typedef unsigned char uchar;
typedef unsigned int uint;


void Uart_Init();
void ADC_init() ;
void ADC_dis_init();

void UART_send(uchar *str,uchar ch,uint value);

void User_Get_measure_Val_10ms();
//void Get_ADC_Val(*unsigned int Vbat_val,*unsigned int Temp_val);
void Send_test();
void User_Get_measure_Val();
extern float vcc_val;

extern float RV;
extern float RT;
extern float Tmp;


#endif