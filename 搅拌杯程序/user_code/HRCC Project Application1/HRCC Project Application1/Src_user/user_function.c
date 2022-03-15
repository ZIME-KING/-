#include "../main.h"
#include "../inc_user/user_function.h"
#include <math.h>
/*********************************************************
*Copyright (C), 2020, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  adc_offset.c
*��  ��:  AE Team
*��  ��:  v1.0��������iDesigner(v4.2.3.166) + ������HRCC(v1.2.0.106)
*��  ��:  2020/12/25
*��  ��:  ADCͨ����ʾ
          PA7��ģ������˿�
          PB5��TX
          PB6��RX 
          ����ת�����ADֵͨ�����ڷ��͵���λ����������9600bps���궨��VDDVREFѡ��VDD��Ϊ�ο���ѹ���ˣ�
          ����ѡ���ڲ�2.048V��Ϊ�ο���ѹ���ˡ�
		  ת��ֵ��ȥoffset����ADC���������offsetΪ802FH���ڲ�2.048V���ο�����8030H��VDD���ο�����8λ���ݣ�
		  IAP��16λ���ݺ������ж��Ƿ�����ߵ�8λȡ����
		  ע�⣺����offset�Ĵ��ڣ�Ϊ��ֹ�����ת��ֵС��offsetʱ��ADC���ֱ�ӹ�0������ADC���ֻ�ܲ⵽(0xFFF-offset)��
*��  ע:  ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/

//#define VDDVREF        //�궨��ѡ��VDD��Ϊ�ο���ѹ��ע�ͱ�����ѡ���ڲ�2.048V��Ϊ�ο���ѹ����
typedef unsigned char uchar;
typedef unsigned int uint;

uint adc_value;
uint offset_value = 0;  //����ADCУ׼ֵ
uchar str[] = "ͨ�� ��ת��ֵΪ:    \r\n\0";


#define B 3950.0//�¶�ϵ��
#define TN 298.15//��¶�(�����¶ȼӳ���:273.15+25)
#define RN 100// ���ֵ(�����¶�ʱ�ĵ���ֵ10k)
#define RES 200// ��ѹ����200K
#define BaseVol  2.048 //ADC��׼��ѹ

float vcc_val;
float RV,RT,Tmp;
float Get_Tempture(unsigned int adc)
{        //float RV,RT,Tmp;
        RV=BaseVol*(float)adc/4096.0;		//ADCΪ12λADC,���NTC��ѹ:RV=ADCValu/4096*BaseVoltag
       // RT=RV*100/(BaseVol-RV);				//�����ǰ�¶���ֵ (BaseVoltage-RV)/R16=RV/RT;
		RT=RES/((vcc_val/RV)-1);
	    Tmp=1/(1/TN+(log(RT/RN)/B))-273.15;//%RT = RN exp*B(1/T-1/TN)%
        return Tmp;
}
//��������������������������������
//��Ȩ����������ΪCSDN������LVGRAPE����ԭ�����£���ѭCC 4.0 BY-SA��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
//ԭ�����ӣ�https://blog.csdn.net/u013866683/article/details/79391849



/**********************************************
��������UART_send(uchar *str,uchar ch,uint value)
��  ����UART���ͺ���
����ֵ���ַ���ָ�룬ͨ������ADCת��ֵ
���ֵ����
����ֵ����
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
��������ADC_convert(uchar ch)
��  ����ADCת������
����ֵ��ת��ͨ��ch
���ֵ����
����ֵ��ת����12λ���
**********************************************/
uint ADC_convert(void)
{
    ADTRG = 1;      //����ADת��
    while(ADTRG);
    ADIF = 0;

    return (uint)ADCRH<<8 | ADCRL;
}

/*******************************************************
��������uint GetOffset2048(void)
��  ������ȡ�ο���ѹΪ�ڲ�2.048Vʱoffsetֵ
����ֵ����
���ֵ����
����ֵ��offsetֵ
*******************************************************/
uint GetOffset2048(void)
{
	uint value_tmp = 0;
	unsigned char gie_bk = GIE;		//����GIE

    CLRWDT();

	while(GIE) GIE = 0;
	DATARDEN = 1;

	FRAH = 0x802F >> 8;
	FRAL = 0x802F;
	DATARDTRG = 1;
	while(DATARDTRG) ;	     //�ȴ������
	__Asm TBR;		         //����ָ��
	value_tmp = (ROMDH<<8) | ROMDL;

    ROMCL = 0x00;            //�˳�IAP
	GIE = gie_bk;            //�ָ�ȫ���ж�

	return value_tmp;
}

