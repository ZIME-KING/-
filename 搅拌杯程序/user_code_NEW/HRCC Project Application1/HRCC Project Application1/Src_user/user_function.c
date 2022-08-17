#include "../main.h"
#include "../inc_user/user_function.h"
#include <math.h>
//#include <stdlib.h>



/*********************************************************
*Copyright (C), 2020, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  adc_offset.c
*作  者:  AE Team
*版  本:  v1.0，编译于iDesigner(v4.2.3.166) + 工具链HRCC(v1.2.0.106)
*日  期:  2020/12/25
*描  述:  ADC通信演示
          PA7：模拟输入端口
          PB5：TX
          PB6：RX 
          程序将转换完的AD值通过串口发送到上位机，波特率9600bps。宏定义VDDVREF选择VDD作为参考电压正端，
          否则选择内部2.048V作为参考电压正端。
		  转换值减去offset进行ADC软件补偿，offset为802FH（内部2.048V作参考）和8030H（VDD作参考）低8位数据，
		  IAP读16位数据后需先判断是否满足高低8位取反。
		  注意：由于offset的存在，为防止溢出，转换值小于offset时，ADC结果直接归0；并且ADC最大只能测到(0xFFF-offset)。
*备  注:  本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/

//#define VDDVREF        //宏定义选择VDD作为参考电压，注释本句则选择内部2.048V作为参考电压正端
//typedef unsigned char uchar;
//typedef unsigned int uint;

uint adc_value;
uint offset_value = 0;  //保存ADC校准值
uchar str[] = "通道 的转换值为:    \r\n\0";


#define B 3950.0//温度系数
#define TN 298.15//额定温度(绝对温度加常温:273.15+25)
#define RN 100// 额定阻值(绝对温度时的电阻值100k)
#define RES 330// 分压电阻200K/330k
#define BaseVol  2.048 //ADC基准电压

float vcc_val;
float temp_vcc_val;
float RV,RT,Tmp;
float Get_Tempture(unsigned int adc)
{        //float RV,RT,Tmp;
        RV=BaseVol*(float)adc/4096.0;		//ADC为12位ADC,求出NTC电压:RV=ADCValu/4096*BaseVoltag
       // RT=RV*100/(BaseVol-RV);				//求出当前温度阻值 (BaseVoltage-RV)/R16=RV/RT;
		RT=RES/((temp_vcc_val/RV)-1);
	    Tmp=1/(1/TN+(log(RT/RN)/B))-273.15;//%RT = RN exp*B(1/T-1/TN)%

        return Tmp;
}
//————————————————
//版权声明：本文为CSDN博主「LVGRAPE」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
//原文链接：https://blog.csdn.net/u013866683/article/details/79391849



/**********************************************
函数名：UART_send(uchar *str,uchar ch,uint value)
描  述：UART发送函数
输入值：字符串指针，通道数，ADC转换值
输出值：无
返回值：无
**********************************************/
void UART_send(uchar *str,uchar ch,uint value)
{
    *(str+4) = ch+'0';
    *(str+16) = value/1000+'0';
    *(str+17) = value%1000/100+'0';
    *(str+18) = value%100/10+'0';
    *(str+19) = value%10+'0';

    while(*str)
    {
        while(!TRMT1);
        TX1B = *str++;
    }
}

/**********************************************
函数名：ADC_convert(uchar ch)
描  述：ADC转换函数
输入值：转换通道ch
输出值：无
返回值：转换的12位结果
**********************************************/
uint ADC_convert(void)
{
    ADTRG = 1;      //启动AD转换
    while(ADTRG);
    ADIF = 0;

    return (uint)ADCRH<<8 | ADCRL;
}

