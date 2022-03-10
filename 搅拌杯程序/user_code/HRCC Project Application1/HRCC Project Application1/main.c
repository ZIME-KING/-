/*sample.c*/
#include <hic.h>
#include "main.h"

unsigned long global_count;//全局时间计数1ms ++
unsigned char State_flag=1;//运行状态
unsigned int  sleep_count;//休眠时间计数
unsigned char buzzer_flag;//蜂鸣器启动标记
 char temperature;//温度值 0~99
unsigned char Vbat_val;   //电量%  0~99

unsigned char display_buf[18]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//显示缓存 display_buf[1-1]=1； 1号LED亮
unsigned long Get_Sys_time(){
	return global_count;
}
/******************************************************
函数名：void RAMclear(void)
描  述：RAM区数据清零，RAM区地址0x0000~0x03FF
输入值：无
输出值：无
返回值：无
*******************************************************/
void RAMclear(void){
    for (IAAH=0; IAAH<=0x03; IAAH++)
    {
        for (IAAL=0; IAAL<0xFF; IAAL++)
            IAD = 0x00;
        IAD = 0x00;
    }
}

/**********************************************
函数名：void sleep(void)
描  述：进入IDLE模式
输入值：无
输出值：无
返回值：无
**********************************************/
void sleep(void)
{
    PWRC &= 0x3F;
    PWRC |= 2<<6;        //选择IDLE模式
    __Asm IDLE;     //进入IDLE模式
}

/******************************************************
函数名：void GPIOInit(void)
描  述：首先初始化所有未用到的IO口为输出低电平
输入值：无
输出值：无
返回值：无
*******************************************************/
void GPIOInit(void)
{
    ANSH = 0xFF;        //选择对应端口为数字IO功能
    ANSL = 0xFF;        //选择对应端口为数字IO功能
    PAT  = 0x00;        //所有IO设为输出低电平
    PBT  = 0x00;		
    PCT  = 0x00;
    PA   = 0x00;
    PB   = 0x00;
    PC   = 0x00;
	
	PAT3=0;		//PA3 复用RST脚，设置数字输出
	PAT2=0x01;	//PA2 数字输入 触摸按键
	PBT5=0x01;  //PB5 数字输入
	PB5=1;

	INTC0 |=0x80;       //usb检测双边触发
	PIE7 = 1;           //打开管脚中断
    PIF7 = 0;           //清除外部中断标志

	PAPU=0x00;
	
	//PA3DS：PA3 端口电流选择位
	 PA1DS=1;	
	 PA3DS=1;
	 PA4DS=1;
	 PA5DS=1;
	 PB0DS=1;
	 PC1DS=1;
	 PC0DS=1;

	// 设置AIN11 PB1  MOTO_CUR
	// 设置AIN4  PB2  VBAT
	// 设置AIN9  PB4  NTC
	ANSH3=0;  //PB1/AIN11
	ANSL4=0;  //PB2/AIN4
	ANSH1=0;  //PB4/AIN9
}

void Timer_T8_Init(){
	//16MHZ 时钟 1ms中断
    T8NC = 0x0D;         //定时器模式，预分频1:(Fosc/2)/64
	//16MHZ 时钟 0.51ms中断
    //T8NC = 0x0C;         //定时器模式，预分频1:(Fosc/2)/32
    //T8NC = 0x0F;         //定时器模式，预分频1:(Fosc/2)/256
	//T8NC = 0x08;         //定时器模式，预分频1:(Foc/2)/2
    T8N = 131;           //赋计数器初值
    T8NIE = 1;           //打开定时器溢出中断
    T8NIF = 0;           //清溢出标志位
    GIE = 1;             //开全局中断
    T8NEN = 1;           //使能T8N
}

void Delay_ms(unsigned int delay){
	static long temp_time;
	temp_time=Get_Sys_time();
	while(Get_Sys_time()-temp_time<delay);
}

void TEST_Delay_ms(unsigned int delay){
	   int i;
	   for(i = 0;i<500*delay;i++);        //延时
}

