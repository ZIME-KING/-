; Asm codes generated by Shanghai Haier C Compiler
; HRCO, Ver: 1.0,0133

#INCLUDE       	<ES7P0693.INC>
#INCLUDE       	<OPERATION.INC>
	EXTERN         	MUL_TEMP
	EXTERN         	MUL_TEMP
	EXTERN         	_Uart_Init
	EXTERN         	_ADC_init
	EXTERN         	_ADC_dis_init
	EXTERN         	_UART_send
	EXTERN         	_UART_sendDATA
	EXTERN         	_Send_test
	EXTERN         	_User_Get_measure_Val
	EXTERN         	_vcc_val
	EXTERN         	_RV
	EXTERN         	_RT
	EXTERN         	_Tmp
	PUBLIC         	_Task_1
	PUBLIC         	_Task_5
	PUBLIC         	_Task_50
	PUBLIC         	_Task_100
	PUBLIC         	_Task_200
	PUBLIC         	_Task_500
	PUBLIC         	_Task_1000
	PUBLIC         	_SetTime
	PUBLIC         	_GetTime
	PUBLIC         	_GetTimeDATA
	PUBLIC         	_CompareTime
	PUBLIC         	_CompareTimeDATA
	EXTERN         	_key_status
	EXTERN         	_key_busy
	EXTERN         	_touch_key_busy
	EXTERN         	_touch_key_staus
	EXTERN         	_scan_touch_key
	EXTERN         	_scan_key
	EXTERN         	_Set_LED
	EXTERN         	_Set_LEDDATA
	EXTERN         	_LED_Clear
	EXTERN         	_Updata_SCAN_LED_BUF_L
	EXTERN         	_D1_NUM
	EXTERN         	_D1_NUMDATA
	EXTERN         	_D2_NUM
	EXTERN         	_D2_NUMDATA
	EXTERN         	_SCAN_NEW
	EXTERN         	_acos
	EXTERN         	_acosDATA
	EXTERN         	_asin
	EXTERN         	_asinDATA
	EXTERN         	_atan2
	EXTERN         	_atan2DATA
	EXTERN         	_atan
	EXTERN         	_atanDATA
	EXTERN         	_ceil
	EXTERN         	_ceilDATA
	EXTERN         	_cos
	EXTERN         	_cosDATA
	EXTERN         	_cosh
	EXTERN         	_coshDATA
	EXTERN         	_eval_poly
	EXTERN         	_eval_polyDATA
	EXTERN         	_exp
	EXTERN         	_expDATA
	EXTERN         	_fabs
	EXTERN         	_fabsDATA
	EXTERN         	_floor
	EXTERN         	_floorDATA
	EXTERN         	_frexp
	EXTERN         	_frexpDATA
	EXTERN         	_ldexp
	EXTERN         	_ldexpDATA
	EXTERN         	_log10
	EXTERN         	_log10DATA
	EXTERN         	_log
	EXTERN         	_logDATA
	EXTERN         	_pow
	EXTERN         	_powDATA
	EXTERN         	_sin
	EXTERN         	_sinDATA
	EXTERN         	_sinh
	EXTERN         	_sinhDATA
	EXTERN         	_sqrt
	EXTERN         	_sqrtDATA
	EXTERN         	_tan
	EXTERN         	_tanDATA
	EXTERN         	_tanh
	EXTERN         	_tanhDATA
	EXTERN         	_Get_Sys_time
	EXTERN         	_display_buf
	EXTERN         	_buzzer_flag
	EXTERN         	_State_flag
	EXTERN         	_temperature
	EXTERN         	_Vbat_val
	EXTERN         	_global_count
	EXTERN         	_USB_Check