/*******************************************************
函数名：uint GetOffset2048(void)
描  述：获取参考电压为内部2.048V时offset值
输入值：无
输出值：无
返回值：offset值
*******************************************************/
uint GetOffset2048(void)
{
	uint value_tmp = 0;
	unsigned char gie_bk = GIE;		//备份GIE

    CLRWDT();

	while(GIE) GIE = 0;
	DATARDEN = 1;

	FRAH = 0x802F >> 8;
	FRAL = 0x802F;
	DATARDTRG = 1;
	while(DATARDTRG) ;	     //等待读完成
	__Asm TBR;		         //查表读指令
	value_tmp = (ROMDH<<8) | ROMDL;

    ROMCL = 0x00;            //退出IAP
	GIE = gie_bk;            //恢复全局中断

	return value_tmp;
}

/*******************************************************
函数名：uint GetOffsetVDD(void)
描  述：获取参考电压为VDD时offset值
输入值：无
输出值：无
返回值：offset值
*******************************************************/
uint GetOffsetVDD(void)
{
	uint value_tmp = 0;
	unsigned char gie_bk = GIE;		//备份GIE

    CLRWDT();

	while(GIE) GIE = 0;
	DATARDEN = 1;

	FRAH = 0x8030 >> 8;
	FRAL = 0x8030;
	DATARDTRG = 1;
	while(DATARDTRG) ;	     //等待读完成
	__Asm TBR;		         //查表读指令
	value_tmp = (ROMDH<<8) | ROMDL;

    ROMCL = 0x00;            //退出IAP
	GIE = gie_bk;            //恢复全局中断

    return value_tmp;
}

/****************初始化UART*******************/
void Uart_Init(void){
    PCT1 = 0;       //TX输出
    PAT5 = 1;       //RX输入
   // PBT5 = 0;       //TX输出
   // PBT6 = 1;       //RX输入
    TX1LEN = 0;     //8位数据发送格式 UART1SEL
    BRGH1 = 0;      //波特率低速模式：波特率=Fosc/(64*(BRR<7:0>+1))
    BR1R = 25;      //波特率=16MHz/(64*26)≈9600bps
    TX1EN = 1;       //打开发送
	UART1SEL=1;
}

void ADC_dis_init(){
  
    ANSH1 = 0;          //选择AIN9为模拟口
    ADCCL = 0xF8;      //ADCCL<7:4>选择通道
	//ADCCL &= 0x9F;      //选择通道9
	//ADCCM = 0x6B;       //参考源内部固定选择2.048V,负参考固定选择VSS，转换位数固定选择12位，AD调整offset固定选择档位1
    ADCCH = 0xC3 ;       //低位对齐;时钟周期FOSC/16
	ADEN = 0;           //使能ADC模块
    VREFEN = 0;         //参考电压模块使能
//	while(j--);         //等待300us以上
	VREF_CHOPEN = 0 ;    //内部参考必须使能电压斩波器
//    while(i--);         //等待1ms以上再启动转换

	ADC_LP_EN = 0;      //ADC低功耗必须固定使能
	PBT4 = 0;
	PBT2 = 0;
    SMPS = 1;           //硬件控制采样，ADTRG=1时启动AD采样转换
}