/******************************************************
函数名：void Timer_T21_Init(void)
描  述：定时器T21初始化
*******************************************************/
void Timer_T21_Init(){
	unsigned int ch0_duty=500;
	unsigned int ch1_duty=500;
	T21CL = 0xC0;        //多精度pwm模式
    T21CM = 0x3F;        //T21_CH0输出低有效、T21_CH1输出低有效，预分频1:16
    T21OC = 0x45;        //T21_CH0，T21_CH1,开启在PA0，PA7上，PWM时钟源选择INTHRC
   
    T21PH = 999 >> 8;        //pwm周期
    T21PL = 999 & 0xFF;

	ch0_duty=999;
	ch1_duty=999;

    T21R0H = ch0_duty >>8 ;       //pwm0占空比
    T21R0L = ch0_duty & 0xFF;

    T21R1H = ch1_duty >>8;		//pwm1占空比
    T21R1L = ch1_duty & 0xFF;
    
	T21TR = 1;           //启动pwm输出
    T21PIE = 1;          //打开T21周期2中断    
    T21PIF = 0;          //清标志位
    GIE = 1;             //开全局中断    
    T21EN = 1;           //使能T21
}
//
//输入值为0~999
//
void Set_PWM_CH0_Duty(int duty){
	    T21R0H = duty >>8 ;     //pwm0占空比
		T21R0L = duty & 0xFF;
}
void Set_PWM_CH1_Duty(int duty){
		T21R1H = duty >>8;		//pwm1占空比
		T21R1L = duty & 0xFF;
}
//#define BUZER_N  //无源
#define BUZER_A	 //有源
#ifdef BUZER_N
unsigned char Buzzer_Init(void){
	BEEPC=0xD8;
	return 0xff;
}
void Buzzer_Stop(){
	BEEPEN=0;
}
void Buzzer_Start(){
	BEEPEN=1;
}
#endif

#ifdef BUZER_A
unsigned char  Buzzer_Init(void){
	return 0x88;
}
void Buzzer_Stop(){
	PB7=0;
}
void Buzzer_Start(){
	PB7=1;
}
#endif

void State_Trans(unsigned char new_state){
	State_flag=new_state;
}
unsigned char Get_State(){
	return State_flag;
}
void Buzzer_Task(){
	if(Get_State()!=3){
		if(buzzer_flag){
			Buzzer_Start();
			buzzer_flag=0;
		}
	else{
		Buzzer_Stop();
	}
	}
}
unsigned char USB_Check(){
	return PB5;
}
void Sleep_Tsak(){
static unsigned char last_state;
	if(last_state!=Get_State()){
		last_state=Get_State();
		sleep_count=0;
	}
	  sleep_count++;
	if(Get_State()==1){
		if(sleep_count>180){
			State_Trans(0);
		}
	}
	else if(Get_State()==2){
		if(sleep_count>120){
			State_Trans(0);
		}
	}
	else if(Get_State()==3){
		if(sleep_count>3){
			State_Trans(0);
			//sleep();
		}
	}
}

void LED_Task(){
//显示温度
	//char temp;
	//RV;vcc_val
	//temp=vcc_val*10;
	//D1_NUM(temp /10);
	//D2_NUM(temp %10);
	display_buf[13-1]=1;

	if(temperature==0xff){
	  D1_NUM(0xff);
	  D2_NUM(0xff);	
	}
	else{
	  D1_NUM(temperature/10);
	  D2_NUM(temperature%10);	
	}

	//D1_NUM(Vbat_val/10);
	//D2_NUM(Vbat_val%10);


	//vcc_val
//电量指示
	if(USB_Check()){
		if(0<=Vbat_val && Vbat_val<30){
			display_buf[14-1]=!display_buf[14-1]; //左一闪
			display_buf[12-1]=0; 
			display_buf[15-1]=0;
		}
		else if(30<=Vbat_val && Vbat_val<60){
			display_buf[14-1]=1;
			display_buf[12-1]=!display_buf[12-1]; //左一亮 左二闪
			display_buf[15-1]=0;
		}
		else if(60<=Vbat_val && Vbat_val<90){
			display_buf[14-1]=1;
			display_buf[12-1]=1; 
			display_buf[15-1]=!display_buf[15-1]; //左一亮 左二亮 左三闪
		}
		else if(90<=Vbat_val){
			display_buf[14-1]=1;
			display_buf[12-1]=1; 
			display_buf[15-1]=1; //左一亮 左二亮 左三亮		
		}
	}
	else{
		if(0<=Vbat_val && Vbat_val<33){
			display_buf[14-1]=1;
			display_buf[12-1]=0; 
			display_buf[15-1]=0; //左一亮 左二亮 左三亮				
		}
		else if(33<=Vbat_val && Vbat_val<66){
			display_buf[14-1]=1;
			display_buf[12-1]=1; 
			display_buf[15-1]=0; //左一亮 左二亮 左三亮		
		}
		else if(66<=Vbat_val && Vbat_val<99){
			display_buf[14-1]=1;
			display_buf[12-1]=1; 
			display_buf[15-1]=1; //左一亮 左二亮 左三亮		
		}
	}	
	Updata_SCAN_LED_BUF_R();
}
//进入休眠状态
void state_0(){
	//PA1=0;
	char i;
	i=18;
	while(i--)
	display_buf[i]=0;
	Updata_SCAN_LED_BUF_R();
	LED_Clear();

	//Set_PWM_CH0_Duty(999);
	//Set_PWM_CH1_Duty(999);

	Timer_T21_Init();


	//RAMclear();
	 State_Trans(3);
	//配置PA2中断模式唤醒

	ANSL = 0xFF;        //选择对应端口为数字IO功能
	ANSH = 0xFF;
    PAT = 0x00;         //所有IO设为输出低电平
    PBT = 0x00;
    PCT = 0x00;
    PA = 0x00;
    PB = 0x00;
    PC = 0x00;

	PAT2=0x01;	//PA2 数字输入
	KIE=1;
	KMSK1=1;
	PAPU=PAPU|0X04;

	PBT5=0x01;  //PB5 数字输入
	PB5=1;

	INTC0 |=0x80;       //usb检测双边触发
	PIE7 = 1;           //打开管脚中断
    PIF7 = 0;           //清除外部中断标志


	ADC_dis_init();

	//PWRC &= 0x3F;
    //PWRC |= 2<<6;        //选择IDLE模式
    //__Asm IDLE;     //进入IDLE模式

	sleep();
}
//全关检测按键长按开机
void state_3(){

	unsigned char i=18;
	while(i--)
	display_buf[i]=0;
	Updata_SCAN_LED_BUF_R();
	LED_Clear();

}