_GetTime_#T20372_45	EQU            	_GetTimeDATA + 0X2		; Bank 0
_CompareTime_#T20378_47	EQU            	_CompareTimeDATA + 0X2		; Bank 0
_CompareTime_#T20399_47	EQU            	_CompareTimeDATA + 0X6		; Bank 0
_CompareTime_#T20409_47	EQU            	_CompareTimeDATA + 0X8		; Bank 0
_CompareTime_#T20410_47	EQU            	_CompareTimeDATA + 0XA		; Bank 0
_CompareTime_#T20412_47	EQU            	_CompareTimeDATA + 0X0		; Bank 0
#TMP	EQU            	?_TMP+ 0X4		; Bank 0
?_TMP_RET	EQU            	?_TMP		; Bank 0
_MULA_0#sh	EQU            	(MULA - 0X6080) % 0X40 + 0xC0		; Bank 0
_MULB_0#sh	EQU            	(MULB - 0X6080) % 0X40 + 0xC0		; Bank 0
_MULL_0#sh	EQU            	(MULL - 0X6080) % 0X40 + 0xC0		; Bank 0
_MULH_0#sh	EQU            	(MULH - 0X6080) % 0X40 + 0xC0		; Bank 0
_DIVEL_0#sh	EQU            	(DIVEL - 0X6080) % 0X40 + 0xC0		; Bank 0
_DIVEM_0#sh	EQU            	(DIVEM - 0X6080) % 0X40 + 0xC0		; Bank 0
_DIVSL_0#sh	EQU            	(DIVSL - 0X6080) % 0X40 + 0xC0		; Bank 0
_DIVSH_0#sh	EQU            	(DIVSH - 0X6080) % 0X40 + 0xC0		; Bank 0
_DIVQL_0#sh	EQU            	(DIVQL - 0X6080) % 0X40 + 0xC0		; Bank 0
_DIVQM_0#sh	EQU            	(DIVQM - 0X6080) % 0X40 + 0xC0		; Bank 0
_DIVRL_0#sh	EQU            	(DIVRL - 0X6080) % 0X40 + 0xC0		; Bank 0
_DIVRH_0#sh	EQU            	(DIVRH - 0X6080) % 0X40 + 0xC0		; Bank 0
_DIVC_0#sh	EQU            	(DIVC - 0X6080) % 0X40 + 0xC0		; Bank 0
_DIVEU_0#sh	EQU            	(DIVEU - 0X6080) % 0X40 + 0xC0		; Bank 0
_DIVEH_0#sh	EQU            	(DIVEH - 0X6080) % 0X40 + 0xC0		; Bank 0
_FRAH_0#sh	EQU            	(FRAH - 0X6080) % 0X40 + 0xC0		; Bank 0
_FRAL_0#sh	EQU            	(FRAL - 0X6080) % 0X40 + 0xC0		; Bank 0
	_DESC          	SetTime,0X0,0X0