/**********************************************
函数名：ADC_init()
描  述：初始化ADC
输入值：无
输出值：无
返回值：无
**********************************************/
void ADC_init(void) 
{
    uint j = 3000;        //延时变量
	uint i = 10000;       //延时变量
	uchar cnt = 3;
     
/****************初始化ADC********************/
#ifdef VDDVREF
	while(cnt != 0)
	{
        offset_value = GetOffsetVDD();  //获取offset值
		if((offset_value>>8) == ((~offset_value) & 0x00FF)) //是否满足高低8位取反，是则取低8位作为offset
		{
			offset_value =  offset_value & 0x00FF;

			break;
		}
		else
		{
		    cnt--;

			if(cnt == 0)
			    offset_value = 0;  //读IAP超过3次后仍不满足高低8位取反则offset固定为0
		}
	}
    ANSL7 = 0;          //选择AIN7为模拟口
    ADCCL |= 0xF0;      //ADCCL<7:4>选择通道
    ADCCL &= 0x7F;      //选择通道7
	ADCCM = 0x4B;       //参考源VDD,负参考固定选择VSS，转换位数固定选择12位，AD调整offset固定选择档位1
    ADCCH = 0xC8;       //低位对齐;时钟周期FOSC/16
	ADEN = 1;           //使能ADC模块
#else
	while(cnt != 0)
	{
        offset_value = GetOffset2048();  //获取offset值
		if((offset_value>>8) == ((~offset_value) & 0x00FF)) //是否满足高低八位取反，是则取低8位作为offset
		{
			offset_value =  offset_value & 0x00FF;

			break;
		}
		else
		{
		    cnt--;

			if(cnt == 0)
			    offset_value = 0;    //读IAP超过3次后仍不满足高低8位取反则offset固定为0
		}
	}
    ANSH1 = 0;          //选择AIN9为模拟口
    ADCCL |= 0xF0;      //ADCCL<7:4>选择通道
    ADCCL &= 0x9F;      //选择通道9

	ADCCM = 0x6B;       //参考源内部固定选择2.048V,负参考固定选择VSS，转换位数固定选择12位，AD调整offset固定选择档位1
    ADCCH = 0xC8;       //低位对齐;时钟周期FOSC/16
	ADEN = 1;           //使能ADC模块
    VREFEN = 1;         //参考电压模块使能
	while(j--);         //等待300us以上
	VREF_CHOPEN = 1;    //内部参考必须使能电压斩波器
    while(i--);         //等待1ms以上再启动转换
#endif
	ADC_LP_EN = 1;      //ADC低功耗必须固定使能
	PBT4 = 1;
	PBT2 = 1;
    SMPS = 1;           //硬件控制采样，ADTRG=1时启动AD采样转换
}

void _f(int a[],char len)
{
    //int a[10];
	int n;  //存放数组a中元素的个数
    int i;  //比较的轮数
    int j;  //每轮比较的次数
    int buf;  //交换数据时用于存放中间数据
   // n = sizeof(a) / sizeof(a[0]);  /*a[0]是int型, 占4字节, 所以总的字节数除以4等于元素的个数*/
   //int ii;
    //for(ii=0;ii<len;ii++){
	//	a[ii] = *(num+ii);
	//}
	n=len;
	for (i=0; i<n-1; ++i)  //比较n-1轮
    {
        for (j=0; j<n-1-i; ++j)  //每轮比较n-1-i次,
        {
            if (a[j] < a[j+1])
            {
                buf = a[j];
                a[j] = a[j+1];
                a[j+1] = buf;
            }
        }
    }
    //for(int x=0;x<10;x++)
        //printf("%d\x20", a[x]);
}

static void Get_ADC_Val_Vbat(unsigned int *Vbat_val){

		ADCCL |= 0xF0;      //ADCCL<7:4>选择通道
		ADCCL &= 0x4F;      //选择通道

		adc_value = ADC_convert();
		if(adc_value > offset_value)   //AD转换值大于offset值则减去offset，否则ADC结果归0
		    adc_value -= offset_value;
		else
		    adc_value = 0;
		*Vbat_val=adc_value;
}

static void Get_ADC_Val_Temp(unsigned int *Temp_val){

		ADCCL |= 0xF0;      //ADCCL<7:4>选择通道
		ADCCL &= 0x9F;		//选择通道9
		adc_value = ADC_convert();
		if(adc_value > offset_value)   //AD转换值大于offset值则减去offset，否则ADC结果归0
		    adc_value -= offset_value;
		else
		    adc_value = 0;
		*Temp_val=adc_value;
}