/*******************************************************
��������uint GetOffsetVDD(void)
��  ������ȡ�ο���ѹΪVDDʱoffsetֵ
����ֵ����
���ֵ����
����ֵ��offsetֵ
*******************************************************/
uint GetOffsetVDD(void)
{
	uint value_tmp = 0;
	unsigned char gie_bk = GIE;		//����GIE

    CLRWDT();

	while(GIE) GIE = 0;
	DATARDEN = 1;

	FRAH = 0x8030 >> 8;
	FRAL = 0x8030;
	DATARDTRG = 1;
	while(DATARDTRG) ;	     //�ȴ������
	__Asm TBR;		         //����ָ��
	value_tmp = (ROMDH<<8) | ROMDL;

    ROMCL = 0x00;            //�˳�IAP
	GIE = gie_bk;            //�ָ�ȫ���ж�

    return value_tmp;
}

/****************��ʼ��UART*******************/
void Uart_Init(void){
    //PCT1 = 0;       //TX���
    //PAT5 = 1;       //RX����
   // PBT5 = 0;       //TX���
   // PBT6 = 1;       //RX����
    TX1LEN = 0;     //8λ���ݷ��͸�ʽ UART1SEL
    BRGH1 = 0;      //�����ʵ���ģʽ��������=Fosc/(64*(BRR<7:0>+1))
    BR1R = 25;      //������=16MHz/(64*26)��9600bps
    
	UART1SEL=1;
}

void ADC_dis_init(){
  
    ANSH1 = 0;          //ѡ��AIN9Ϊģ���
    ADCCL = 0xF8;      //ADCCL<7:4>ѡ��ͨ��
 //   ADCCL &= 0x9F;      //ѡ��ͨ��9

	//ADCCM = 0x6B;       //�ο�Դ�ڲ��̶�ѡ��2.048V,���ο��̶�ѡ��VSS��ת��λ���̶�ѡ��12λ��AD����offset�̶�ѡ��λ1
    ADCCH = 0xC3 ;       //��λ����;ʱ������FOSC/16
	ADEN = 0;           //ʹ��ADCģ��
    VREFEN = 0;         //�ο���ѹģ��ʹ��
//	while(j--);         //�ȴ�300us����
	VREF_CHOPEN = 0 ;    //�ڲ��ο�����ʹ�ܵ�ѹն����
//    while(i--);         //�ȴ�1ms����������ת��

	ADC_LP_EN = 0;      //ADC�͹��ı���̶�ʹ��
	PBT4 = 0;
	PBT2 = 0;
    SMPS = 1;           //Ӳ�����Ʋ�����ADTRG=1ʱ����AD����ת��
}