SetTime#	CSEG           
_SetTime
; /*
;  * software_Time.c
;  *
;  *  Created on: 2020年9月10日
;  *      Author: champion
;  */
; #include "../main.h"
; #include "../inc_user/software_Time.h"
;  TIME_TYPE_ST Task_1;
;  TIME_TYPE_ST Task_5;
;  TIME_TYPE_ST Task_50;
;  TIME_TYPE_ST Task_100;
;  TIME_TYPE_ST Task_200;
;  TIME_TYPE_ST Task_500;
;  TIME_TYPE_ST Task_1000;
;  //__attribute__机制在main之前运行一次 set_time
;  
;  //static attribute((constructor)) void SetTime();
; //设定间隔时间
; void SetTime(){
#line 26	C:\Users\king\Desktop\Mixing_cup\���豭����\user_code_NEW\HRCC Project Application1\HRCC Project Application1\Src_user\software_Time.c ; 	Task_1.TimeInter     = 1;//设定间隔时间
	CLR            	BKSR
;   26:(    ASGN_4,          1 ,            ,*(Task_1.4))

; ITemplate_ASGN1_4
	MOVI           	0x1
	SECTION        	0x2
	MOVA           	(_Task_1+0x4) & 0X7F		; Bank 2
	MOVI           	0x0
	MOVA           	(_Task_1+0x5) & 0X7F		; Bank 2
	MOVI           	0x0
	MOVA           	(_Task_1+0x6) & 0X7F		; Bank 2
	MOVI           	0x0
	MOVA           	(_Task_1+0x7) & 0X7F		; Bank 2
#line 27	C:\Users\king\Desktop\Mixing_cup\���豭����\user_code_NEW\HRCC Project Application1\HRCC Project Application1\Src_user\software_Time.c ; 	Task_5.TimeInter      = 5;
;   27:(    ASGN_4,          5 ,            ,*(Task_5.4))

; ITemplate_ASGN1_4
	MOVI           	0x5
	MOVA           	(_Task_5+0x4) & 0X7F		; Bank 2
	MOVI           	0x0
	MOVA           	(_Task_5+0x5) & 0X7F		; Bank 2
	MOVI           	0x0
	MOVA           	(_Task_5+0x6) & 0X7F		; Bank 2
	MOVI           	0x0
	MOVA           	(_Task_5+0x7) & 0X7F		; Bank 2
#line 28	C:\Users\king\Desktop\Mixing_cup\���豭����\user_code_NEW\HRCC Project Application1\HRCC Project Application1\Src_user\software_Time.c ; 	Task_50.TimeInter    = 50;
;   28:(    ASGN_4,         50 ,            ,*(Task_50.4))

; ITemplate_ASGN1_4
	MOVI           	0x32
	MOVA           	(_Task_50+0x4) & 0X7F		; Bank 2
	MOVI           	0x0
	MOVA           	(_Task_50+0x5) & 0X7F		; Bank 2
	MOVI           	0x0
	MOVA           	(_Task_50+0x6) & 0X7F		; Bank 2
	MOVI           	0x0
	MOVA           	(_Task_50+0x7) & 0X7F		; Bank 2
#line 29	C:\Users\king\Desktop\Mixing_cup\���豭����\user_code_NEW\HRCC Project Application1\HRCC Project Application1\Src_user\software_Time.c ; 	Task_100.TimeInter   = 100;
;   29:(    ASGN_4,        100 ,            ,*(Task_100.4))

; ITemplate_ASGN1_4
	MOVI           	0x64
	MOVA           	(_Task_100+0x4) & 0X7F		; Bank 2
	MOVI           	0x0
	MOVA           	(_Task_100+0x5) & 0X7F		; Bank 2
	MOVI           	0x0
	MOVA           	(_Task_100+0x6) & 0X7F		; Bank 2
	MOVI           	0x0
	MOVA           	(_Task_100+0x7) & 0X7F		; Bank 2
#line 30	C:\Users\king\Desktop\Mixing_cup\���豭����\user_code_NEW\HRCC Project Application1\HRCC Project Application1\Src_user\software_Time.c ; 	Task_200.TimeInter   = 200;
;   30:(    ASGN_4,        200 ,            ,*(Task_200.4))

; ITemplate_ASGN1_4
	MOVI           	0xc8
	MOVA           	(_Task_200+0x4) & 0X7F		; Bank 2
	MOVI           	0x0
	MOVA           	(_Task_200+0x5) & 0X7F		; Bank 2
	MOVI           	0x0
	MOVA           	(_Task_200+0x6) & 0X7F		; Bank 2
	MOVI           	0x0
	MOVA           	(_Task_200+0x7) & 0X7F		; Bank 2
#line 31	C:\Users\king\Desktop\Mixing_cup\���豭����\user_code_NEW\HRCC Project Application1\HRCC Project Application1\Src_user\software_Time.c ; 	Task_500.TimeInter   = 500;
;   31:(    ASGN_4,        500 ,            ,*(Task_500.4))

; ITemplate_ASGN1_4
	MOVI           	0xf4
	MOVA           	(_Task_500+0x4) & 0X7F		; Bank 2
	MOVI           	0x1
	MOVA           	(_Task_500+0x5) & 0X7F		; Bank 2
	MOVI           	0x0
	MOVA           	(_Task_500+0x6) & 0X7F		; Bank 2
	MOVI           	0x0
	MOVA           	(_Task_500+0x7) & 0X7F		; Bank 2
#line 32	C:\Users\king\Desktop\Mixing_cup\���豭����\user_code_NEW\HRCC Project Application1\HRCC Project Application1\Src_user\software_Time.c ; 	Task_1000.TimeInter  = 1000;
;   32:(    ASGN_4,       1000 ,            ,*(Task_1000.4))

; ITemplate_ASGN1_4
	MOVI           	0xe8
	MOVA           	(_Task_1000+0x4) & 0X7F		; Bank 2
	MOVI           	0x3
	MOVA           	(_Task_1000+0x5) & 0X7F		; Bank 2
	MOVI           	0x0
	MOVA           	(_Task_1000+0x6) & 0X7F		; Bank 2
	MOVI           	0x0
	MOVA           	(_Task_1000+0x7) & 0X7F		; Bank 2
#line 33	C:\Users\king\Desktop\Mixing_cup\���豭����\user_code_NEW\HRCC Project Application1\HRCC Project Application1\Src_user\software_Time.c ; }
;   33:(       RET,            ,            ,          )

; ITemplate_RET
	SECTION        	0x0
	RET            			; Bank 0		; ShBank 0
	_DESC          	GetTime,0X4,0X0,Get_Sys_time

SECTION1GetTime	UNINTIAL       	0		; Bank 0
	ORG            	0XBD		; Bank 0
_GetTimeDATA	RSEG           	0X4		; Bank 0
GetTime#	CSEG           
_GetTime
; void GetTime(TIME_TYPE_ST *TimeType)
; {
#line 36	C:\Users\king\Desktop\Mixing_cup\���豭����\user_code_NEW\HRCC Project Application1\HRCC Project Application1\Src_user\software_Time.c ;     TimeType->TimeStart = Get_Sys_time();//获取起始时间
	CLR            	BKSR
;   36:(    ASGN_1,   TimeType ,            ,   #T20372)

; ITemplate_ASGN1_4_R
	SECTION        	0x1
	MOV            	(_GetTimeDATA+0X0+0x1) & 0X7F,	0x0		; Bank 1
	MOVA           	(_GetTime_#T20372_45+0x1) & 0X7F		; Bank 1
	MOV            	(_GetTimeDATA+0X0) & 0X7F,	0x0		; Bank 1
	MOVA           	(_GetTime_#T20372_45) & 0X7F		; Bank 1
;   36:(     CALLR, (Get_Sys_time.0) ,            ,  *#T20372)

; ITemplate_CALL
	SEGMENTSEL     	_Get_Sys_time
	CALL           	_Get_Sys_time		; Bank 0		; ShBank 0
	SEGMENTSEL     	$
	MOVA           	(?_TMP) & 0X7F		; Bank 0
	MOV            	(?_TMP+0x1) & 0X7F,	0x0		; Bank 0
	MOVA           	(?_TMP+0x1) & 0X7F		; Bank 0
	MOV            	(?_TMP+0x2) & 0X7F,	0x0		; Bank 0
	MOVA           	(?_TMP+0x2) & 0X7F		; Bank 0
	MOV            	(?_TMP+0x3) & 0X7F,	0x0		; Bank 0
	MOVA           	(?_TMP+0x3) & 0X7F		; Bank 0
; ITemplate_SetRamRef
	MOVRA          	_GetTime_#T20372_45+0x1		; Bank 1
	MOVA           	IAAH
	MOVRA          	_GetTime_#T20372_45		; Bank 1
	MOVA           	IAAL
	MOV            	(?_TMP) & 0X7F,	0x0		; Bank 0
	MOVA           	IAD
	ISTEP          	0x1
	MOV            	(?_TMP+0x1) & 0X7F,	0x0		; Bank 0
	MOVA           	IAD
	ISTEP          	0x1
	MOV            	(?_TMP+0x2) & 0X7F,	0x0		; Bank 0
	MOVA           	IAD
	ISTEP          	0x1
	MOV            	(?_TMP+0x3) & 0X7F,	0x0		; Bank 0
	MOVA           	IAD
#line 37	C:\Users\king\Desktop\Mixing_cup\���豭����\user_code_NEW\HRCC Project Application1\HRCC Project Application1\Src_user\software_Time.c ; }
;   37:(       RET,            ,            ,          )

; ITemplate_RET
	RET            			; Bank 0		; ShBank 0
	_DESC          	CompareTime,0X4,0X0,Get_Sys_time

SECTION1CompareTime	UNINTIAL       	0		; Bank 0
	ORG            	0XBD		; Bank 0
_CompareTimeDATA	RSEG           	0XE		; Bank 0
CompareTime#	CSEG           
_CompareTime
;  
; uint8_t CompareTime(TIME_TYPE_ST *TimeType)//每隔1毫秒，计数器就会增加1
; {
#line 41	C:\Users\king\Desktop\Mixing_cup\���豭����\user_code_NEW\HRCC Project Application1\HRCC Project Application1\Src_user\software_Time.c ;     return ((Get_Sys_time()-TimeType->TimeStart) >= TimeType->TimeInter);
	CLR            	BKSR
;   41:(     CALLR, (Get_Sys_time.0) ,            ,   #T20378)

; ITemplate_CALL
	SEGMENTSEL     	_Get_Sys_time
	CALL           	_Get_Sys_time		; Bank 0		; ShBank 0
	SEGMENTSEL     	$
	MOVAR          	_CompareTime_#T20378_47		; Bank 1
	MOV            	(?_TMP+0x1) & 0X7F,	0x0		; Bank 0
	MOVAR          	_CompareTime_#T20378_47+0x1		; Bank 1
	MOV            	(?_TMP+0x2) & 0X7F,	0x0		; Bank 0
	MOVAR          	_CompareTime_#T20378_47+0x2		; Bank 1
	MOV            	(?_TMP+0x3) & 0X7F,	0x0		; Bank 0
	MOVAR          	_CompareTime_#T20378_47+0x3		; Bank 1
;   41:(    ASGN_1,   TimeType ,            ,   #T20399)

; ITemplate_ASGN1_4_R
	MOVRA          	_CompareTimeDATA+0X0+0x1		; Bank 1
	MOVAR          	_CompareTime_#T20399_47+0x1		; Bank 1
	MOVRA          	_CompareTimeDATA+0X0		; Bank 1
	MOVAR          	_CompareTime_#T20399_47		; Bank 1
;   41:(     ADD_2,   TimeType ,          4 ,   #T20409)

; ITemplate_ADD1_4
	MOVRA          	_CompareTimeDATA+0X0		; Bank 1
	ADDI           	0x4
	MOVAR          	_CompareTime_#T20409_47		; Bank 1
	MOVRA          	_CompareTimeDATA+0X0+0x1		; Bank 1
	ADDCI          	0x0
	MOVAR          	_CompareTime_#T20409_47+0x1		; Bank 1
;   41:(     SUB_4,    #T20378 ,   *#T20399 ,   #T20410)

; ITemplate_GetRamRef
	MOVRA          	_CompareTime_#T20399_47+0x1		; Bank 1
	MOVA           	IAAH
	MOVRA          	_CompareTime_#T20399_47		; Bank 1
	MOVA           	IAAL
	MOV            	IAD,	0x0
	MOVA           	(?_TMP) & 0X7F		; Bank 0
	ISTEP          	0x1
	MOV            	IAD,	0x0
	MOVA           	(?_TMP+0x1) & 0X7F		; Bank 0
	ISTEP          	0x1
	MOV            	IAD,	0x0
	MOVA           	(?_TMP+0x2) & 0X7F		; Bank 0
	ISTEP          	0x1
	MOV            	IAD,	0x0
	MOVA           	(?_TMP+0x3) & 0X7F		; Bank 0
; ITemplate_SUB1_4
	MOV            	(?_TMP) & 0X7F,	0x0		; Bank 0
	SECTION        	0x1
	SUB            	(_CompareTime_#T20378_47) & 0X7F,	0x0		; Bank 1
	MOVA           	(_CompareTime_#T20410_47) & 0X7F		; Bank 1
	MOVRA          	?_TMP+0x1		; Bank 0
	SUBC           	(_CompareTime_#T20378_47+0x1) & 0X7F,	0x0		; Bank 1
	MOVA           	(_CompareTime_#T20410_47+0x1) & 0X7F		; Bank 1
	MOVRA          	?_TMP+0x2		; Bank 0
	SUBC           	(_CompareTime_#T20378_47+0x2) & 0X7F,	0x0		; Bank 1
	MOVA           	(_CompareTime_#T20410_47+0x2) & 0X7F		; Bank 1
	MOVRA          	?_TMP+0x3		; Bank 0
	SUBC           	(_CompareTime_#T20378_47+0x3) & 0X7F,	0x0		; Bank 1
	MOVA           	(_CompareTime_#T20410_47+0x3) & 0X7F		; Bank 1
;   41:(    JLT_4U,    #T20410 ,   *#T20409 ,   #L20384)

; ITemplate_GetRamRef
	MOV            	(_CompareTime_#T20409_47+0x1) & 0X7F,	0x0		; Bank 1
	MOVA           	IAAH
	MOV            	(_CompareTime_#T20409_47) & 0X7F,	0x0		; Bank 1
	MOVA           	IAAL
	MOV            	IAD,	0x0
	MOVAR          	?_TMP		; Bank 0
	ISTEP          	0x1
	MOV            	IAD,	0x0
	MOVAR          	?_TMP+0x1		; Bank 0
	ISTEP          	0x1
	MOV            	IAD,	0x0
	MOVAR          	?_TMP+0x2		; Bank 0
	ISTEP          	0x1
	MOV            	IAD,	0x0
	MOVAR          	?_TMP+0x3		; Bank 0
; ITemplate_JLT1_4U
	MOVRA          	?_TMP+0x3		; Bank 0
	SUB            	(_CompareTime_#T20410_47+0x3) & 0X7F,	0x0		; Bank 1
	JBS            	PSW,	0x2
	GOTO           	#L20415
	SECTION        	0x0
	MOV            	(?_TMP+0x2) & 0X7F,	0x0		; Bank 0
	SECTION        	0x1
	SUB            	(_CompareTime_#T20410_47+0x2) & 0X7F,	0x0		; Bank 1
	JBS            	PSW,	0x2
	GOTO           	#L20415
	SECTION        	0x0
	MOV            	(?_TMP+0x1) & 0X7F,	0x0		; Bank 0
	SECTION        	0x1
	SUB            	(_CompareTime_#T20410_47+0x1) & 0X7F,	0x0		; Bank 1
	JBS            	PSW,	0x2
	GOTO           	#L20415
	SECTION        	0x0
	MOV            	(?_TMP) & 0X7F,	0x0		; Bank 0
	SECTION        	0x1
	SUB            	(_CompareTime_#T20410_47) & 0X7F,	0x0		; Bank 1
#L20415
	JBS            	PSW,	0x0
	GOTO           	#L20384
;   41:(    ASGN_1,          1 ,            ,   #T20412)

; ITemplate_ASGN1_4_R
	MOVI           	0x1
	MOVA           	(_CompareTime_#T20412_47) & 0X7F		; Bank 1
;   41:(       JMP,            ,            ,   #L20413)

; ITemplate_JMP
	GOTO           	#L20413
;   41:(     LABEL,    #L20384 ,            ,          )

; ITemplate_LABEL
#L20384
;   41:(    ASGN_1,          0 ,            ,   #T20412)

; ITemplate_CLR1_4_TMP
	CLR            	(_CompareTime_#T20412_47) & 0X7F		; Bank 1
;   41:(     LABEL,    #L20413 ,            ,          )

; ITemplate_LABEL
#L20413
;   41:(     RET_1,    #T20412 ,            ,      #RET)

; ITemplate_RET2_N
	MOV            	(_CompareTime_#T20412_47) & 0X7F,	0x0		; Bank 1
	MOVAR          	?_TMP_RET		; Bank 0
	SECTION        	0x0
	RET            			; Bank 0		; ShBank 0

SECTION2C__Users_king_Desktop_Mixing_cup_���豭����_user_code_NEW_HRCC_Project_Application1_HRCC_Project_Application1_Src_user_software_Time_c_STATIC	UNINTIAL       	0		; Bank 0
	ORG            	0X120		; Bank 0
_Task_1	RSEG           	0X8		; Bank 0
	ORG            	0X140		; Bank 0
_Task_5	RSEG           	0X8		; Bank 0
	ORG            	0X148		; Bank 0
_Task_50	RSEG           	0X8		; Bank 0
	ORG            	0X128		; Bank 0
_Task_100	RSEG           	0X8		; Bank 0
	ORG            	0X138		; Bank 0
_Task_200	RSEG           	0X8		; Bank 0
	ORG            	0X150		; Bank 0
_Task_500	RSEG           	0X8		; Bank 0
	ORG            	0X130		; Bank 0
_Task_1000	RSEG           	0X8		; Bank 0
	END