static unsigned int Vbat_adc_val[10],Temp_adc_val[20],Temp_vcc_val[20];
unsigned char change_flag=0;
void User_Get_measure_Val(){
		static char i=0;
		static char ii=0;
		i=i%20; 
		ii=ii%10; 
			    
		Get_ADC_Val_Temp(&Temp_adc_val[i]);
		Get_ADC_Val_Vbat(&Temp_vcc_val[i]);

		if(change_flag==0){
		  i++;
		}
		
		if(i==19){
			_f(Temp_adc_val,20);	//
			_f(Temp_vcc_val,20);
			temp_vcc_val=4*2.048*Temp_vcc_val[10]/4096;
			if(PB5){
				temp_vcc_val=4.6;
					//temp_vcc_val=temp_vcc_val*1.06;
				////Temp_adc_val[10]=Temp_adc_val[10]*0.9;
			}

			temperature=Get_Tempture(Temp_adc_val[10]);

			//GIE=0;
			//UART_send(str,6,Temp_adc_val[10]);
			//UART_send(str,7,temperature);
			//UART_send(str,8,vcc_val*1000);
			//UART_send(str,9,temp_vcc_val*1000);
			//GIE=1;
		}
		//开机测量
		if (global_count<10000){
			PA7=1;
			Get_ADC_Val_Vbat(&Vbat_adc_val[ii]);
			ii++;
				if(ii==9){
					_f(Vbat_adc_val,10);	//
					vcc_val=4*2.048*Vbat_adc_val[5]/4096;
					temp_vcc_val=vcc_val;
					if(vcc_val>4.15) vcc_val=4.15;
					if(vcc_val<3.5) vcc_val=3.5;
					Vbat_val=(vcc_val-3.5)*100/(4.15-3.5);

					//GIE=0;
					//UART_send(str,8,Vbat_val);
					//UART_send(str,9,vcc_val*1000);
					//GIE=1;
				}
		}
		#ifdef UART_TEST
			GIE=0;
			UART_send(str,('A'-'0'),Vbat_val);
			UART_send(str,('B'-'0'),vcc_val*1000);
			
			GIE=1;
			float a;

			a=Get_Tempture(Temp_adc_val[10]);
			GIE=0;
			UART_send(str,1,Temp_adc_val[5]);
			UART_send(str,1,RT*10);
			UART_send(str,0,a*100);
			GIE=1;
		#endif

		//温度
		//if(Temp_adc_val[10]<4000){
		//	temperature=Get_Tempture(Temp_adc_val[10]);
		//}	//temperature=adc_value/1000*10+(adc_value/100)%10;
		//else{
		//	temperature=0xff;
		//}
}

void User_Get_measure_Val_10ms(){
		//正常
		if(global_count>10000 ){
					static unsigned int count;
					count++;
					change_flag=0;
					if(count>=100){
						count=0;
					}
					if(count==0){
						PA7=0;
					}
					if(count<10){
						change_flag=1;
						Get_ADC_Val_Vbat(&Vbat_adc_val[count]);
						Get_ADC_Val_Temp(&Temp_adc_val[count]);
					}
					else if(count==10){
						PA7=1;
						_f(Vbat_adc_val,10);
						//_f(Temp_adc_val,10);
						vcc_val=4*2.048*Vbat_adc_val[5]/4096;
						//temp_vcc_val=vcc_val;
						//temperature=Get_Tempture(Temp_adc_val[5]);						
						if(vcc_val>4.15) vcc_val=4.15;
						if(vcc_val<3.5) vcc_val=3.5;
						if(State_flag!=2){
							Vbat_val=(vcc_val-3.5)*100/(4.15-3.5);
				
							//GIE=0;
							//UART_send(str,1,Vbat_val);
							//UART_send(str,2,vcc_val*1000);
							//GIE=1;
						}
					}
		}
}
		
		//if(USB_Check() && global_count>10000 ){
					//static unsigned int count;
					//count++;
					//if(count>54){   //108s ++
						//count=0;
						//Vbat_val++;
					//}
				//if(Vbat_val>99) Vbat_val=99;
				//if(Vbat_val<0) Vbat_val=0;		
		//}
		//else{
			//if(State_flag!=2){
				//vcc_val=4*2.048*Vbat_adc_val[10]/4096;
				//if(vcc_val>4.2) vcc_val=4.2;
				//if(vcc_val<3.5) vcc_val=3.5;
				//Vbat_val=(vcc_val-3.5)*100/(4.2-3.5);
				////if(Vbat_val>99) Vbat_val=99;
				////if(Vbat_val<0) Vbat_val=0;
			//}
			//else{
			//}
		//}