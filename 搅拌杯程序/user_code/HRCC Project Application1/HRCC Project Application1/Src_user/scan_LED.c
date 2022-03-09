#include "..\main.h"
#include "..\inc_user\scan_LED.h"

#define LED_IO_0(x)		PC1=x
#define LED_IO_0_OUT()	PCT1=0
#define LED_IO_0_Z()	PCT1=1

#define LED_IO_1(x) 	PA5=x
#define LED_IO_1_OUT()	PAT5=0
#define LED_IO_1_Z()	PAT5=1

#define LED_IO_2(x) 	PA4=x
#define LED_IO_2_OUT()	PAT4=0
#define LED_IO_2_Z()	PAT4=1

#define LED_IO_3(x) 	PB6=x
#define LED_IO_3_OUT()	PBT6=0
#define LED_IO_3_Z()	PBT6=1

#define LED_IO_4(x)		PA1=x
#define LED_IO_4_OUT()	PAT1=0
#define LED_IO_4_Z()	PAT1=1

#define LED_IO_5(x)		PC0=x
#define LED_IO_5_OUT()	PCT0=0
#define LED_IO_5_Z()	PCT0=1

#define LED_IO_6(x)		PA6=x
#define LED_IO_6_OUT()	PAT6=0
#define LED_IO_6_Z()	PAT6=1

#define LED_IO_7(x)		PB0=x
#define LED_IO_7_OUT()	PBT0=0
#define LED_IO_7_Z()	PBT0=1

#define LED_IO_8(x)		PA3=x
#define LED_IO_8_OUT()	PAT3=0
#define LED_IO_8_Z()	PAT3=1

const unsigned char D1_NUM1[]={2,7};
const unsigned char D1_NUM2[]={11,2,16,9,17};
const unsigned char D1_NUM3[]={11,2,16,7,17};
const unsigned char D1_NUM4[]={4,2,16,7};
const unsigned char D1_NUM5[]={11,4,16,7,17};
const unsigned char D1_NUM6[]={11,4,16,9,7,17};
const unsigned char D1_NUM7[]={11,2,7};
const unsigned char D1_NUM8[]={11,4,2,16,9 ,7,17};
const unsigned char D1_NUM9[]={11,4,2 ,16,7,17};
const unsigned char D1_NUM0[]={11,4,2,9,7,17};
const unsigned char D1_NUM_F[]={11,4,16,9};

const unsigned char D2_NUM1[]={3,8};
const unsigned char D2_NUM2[]={1,3,6,10,18};
const unsigned char D2_NUM3[]={1,3,6,8,18};
const unsigned char D2_NUM4[]={5,6,3,8};
const unsigned char D2_NUM5[]={1,5,6,8,18};
const unsigned char D2_NUM6[]={1,5,6,10,18,8};
const unsigned char D2_NUM7[]={1,3,8};
const unsigned char D2_NUM8[]={1,5,3 ,6,10 ,8,18};
const unsigned char D2_NUM9[]={1,5,3 ,6,8,18};
const unsigned char D2_NUM0[]={1,3,5,8,10,18};
const unsigned char D2_NUM_F[]={1,5,6,10};

const unsigned int LED_BUF[]={0x1E,0x2E,0x4E,0x8E,0x10E,0x1D,0x2D,0x4D,0x8D,0x10D,0x1B,0x2B,0x4B,0x8B,0x10B,0x17,0x27,0x47/*0x87,0x107*/};

unsigned char SCAN_LED_BUF_R[5]={0x0f,0x0f,0x0f,0x0f,0x0f};