//电机关 开灯
void state_1(){
	Set_PWM_CH0_Duty(999);
	Set_PWM_CH1_Duty(999);
}

//电机开
void state_2(){

	Set_PWM_CH1_Duty(1);
	Set_PWM_CH0_Duty(100);
}
void State_Ruun(){
			switch (State_flag){
				case 3:
					state_3();
				break;
				case 1:
					state_1();
				break;
				case 2:
					state_2();
				break;
				case 0:
					state_0();
				break;
			}
}


void user_delay(){
unsigned int i=4000;
while(i--);
}
void main(void) 
{
	//RAMclear();
	WDTC = 0x16;         //分频比1:128，使能WDT预分频器，看门狗溢出时间t=256*128/32000=1.024s

	SetTime();			//任务间隔时间初始化
	GPIOInit();
	Timer_T8_Init();
	Timer_T21_Init();
	//sleep();
	ADC_init() ;
	
	//ADC_dis_init();
	//sleep();
	Buzzer_Init();
	LED_Clear();

	PB3=1;
	//int ii=0;
	//while(ii--){
		//Buzzer_Start();
		//Delay_ms(100);
		//Buzzer_Stop();
		//Delay_ms(100);
	//}

	int iii=100;
	while(iii--){
		user_delay();
		//Delay_ms(10);
		User_Get_measure_Val();
	}
	LED_Task();




	while (1)
    {
	  if(CompareTime(&Task_50)){
			GetTime(&Task_50);
			if(touch_key_busy){
			touch_key_busy=0;
			sleep_count=0;
				if(touch_key_staus==SHORT ){
						if(Get_State()==2) {
							State_Trans(0);
							//state_0();
							//sleep();
						}
				}
				if(touch_key_staus==DOUBLE){
						if(Get_State()==1 && USB_Check()==0){
								State_Trans(2);
						}
				}
				if(touch_key_staus==LONG_NO_RELEASE){
						if(Get_State()==3) 
						{
							__Asm RST;     //
						}//State_Trans(1);
				}
			}
	  }
	  if(CompareTime(&Task_100)){
		  GetTime(&Task_100);
		  User_Get_measure_Val();
		  State_Ruun();
		  Buzzer_Task();
		  if(USB_Check()==1){
			 State_Trans(1);
			 sleep_count=0;
		  }
		  	//Get_ADC_Val();
	  }
	  if(CompareTime(&Task_1000)){
		  GetTime(&Task_1000);
			Sleep_Tsak();
			//Get_ADC_Val();
			if(Get_State()!=3){
				LED_Task();
			}

	  }
        CLRWDT();
    }
}

/*******************************************************
函数名：void isr(void) interrupt
描  述：中断服务程序
输入值：无
输出值：无
返回值：无
*******************************************************/
//unsigned int timer_cnt;
 unsigned char cnt_0;
void isr(void) interrupt
{
    if (T8NIE==1 && T8NIF==1)        //定时器溢出中断
    {
        T8NIF = 0;        //清标志位
        T8N += 131;         //进中断先赋计数器初值
		SCAN_NEW();
		global_count++;
		scan_touch_key();
    }
	  if (T21PIE==1 && T21PIF==1)        //定时器pwm周期中断
    {
        T21PIF = 0;                //清标志位
    }
	    if(KIF==1 && KIE==1)
    {
		PA2=1;
		KIF = 0;       //清中断标志位
    }
	    if(PIE7==1 && PIF7==1) //usb插入
    {
		sleep_count=0;
		if(State_flag==2 )State_flag=1;    
		
        
		if(State_flag==3){
			__Asm RST;     //
		}

		
		PIF7 = 0;		 //清除外部中断
    }
}