/**********************************************
��������ADC_init()
��  ������ʼ��ADC
����ֵ����
���ֵ����
����ֵ����
**********************************************/
void ADC_init(void) 
{
    uint j = 3000;        //��ʱ����
	uint i = 10000;       //��ʱ����
	uchar cnt = 3;
     
/****************��ʼ��ADC********************/
#ifdef VDDVREF
	while(cnt != 0)
	{
        offset_value = GetOffsetVDD();  //��ȡoffsetֵ
		if((offset_value>>8) == ((~offset_value) & 0x00FF)) //�Ƿ�����ߵ�8λȡ��������ȡ��8λ��Ϊoffset
		{
			offset_value =  offset_value & 0x00FF;

			break;
		}
		else
		{
		    cnt--;

			if(cnt == 0)
			    offset_value = 0;  //��IAP����3�κ��Բ�����ߵ�8λȡ����offset�̶�Ϊ0
		}
	}
    ANSL7 = 0;          //ѡ��AIN7Ϊģ���
    ADCCL |= 0xF0;      //ADCCL<7:4>ѡ��ͨ��
    ADCCL &= 0x7F;      //ѡ��ͨ��7
	ADCCM = 0x4B;       //�ο�ԴVDD,���ο��̶�ѡ��VSS��ת��λ���̶�ѡ��12λ��AD����offset�̶�ѡ��λ1
    ADCCH = 0xC8;       //��λ����;ʱ������FOSC/16
	ADEN = 1;           //ʹ��ADCģ��
#else
	while(cnt != 0)
	{
        offset_value = GetOffset2048();  //��ȡoffsetֵ
		if((offset_value>>8) == ((~offset_value) & 0x00FF)) //�Ƿ�����ߵͰ�λȡ��������ȡ��8λ��Ϊoffset
		{
			offset_value =  offset_value & 0x00FF;

			break;
		}
		else
		{
		    cnt--;

			if(cnt == 0)
			    offset_value = 0;    //��IAP����3�κ��Բ�����ߵ�8λȡ����offset�̶�Ϊ0
		}
	}
    ANSH1 = 0;          //ѡ��AIN9Ϊģ���
    ADCCL |= 0xF0;      //ADCCL<7:4>ѡ��ͨ��
    ADCCL &= 0x9F;      //ѡ��ͨ��9

	ADCCM = 0x6B;       //�ο�Դ�ڲ��̶�ѡ��2.048V,���ο��̶�ѡ��VSS��ת��λ���̶�ѡ��12λ��AD����offset�̶�ѡ��λ1
    ADCCH = 0xC8;       //��λ����;ʱ������FOSC/16
	ADEN = 1;           //ʹ��ADCģ��
    VREFEN = 1;         //�ο���ѹģ��ʹ��
	while(j--);         //�ȴ�300us����
	VREF_CHOPEN = 1;    //�ڲ��ο�����ʹ�ܵ�ѹն����
    while(i--);         //�ȴ�1ms����������ת��
#endif
	ADC_LP_EN = 1;      //ADC�͹��ı���̶�ʹ��
	PBT4 = 1;
	PBT2 = 1;
    SMPS = 1;           //Ӳ�����Ʋ�����ADTRG=1ʱ����AD����ת��
}

void _f(int a[],char len)
{
    //int a[10];
	int n;  //�������a��Ԫ�صĸ���
    int i;  //�Ƚϵ�����
    int j;  //ÿ�ֱȽϵĴ���
    int buf;  //��������ʱ���ڴ���м�����
   // n = sizeof(a) / sizeof(a[0]);  /*a[0]��int��, ռ4�ֽ�, �����ܵ��ֽ�������4����Ԫ�صĸ���*/
   //int ii;
    //for(ii=0;ii<len;ii++){
	//	a[ii] = *(num+ii);
	//}
	n=len;
	for (i=0; i<n-1; ++i)  //�Ƚ�n-1��
    {
        for (j=0; j<n-1-i; ++j)  //ÿ�ֱȽ�n-1-i��,
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

static void Get_ADC_Val(unsigned int *Vbat_val,unsigned int *Temp_val){
		unsigned int i;
		ADCCL |= 0xF0;      //ADCCL<7:4>ѡ��ͨ��
		ADCCL &= 0x4F;      //ѡ��ͨ��4

		adc_value = ADC_convert();
		if(adc_value > offset_value)   //ADת��ֵ����offsetֵ���ȥoffset������ADC�����0
		    adc_value -= offset_value;
		else
		    adc_value = 0;
		*Vbat_val=adc_value;


		ADCCL |= 0xF0;      //ADCCL<7:4>ѡ��ͨ��
		ADCCL &= 0x9F;		//ѡ��ͨ��9
		adc_value = ADC_convert();
		if(adc_value > offset_value)   //ADת��ֵ����offsetֵ���ȥoffset������ADC�����0
		    adc_value -= offset_value;
		else
		    adc_value = 0;
		*Temp_val=adc_value;
}
void User_Get_measure_Val(){
		static unsigned int Vbat_adc_val[20],Temp_adc_val[20];
		static char i=0;
		i=i%20;
		Get_ADC_Val(&Vbat_adc_val[i],&Temp_adc_val[i]);
		i++;
		if(i==19){
			_f(Vbat_adc_val,20);  //
			_f(Temp_adc_val,20);
		//����ֵ
		vcc_val=4*2.048*Vbat_adc_val[10]/4096;
		if(vcc_val>4.2) vcc_val=4.2;
		Vbat_val=(vcc_val-3.6)*100/(4.2-3.6);

		if(Vbat_val>99) Vbat_val=99;
		if(Vbat_val<0) Vbat_val=0;

		//�¶�
		if(Temp_adc_val[10]<4000){
			temperature=Get_Tempture(Temp_adc_val[10]);
		}	//temperature=adc_value/1000*10+(adc_value/100)%10;
		else{
			temperature=0xff;
		}
	}
}