void Set_LED(unsigned char IO,unsigned char state){
	switch(IO){
		case 0:
			LED_IO_0(state);
		break;
		case 1:
			LED_IO_1(state);
		break;
		case 2:
			LED_IO_2(state);
		break;
		case 3:
			LED_IO_3(state);
		break;
		case 4:
			LED_IO_4(state);
		break;
		case 5:
			LED_IO_5(state);
		break;
		case 6:
			LED_IO_6(state);
		break;
		case 7:
			LED_IO_7(state);
		break;
		case 8:
			LED_IO_8(state);
		break;
	}
}
void LED_Clear(){
	int i=9;
	while(i--){
		Set_LED(i,0);	
	}
}
void Updata_SCAN_LED_BUF_R(){
  char x=1;

  SCAN_LED_BUF_R[0]=0x0f;
  SCAN_LED_BUF_R[1]=0x0f;
  SCAN_LED_BUF_R[2]=0x0f;
  SCAN_LED_BUF_R[3]=0x0f;
  SCAN_LED_BUF_R[4]=0x0f;

  if(display_buf[1-x]==1){
		 SCAN_LED_BUF_R[0]=SCAN_LED_BUF_R[0] & 0x0E;
  }
  if(display_buf[6-x]==1){
		 SCAN_LED_BUF_R[0]=SCAN_LED_BUF_R[0] & 0x0D;
  }
  if(display_buf[11-x]==1){
		 SCAN_LED_BUF_R[0]=SCAN_LED_BUF_R[0] & 0x0B;   
  }
  if(display_buf[16-x]==1){
 		 SCAN_LED_BUF_R[0]=SCAN_LED_BUF_R[0] & 0x07;   
  }
	if(display_buf[2-x]==1){
		SCAN_LED_BUF_R[1]=SCAN_LED_BUF_R[1] & 0x0E; 
  }
	if(display_buf[7-x]==1){
		SCAN_LED_BUF_R[1]=SCAN_LED_BUF_R[1] & 0x0D;    
  }
	if(display_buf[12-x]==1){
		SCAN_LED_BUF_R[1]=SCAN_LED_BUF_R[1] & 0x0B;    
  }
	if(display_buf[17-x]==1){
		SCAN_LED_BUF_R[1]=SCAN_LED_BUF_R[1] & 0x07;    
  }

  	if(display_buf[3-x]==1){
		SCAN_LED_BUF_R[2]=SCAN_LED_BUF_R[2] & 0x0E;    
  }
	if(display_buf[8-x]==1){
		SCAN_LED_BUF_R[2]=SCAN_LED_BUF_R[2] & 0x0D;   
  }
	if(display_buf[13-x]==1){
		SCAN_LED_BUF_R[2]=SCAN_LED_BUF_R[2] & 0x0B;   
  }
	if(display_buf[18-x]==1){
		SCAN_LED_BUF_R[2]=SCAN_LED_BUF_R[2] & 0x07;    
  }

    if(display_buf[4-x]==1){
		SCAN_LED_BUF_R[3]=SCAN_LED_BUF_R[3] & 0x0E;    
  }
	if(display_buf[9-x]==1){
		SCAN_LED_BUF_R[3]=SCAN_LED_BUF_R[3] & 0x0D;    
  }
	if(display_buf[14-x]==1){
		SCAN_LED_BUF_R[3]=SCAN_LED_BUF_R[3] & 0x0B;    
  }

    if(display_buf[5-x]==1){
		SCAN_LED_BUF_R[4]=SCAN_LED_BUF_R[4] & 0x0E;   
  }
	if(display_buf[10-x]==1){
		SCAN_LED_BUF_R[4]=SCAN_LED_BUF_R[4] & 0x0D;   
  }
	if(display_buf[15-x]==1){
		SCAN_LED_BUF_R[4]=SCAN_LED_BUF_R[4] & 0x0B;   
  }
}
void D1_NUM(unsigned char num){
	char i;
		i=sizeof(D1_NUM8)/sizeof(D1_NUM8[0]); 
		while(i--)
		display_buf[D1_NUM8[i]-1]=0;

	switch(num){
	case 0:
		i=sizeof(D1_NUM0)/sizeof(D1_NUM0[0]); 
		while(i--)
		display_buf[D1_NUM0[i]-1]=1;
	break;
	
	case 1:
		i=sizeof(D1_NUM1)/sizeof(D1_NUM0[1]); 
		while(i--)
		display_buf[D1_NUM1[i]-1]=1;
	break;

	case 2:
		i=sizeof(D1_NUM2)/sizeof(D1_NUM0[2]); 
		while(i--)
		display_buf[D1_NUM2[i]-1]=1;
	break;

	case 3:
		i=sizeof(D1_NUM3)/sizeof(D1_NUM3[0]); 
		while(i--)
		display_buf[D1_NUM3[i]-1]=1;
	break;

	case 4:
		i=sizeof(D1_NUM4)/sizeof(D1_NUM4[0]); 
		while(i--)
		display_buf[D1_NUM4[i]-1]=1;
	break;

	case 5:
		i=sizeof(D1_NUM5)/sizeof(D1_NUM5[0]); 
		while(i--)
		display_buf[D1_NUM5[i]-1]=1;
	break;

		case 6:
		i=sizeof(D1_NUM6)/sizeof(D1_NUM6[0]); 
		while(i--)
		display_buf[D1_NUM6[i]-1]=1;
	break;

	case 7:
		i=sizeof(D1_NUM7)/sizeof(D1_NUM7[0]); 
		while(i--)
		display_buf[D1_NUM7[i]-1]=1;
	break;

	case 8:
		i=sizeof(D1_NUM8)/sizeof(D1_NUM8[0]); 
		while(i--)
		display_buf[D1_NUM8[i]-1]=1;
	break;

	case 9:
		i=sizeof(D1_NUM9)/sizeof(D1_NUM9[0]); 
		while(i--)
		display_buf[D1_NUM9[i]-1]=1;
	break;
	case 0xff:
		i=sizeof(D1_NUM_F)/sizeof(D1_NUM_F[0]); 
		while(i--)
		display_buf[D1_NUM_F[i]-1]=1;
	break;


	}
}
void D2_NUM(unsigned char num){
	char i;
		i=sizeof(D2_NUM8)/sizeof(D2_NUM8[0]); 
		while(i--)
		display_buf[D2_NUM8[i]-1]=0;

	switch(num){
	case 0:
		i=sizeof(D2_NUM0)/sizeof(D2_NUM0[0]); 
		while(i--)
		display_buf[D2_NUM0[i]-1]=1;
	break;
	
	case 1:
		i=sizeof(D2_NUM1)/sizeof(D2_NUM0[1]); 
		while(i--)
		display_buf[D2_NUM1[i]-1]=1;
	break;

	case 2:
		i=sizeof(D2_NUM2)/sizeof(D2_NUM0[2]); 
		while(i--)
		display_buf[D2_NUM2[i]-1]=1;
	break;

	case 3:
		i=sizeof(D2_NUM3)/sizeof(D2_NUM3[0]); 
		while(i--)
		display_buf[D2_NUM3[i]-1]=1;
	break;

	case 4:
		i=sizeof(D2_NUM4)/sizeof(D2_NUM4[0]); 
		while(i--)
		display_buf[D2_NUM4[i]-1]=1;
	break;

	case 5:
		i=sizeof(D2_NUM5)/sizeof(D2_NUM5[0]); 
		while(i--)
		display_buf[D2_NUM5[i]-1]=1;
	break;

		case 6:
		i=sizeof(D2_NUM6)/sizeof(D2_NUM6[0]); 
		while(i--)
		display_buf[D2_NUM6[i]-1]=1;
	break;

	case 7:
		i=sizeof(D2_NUM7)/sizeof(D2_NUM7[0]); 
		while(i--)
		display_buf[D2_NUM7[i]-1]=1;
	break;

	case 8:
		i=sizeof(D2_NUM8)/sizeof(D2_NUM8[0]); 
		while(i--)
		display_buf[D2_NUM8[i]-1]=1;
	break;

	case 9:
		i=sizeof(D2_NUM9)/sizeof(D2_NUM9[0]); 
		while(i--)
		display_buf[D2_NUM9[i]-1]=1;
	break;
	
	case 0xff:
		i=sizeof(D2_NUM_F)/sizeof(D2_NUM_F[0]); 
		while(i--)
		display_buf[D2_NUM_F[i]-1]=1;
	break;
	}
}


void SCAN_NEW(){
static char cnt;
static char iii;	
	
	iii++;
	if(iii%2)
		cnt++;

		cnt=cnt%5;

			LED_IO_4(0);
			LED_IO_5(0);
			LED_IO_6(0);
			LED_IO_7(0);
			LED_IO_8(0);

			LED_IO_0(0);
			LED_IO_1(0);
			LED_IO_2(0);
			LED_IO_3(0);
		switch (cnt){
		case 0:
			LED_IO_0(SCAN_LED_BUF_R[0]    & 0x01);
        	LED_IO_1(SCAN_LED_BUF_R[0]>>1 & 0x01);
			LED_IO_2(SCAN_LED_BUF_R[0]>>2 & 0x01);
        	LED_IO_3(SCAN_LED_BUF_R[0]>>3 & 0x01);

			LED_IO_4(1);
			LED_IO_5(0);
			LED_IO_6(0);
			LED_IO_7(0);
			LED_IO_8(0);

		break;
		case 1:
			LED_IO_0(SCAN_LED_BUF_R[1]    & 0x01);
        	LED_IO_1(SCAN_LED_BUF_R[1]>>1 & 0x01);
			LED_IO_2(SCAN_LED_BUF_R[1]>>2 & 0x01);
        	LED_IO_3(SCAN_LED_BUF_R[1]>>3 & 0x01);
			LED_IO_4(0);
			LED_IO_5(1);
			LED_IO_6(0);
			LED_IO_7(0);
			LED_IO_8(0);


		break;

		case 2:
			LED_IO_0(SCAN_LED_BUF_R[2]    & 0x01);
        	LED_IO_1(SCAN_LED_BUF_R[2]>>1 & 0x01);
			LED_IO_2(SCAN_LED_BUF_R[2]>>2 & 0x01);
        	LED_IO_3(SCAN_LED_BUF_R[2]>>3 & 0x01);
			
			LED_IO_4(0);
			LED_IO_5(0);
			LED_IO_6(1);
			LED_IO_7(0);
			LED_IO_8(0);

		break;
		
		case 3:
			
			LED_IO_0(SCAN_LED_BUF_R[3]    & 0x01);
        	LED_IO_1(SCAN_LED_BUF_R[3]>>1 & 0x01);
			LED_IO_2(SCAN_LED_BUF_R[3]>>2 & 0x01);
        	LED_IO_3(SCAN_LED_BUF_R[3]>>3 & 0x01);
		
		LED_IO_4(0);
			LED_IO_5(0);
			LED_IO_6(0);
			LED_IO_7(1);
			LED_IO_8(0);

		
		break;
		
		case 4:
			LED_IO_0(SCAN_LED_BUF_R[4]    & 0x01);
        	LED_IO_1(SCAN_LED_BUF_R[4]>>1 & 0x01);
			LED_IO_2(SCAN_LED_BUF_R[4]>>2 & 0x01);
        	LED_IO_3(SCAN_LED_BUF_R[4]>>3 & 0x01);

			LED_IO_4(0);
			LED_IO_5(0);
			LED_IO_6(0);
			LED_IO_7(0);
			LED_IO_8(1);


		break;
		}
		
		
}