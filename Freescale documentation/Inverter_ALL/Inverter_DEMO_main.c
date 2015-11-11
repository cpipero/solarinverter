/*******************************************************************************
*
* File Name: Inverter_DEMO_main.c
*
* Description: Main application file 
*              DSP56800E_Quick_Start stationery
*
* Target: MC56F8023 device
*
*******************************************************************************/

/* required DSP56F800E_Quick_Start header */
#include "qs.h"

/* low-level driver headers for each module used */
#include "occs.h"
#include "sys.h"
#include "adc.h"
#include "cop.h"
#include "cmp.h"
#include "dac.h"
#include "gpio.h"
#include "iic.h"
#include "intc.h"
#include "pit.h"
#include "pwm.h"
#include "qtimer.h"
#include "sci.h"
#include "spi.h"
#include "gflib.h"
#include "freemaster.h"

//-------------------------------------------------------------------------------------------------
/* Macros */

#define UP				5
#define DOWN			10
#define RAMP			95
#define RUN				115
#define STOP			54
#define GO_DOWN			68
#define OFF_GRID		47
#define ON_GRID			37
#define LOCKED			112
#define UNLOCKED		121
#define DCBMAX			460.0		// DCBus Max Voltage - measured value = 0.999;
#define DCBLIM			380.0		// Limited max voltge on DCBus - for MPPT;							[380]
#define VOLTAGELIMIT	330.0		// Limited min voltge on DCBus for lowest output voltage; [207V AC]
#define DCBVOLT			365.0		// DCBus Voltage Desired Value - fix for debug only!!!				[365]
#define DCBLOWLIM		50.0		// DCBus voltage low limit - switch down the AC voltage generation;	[200]
#define IPWRMAX			1.00		// Max value of the output current [Ief];
#define IPWRLIM			0.8			// I_power output current limitation = 0.8Aef;
#define IPWR			0.2			// I_power output current desired value;
#define PWMSTARTVAL		0.07

#define DCBRAMPLIM_FRAC16	FRAC16((DCBVOLT - 2) / DCBMAX)
#define DCBRELAY_ON			FRAC16((DCBVOLT - 10) / DCBMAX)	// -10V;
#define DCBVOLT_FRAC16		FRAC16(DCBVOLT / DCBMAX)		// DCBus Voltage Desired Value;
#define DCBLIM_FRAC16		FRAC16(DCBLIM / DCBMAX)
#define DCBLLIM_FRAC16		FRAC16(DCBLOWLIM / DCBMAX)
#define VOLTAGELIM_FRAC16	FRAC16(VOLTAGELIMIT / DCBMAX)
#define IPWRLIM_FRAC16		FRAC16(IPWRLIM/IPWRMAX)
#define IPWR_FRAC16			FRAC16(IPWR/IPWRMAX)

//------PWM definitions----------
#define PWM_P		MC_PWM_SIGNAL_0 | MC_PWM_SIGNAL_1
#define PWM_S		MC_PWM_SIGNAL_2 | MC_PWM_SIGNAL_3
#define PWM_BAT		MC_PWM_SIGNAL_4 | MC_PWM_SIGNAL_5

//------GPIO_B definitions for 8023 inverter board-------
#define START_SW	BIT_0
#define OFFGR_SW	BIT_1
#define FAULT_LED	BIT_2
#define OFF_G_LED	BIT_3
#define RELAY		BIT_4
#define RELAY_P		BIT_5

//-------------------------------------------------------------------------------------------------
/* Variables */

static UWord8 u8PWM_P_state;		// Primary PWM state - ramping or stable 50/50;
static UWord8 u8PWM_S_state;		// Secondary PWM state;
static UWord8 u8PWM_B_state;		// Battery PWM state;
static UWord8 u8OutGenState;		// Output Generation State; [OFF_GRID, ON_GRID, STOP];
static UWord8 u8StartPWM_P;
static UWord8 u8StartSwitch;
static UWord8 u8sine_crossL, u8sine_crossH, u8AmplStatus;
static UWord16 u16Fault, u16UmaxSavedp, u16UmaxSavedn;
static UWord16 u16ImaxSavedp, u16ImaxSavedn;
static UWord16 u16LoopCnt, u16LoopSwitch1Cnt;
static Frac16 f16angle, f16angleInc, f16sinusVal, f16QT3Delay;
static Frac16 f16AmplValue, f16PWMOutput;
static Frac16 mf16DCBusControllerOutput;
static Frac16 f16PowerUef, f16PowerIef;
static Frac16 f16Uin, f16Iin;
static Frac16 f16INpower, f16INpower1, f16DeltaInPower;
static Frac16 f16PowerUmax, f16PowerImax;
static Frac16 f16Upower, f16Ipower, f16ImaxN, f16ImaxP;
static Frac16 f16DCBVoltSet, f16DCBAvg, f16UmaxN, f16UmaxP;
static Frac16 f16PowerUmax_Sp, f16PowerUmax_Sn, f16PowerUmaxS, f16ACZeroU;
static Frac16 f16PowerImax_Sp, f16PowerImax_Sn, f16PowerImaxS, f16ACZeroI;
static Frac16 f16ACZeroUavg, f16ACZeroIavg;		

/* Regulators definotions */
static GFLIB_CONTROLLER_PI_RECURRENT_LIM_T sPirLimDCBusParams;
Frac16 GFLIB_ControllerPIrLim(Frac16 f16Error, GFLIB_CONTROLLER_PI_RECURRENT_LIM_T * const pudtCtr);
//-------------------------------------------------------------------------------------------------
/* Functions */
void Init_Variables(void);
void PWM_Init(void);
void ControllersInit(void);
void CntrlSwitchTest(void);

//-------------------------------------------------------------------------------------------------
//** PWM - begin
pwm_sIndependentValues sPwmIndep;

//** PWM - end
//-------------------------------------------------------------------------------------------------

//*************************************************************************************************
void main (void) 
{
	/* initialize COP first */
	ioctl(COP, COP_INIT, NULL);
    
	/* initialize device pins */
	ioctl(SYS, SYS_INIT, NULL);
	ioctl(GPIO_A, GPIO_INIT, NULL);
	ioctl(GPIO_B, GPIO_INIT, NULL);
	ioctl(GPIO_C, GPIO_INIT, NULL);
	ioctl(GPIO_D, GPIO_INIT, NULL);
	
		/* Internal modules initialization */
	ioctl(ADC, ADC_INIT, NULL);
	ioctl(PIT_0, PIT_INIT, NULL);
	ioctl(PIT_0, PIT_COUNTER, PIT_DISABLE);
	ioctl(QTIMER_A0, QT_INIT, NULL);
	ioctl(QTIMER_A3, QT_INIT, NULL);
	
	//------------------------------------------------------	
	PWM_Init();
	
	Init_Variables();
	ControllersInit();
	
	u16UmaxSavedp = 0;
	u16UmaxSavedn = 0;
	
	/* initialize interrupt controller and enable interrupts */
	ioctl(INTC, INTC_INIT, NULL);
	
	/* initialize SCI module to enable FreeMaster */
	ioctl(SCI_0, SCI_INIT, NULL);

	FMSTR_Init();
	
	archEnableInt();
	
	ioctl(GPIO_B, GPIO_SET_PIN, FAULT_LED);	// deactivate FAULT_LED;
	ioctl(GPIO_B, GPIO_SET_PIN, RELAY_P);	// deactivate RELAY_P;
	f16DCBVoltSet = DCBVOLT_FRAC16;			// desired value of the DCBus Voltage;
//-------------------------------------------------------------------------------------------------	
	while(1)
	{
		if(u8StartSwitch == RUN) 
		{
			if(u8PWM_P_state == UP)
			{
				//-----------DCBus Regulator-----------------------------------
				mf16DCBusControllerOutput = GFLIB_ControllerPIrLim((f16DCBVoltSet - f16DCBAvg), &sPirLimDCBusParams);
				sPwmIndep.pwmChannel_0_Value = mf16DCBusControllerOutput;							// write values;
				sPwmIndep.pwmChannel_1_Value = FRAC16(1.0) - mf16DCBusControllerOutput;				// 
				f16QT3Delay = (mf16DCBusControllerOutput >> 6) - (mf16DCBusControllerOutput >> 10); // to set the right sample moment for ADC;
				
				//-------------------------------------------------------------
			}
			else if(u8PWM_P_state == DOWN)
			{
				if(!u16Fault)
				{
					//-------Start of PWM_P - primary side---------------------
					sPwmIndep.pwmChannel_0_Value = FRAC16(PWMSTARTVAL);
					sPwmIndep.pwmChannel_1_Value = FRAC16(1.0 - PWMSTARTVAL);
					
					u8PWM_P_state = RAMP;
					u8AmplStatus = RAMP;
					u8StartPWM_P = 1;				//|_for PWM outputs enable;
					u16LoopSwitch1Cnt = 0;			//|
				}
				else
				{
					Init_Variables();
					ControllersInit();
					ioctl(PIT_0, PIT_ROLLOVER_INT, PIT_ENABLE);
					ioctl(PIT_0, PIT_CLEAR_ROLLOVER_INT, NULL);
					ioctl(PIT_0, PIT_COUNTER, PIT_ENABLE);
				}
			}
			else if(u8PWM_P_state == RAMP)
			{
				//-----------DC_Bus RAMP-UP------------------------------------
				if(f16DCBAvg >= DCBLLIM_FRAC16) // DCBRAMPLIM_FRAC16 	// check for DCBus voltage level;
				{
					ioctl(PWM, PWM_CLEAR_FAULT_FLAG, PWM_FAULT_0);		// clear the fault flag;
					ioctl(PWM,PWM_WRITE_DISABLE_MAPPING_REG1,0x1111);	// Enable switch-OFF PWM01 by FAULT_0;
					ioctl(GPIO_A,GPIO_SETAS_PERIPHERAL,BIT_6);			// Enable FAULT_0 input; !!!!!
					u8PWM_P_state = UP;
					sPirLimDCBusParams.f16UpperLim = FRAC16(0.45);		// for DEBUG use <0.45;
					sPirLimDCBusParams.f16ErrorK_1 = 0;
					f16AmplValue = FRAC16(0.01);						// init for generate amplitude;
					u8AmplStatus = RAMP;
					f16angle = 0;
				}
			}
		}
		//-----------------------------------------------------------------------------------------
	
		else if(u8StartSwitch == STOP)
		{
			ioctl(PWM, PWM_OUTPUT_PAD, PWM_DISABLE);
			Init_Variables();
			ControllersInit();

			//---------------OFF_GRID mode-------------------------------------
			u8OutGenState = OFF_GRID;
			u8OutGenState = OFF_GRID;
			ioctl(GPIO_B,GPIO_CLEAR_PIN,RELAY_P);		// switch ON the power relay;
			ioctl(GPIO_B, GPIO_CLEAR_PIN, OFF_G_LED);	// activate OFF_G_LED;
			//-----------------------------------------------------------------
    		
    		u16Fault = 0;
 		}
 		
//-----------------Check Control Switches----------------------------------------------------------
		CntrlSwitchTest();		// check the switches ON/OFF and OFF_GRID;
		if(u16Fault) ioctl(GPIO_B, GPIO_CLEAR_PIN, FAULT_LED);			// activate FAULT_LED;
		else if(!u16Fault) ioctl(GPIO_B, GPIO_SET_PIN, FAULT_LED);		// deactivate FAULT_LED;

//-----------------Check DCBus Voltage level-------------------------------------------------------
		if(f16DCBAvg > DCBLLIM_FRAC16) u8PWM_S_state = UP;
		else if((f16DCBAvg < DCBLLIM_FRAC16)&&(u8PWM_S_state == UP)) u8PWM_S_state = GO_DOWN;
		
//-----------------Check Input Power from Solar Panel----------------------------------------------
		if(mf16DCBusControllerOutput < FRAC16(0.42))
		{
			f16DeltaInPower = f16INpower - f16INpower1;
			f16INpower1 = f16INpower;		// save previous value;
			f16INpower = mult(f16Uin,f16Iin);
			//------Compare Input Power----------------------------------------
			if(f16DCBAvg < FRAC16(0.35))
			{
				if(f16DeltaInPower > 0)
				{
					if(f16DCBAvg < DCBLIM_FRAC16) f16DCBVoltSet += (f16DeltaInPower >> 1);
				}
				else if(f16DeltaInPower < 0) f16DCBVoltSet -= (f16DeltaInPower >> 1);
			}
			else
			{
				if(f16DeltaInPower > 0)
				{
					if(f16DCBAvg < DCBLIM_FRAC16) f16DCBVoltSet += (f16DeltaInPower >> 2);
				}
				else if(f16DeltaInPower < 0) f16DCBVoltSet -= (f16DeltaInPower >> 2);
			}
		}
		
		if(f16DCBVoltSet > DCBLIM_FRAC16) f16DCBVoltSet = DCBLIM_FRAC16;	// limitation;
//-------------------------------------------------------------------------------------------------

//--------------Measure Umax Power Line------------------------------------------------------------
		if(!f16PowerUmax_Sn) f16PowerUmax_Sn = FRAC16(1.0);
		
		if(f16PowerUmax_Sp < f16Upower) f16PowerUmax_Sp = f16Upower;
		if(f16PowerUmax_Sn > f16Upower) f16PowerUmax_Sn = f16Upower;
		
		if((f16angle > FRAC16(0.9))&&(!u16UmaxSavedn))
		{
			f16UmaxN = f16PowerUmax_Sn;
			f16PowerUmax_Sn = FRAC16(1.0);
			u16UmaxSavedn = 1;
			u16UmaxSavedp = 0;
		}
		
		if((f16angle < FRAC16(0.1))&&(!u16UmaxSavedp))
		{
			f16UmaxP = f16PowerUmax_Sp;
			f16PowerUmax_Sp = 0;
			u16UmaxSavedp = 1;
			u16UmaxSavedn = 0;
		}
		
		f16ACZeroUavg = mult(f16UmaxP,FRAC16(0.5)) + mult(f16UmaxN,FRAC16(0.5));
		f16ACZeroU = mult(f16ACZeroU,FRAC16(0.9)) + mult(f16ACZeroUavg,FRAC16(0.1));
		f16PowerUmaxS = f16UmaxP - f16ACZeroU;
		f16PowerUmax = mult(f16PowerUmax,FRAC16(0.95)) + mult(f16PowerUmaxS,FRAC16(0.05));
		f16PowerUef = mult(f16PowerUmax,FRAC16(0.707));
		
//--------------Measure Imax Power Line------------------------------------------------------------
	
		if(!f16PowerImax_Sn) f16PowerImax_Sn = FRAC16(1.0);
		
		if(f16PowerImax_Sp < f16Ipower) f16PowerImax_Sp = f16Ipower;
		if(f16PowerImax_Sn > f16Ipower) f16PowerImax_Sn = f16Ipower;
		
		if((f16angle > FRAC16(0.9))&&(!u16ImaxSavedn))
		{
			
			f16ImaxN = f16PowerImax_Sn;
			f16PowerImax_Sn = FRAC16(1.0);
			u16ImaxSavedn = 1;
			u16ImaxSavedp = 0;
		}
		
		if((f16angle < FRAC16(0.1))&&(!u16ImaxSavedp))
		{
			
			f16ImaxP = f16PowerImax_Sp;
			f16PowerImax_Sp = 0;
			u16ImaxSavedp = 1;
			u16ImaxSavedn = 0;
		}

		f16ACZeroIavg = mult(f16ImaxP,FRAC16(0.5)) + mult(f16ImaxN,FRAC16(0.5));
		f16ACZeroI = mult(f16ACZeroI,FRAC16(0.9)) + mult(f16ACZeroIavg,FRAC16(0.1));
		f16PowerImaxS = f16ImaxP - f16ACZeroI;
		f16PowerImax = mult(f16PowerImax,FRAC16(0.95)) + mult(f16PowerImaxS,FRAC16(0.05));
		f16PowerIef = mult(f16PowerImax,FRAC16(0.707));
//-------------------------------------------------------------------------------------------------

		// feed the watchdog periodically;
	    ioctl(COP, COP_CLEAR_COUNTER, NULL);
	    
		FMSTR_Poll();
	}
}

/******************************************************************************
/	This interrupt is generated ones per two PWM periods (u16LoopCnt = 4)
/	to make the main computations.
/----------------------------------------------------------------------------*/
#pragma interrupt saveall	// if the function is executed in the ISR;
void swi_isr(void)
{
	//-------------Sinus generator---------------------------------------------
	
	f16angle = f16angle + f16angleInc;		// input value pi / 4;
	__turn_on_sat();						// turns on the saturation;
	f16sinusVal = GFLIB_Sin12Tlr(f16angle);	// Compute the sine value;
	__turn_off_sat();						// turns off the saturation;
	
	//-------------------------------------------------------------------------
	
	//-------------Make Average Values ----------------------------------------
	if(!f16Uin) f16Uin = (Frac16)(ioctl(ADC,ADC_READ_SAMPLE,2));		// f16ADCUprim is actualy measured value;
	if(!f16Iin) f16Iin = (Frac16)(ioctl(ADC,ADC_READ_SAMPLE,0));		// f16ADCIprim is actualy measured value;
	if(!f16DCBAvg) f16DCBAvg = (Frac16)(ioctl(ADC,ADC_READ_SAMPLE,6));	// f16DCBusVolt is actualy measured value;
	if(!f16Upower) f16Upower = (Frac16)(ioctl(ADC,ADC_READ_SAMPLE,4));
	if(!f16Ipower) f16Ipower = (Frac16)(ioctl(ADC,ADC_READ_SAMPLE,1));
	
	f16Uin = mult(f16Uin,FRAC16(0.95)) + mult(((Frac16)(ioctl(ADC,ADC_READ_SAMPLE,2))),FRAC16(0.05));
	f16Iin = mult(f16Iin,FRAC16(0.95)) + mult(((Frac16)(ioctl(ADC,ADC_READ_SAMPLE,0))),FRAC16(0.05));
	f16DCBAvg = mult(f16DCBAvg,FRAC16(0.95)) + mult(((Frac16)(ioctl(ADC,ADC_READ_SAMPLE,6))),FRAC16(0.05));
	f16Upower = mult(f16Upower,FRAC16(0.95)) + mult(((Frac16)(ioctl(ADC,ADC_READ_SAMPLE,4))),FRAC16(0.05));
	f16Ipower = mult(f16Ipower,FRAC16(0.95)) + mult(((Frac16)(ioctl(ADC,ADC_READ_SAMPLE,1))),FRAC16(0.05));
		
	//-------------------------------------------------------------------------

	//--------------Power Line Voltage Generator for OFF-GRID------------------
	if(u8OutGenState == OFF_GRID)
	{
		if(u8AmplStatus == RAMP)
		{
			if(f16AmplValue < FRAC16(0.46)) f16AmplValue += FRAC16(0.0001);
		}
		if(f16AmplValue == FRAC16(0.46)) u8AmplStatus = UP;
		if(f16AmplValue > FRAC16(0.46)) f16AmplValue = FRAC16(0.46); 	// amplitude limit;
		f16PWMOutput = mult(f16sinusVal,f16AmplValue) + FRAC16(0.5);	// sine modulation + shift to range <0;1>;
	}
	else f16PWMOutput = FRAC16(0.5);
	//-------------------------------------------------------------------------
	
	//-------------- Switch OFF the AC voltage generation ---------------------
	if((u8StartSwitch == GO_DOWN)||(u8PWM_S_state == GO_DOWN))
	{
		sPwmIndep.pwmChannel_0_Value = FRAC16(0.0);		// write output values;
		sPwmIndep.pwmChannel_1_Value = FRAC16(1.0);
		f16DCBVoltSet = 0;
		
		/*---------- Check the "zero" value of the sine -----------------------
		/----------------------------------------------------------------------
		/ 	switch OFF the generation when the output voltage is close to zero;
		/ 	disable PWM module and clear variables for measurement;
		/--------------------------------------------------------------------*/
		if(f16sinusVal < FRAC16(0.02))
		{
			u8sine_crossL = 1;
			if(u8sine_crossH == 1)
			{
				u8sine_crossH = 0;
				f16PWMOutput = FRAC16(0.5);					// PWM_S input;
				ioctl(PWM, PWM_OUTPUT_PAD, PWM_DISABLE);	// switch OFF PWMs;
				ioctl(GPIO_B, GPIO_SET_PIN, RELAY_P);		// switch OFF the power relay;
				u8StartSwitch = STOP;
				u8PWM_P_state = DOWN;
				u8PWM_S_state = DOWN;
				u8PWM_B_state = DOWN;
				u8sine_crossL = 0;
				u8sine_crossH = 0;
				f16AmplValue = 0;
				f16PowerUmax = FRAC16(0.5);
				f16PowerImax = 0;
				f16INpower1 = 0;
				u16Fault = 0;
				ioctl(GPIO_B, GPIO_SET_PIN, OFF_G_LED);	// deactivate OFF_G_LED;
			}
		}
		//---------- Check the "max" value of the sine ---------
		if(f16sinusVal > FRAC16(0.98))
		{
			u8sine_crossH = 1;
			if(u8sine_crossL == 1) u8sine_crossL = 0;
		}
	}
	//-------------------------------------------------------------------------
	
	if(u16LoopSwitch1Cnt) u16LoopSwitch1Cnt--;
	
	u16LoopCnt = 4;
}
/******************************************************************************
/	The main interrupt routine - need have the highest priority.
/----------------------------------------------------------------------------*/
#pragma interrupt 
void PwmReloadIsr(void)
{
	sPwmIndep.pwmChannel_2_Value = f16PWMOutput;	// for positive halfwave start;
													// [(FRAC16(1.0) - f16PWMOutput) = negative];
	ioctl(PWM, PWM_SET_NEG_BOTTOM_SIDE_POLARITY, PWM_ZERO_MASK);

//-----------------PWM, QTimer_A3 & DAC_1 Update-------------------------------
	
	ioctl(QTIMER_A3, QT_WRITE_COMPARE_REG1, (UWord16)f16QT3Delay); 	// for measurement moment;
	
//-----------------PWM Update--------------------------------------------------
	
	ioctl(PWM, PWM_UPDATE_VALUE_REGS_INDEP, &sPwmIndep);
	ioctl(PWM, PWM_CLEAR_RELOAD_FLAG, NULL);
		
//-----------------for correct start of PWM_P----------------------------------	
	
	if(u8StartPWM_P)
	{
		ioctl(PWM, PWM_OUTPUT_PAD, PWM_ENABLE);
		ioctl(PWM,PWM_OUTPUT_CONTROL,(MC_PWM_SIGNAL_2 | MC_PWM_SIGNAL_3));	// disable PWM2-3 outputs;
		u8StartPWM_P = 0;
	}
	
//-----------------PWM loop count for SWI interrupt generation-----------------
	if(!u16LoopCnt)
	{
		asm (nop);
		asm (nop);
		asm (swi #0);
	}
	else u16LoopCnt--;
}
/******************************************************************************
/	This routine locks the FAULT condition to u16Fault variable.
/	The PWM outputs are disabled by hardware automaticaly.
/	The PWM outputs must be enabled by SW.
/----------------------------------------------------------------------------*/
#pragma interrupt
void FaultIsr(void)
{
	ioctl(PWM, PWM_OUTPUT_PAD, PWM_DISABLE);		// switch OFF PWMs when FAULT active;
	ioctl(PWM, PWM_CLEAR_FAULT_FLAG, PWM_FAULT_0);	// clear the fault flag;
	
	//-------Allow higher current till the DCBus capacitor charged-------------
	if((Frac16)(ioctl(ADC,ADC_READ_SAMPLE,6)) < DCBRAMPLIM_FRAC16)
	{
		ioctl(PWM, PWM_OUTPUT_PAD, PWM_ENABLE);
		u16Fault = 0;
	}
	//-------Copy the fault state to variable----------------------------------
	else
	{
		u8PWM_P_state = DOWN;							// PWM_P OFF flag;
		u8PWM_S_state = DOWN;							// PWM_S OFF flag;
		u8PWM_B_state = DOWN;							// PWM_B OFF flag;
		u16Fault++;
	}
}
/******************************************************************************
/	For DEMO mode only !!!
/	----------------------
/	When FAULT condition activated, wait for 1 sec and turn OFF the inverter
/	by u8StartSwitch = STOP. Then the SW checks the status of the Startswitch
/	and starts run the inverter.
/----------------------------------------------------------------------------*/
#pragma interrupt
void PIT0_isr(void)
{
	ioctl(PIT_0, PIT_CLEAR_ROLLOVER_INT, NULL);
	ioctl(PIT_0, PIT_COUNTER, PIT_DISABLE);
	u8StartSwitch = STOP;
	u16Fault = 0;
}
/******************************************************************************
/	PWM variables initialization
/----------------------------------------------------------------------------*/
void PWM_Init(void)
{
	ioctl(PWM, PWM_INIT, NULL);
	ioctl(PWM, PWM_OUTPUT_PAD, PWM_DISABLE);		// disable all PWM pads (bit15);
	sPwmIndep.pwmChannel_0_Value = FRAC16(0.0);		// PWM_PA - primary side; Independent mode;
	sPwmIndep.pwmChannel_1_Value = FRAC16(1.0);		// PWM_PB - primary side; Independent mode;
	sPwmIndep.pwmChannel_2_Value = FRAC16(0.5);		// PWM_SA - secondary side; Complementary mode;
	sPwmIndep.pwmChannel_4_Value = FRAC16(0.0);		// PWM_ChA - charger phase A; Independent mode;
	sPwmIndep.pwmChannel_5_Value = FRAC16(0.0);		// PWM_ChB - charger phase B; Independent mode;
	ioctl(PWM, PWM_CLEAR_FAULT_FLAG, PWM_FAULT_0);	// clear the fault flag;
	ioctl(PWM, PWM_UPDATE_VALUE_REGS_INDEP, &sPwmIndep);
}
/******************************************************************************
/	Initiallization of some variables.
/----------------------------------------------------------------------------*/
void Init_Variables(void)
{
	f16angle = 0;
	f16angleInc = FRAC16(0.0091153);	// for 50Hz output;
	f16QT3Delay = FRAC16(0.001);
	f16PWMOutput = FRAC16(0.5);
	u8StartPWM_P = 0;
	u16LoopSwitch1Cnt = 0;
	f16INpower1 = 0;
	f16INpower = 0;
	f16DeltaInPower = 0;
	u8sine_crossL = 0;
	u8sine_crossH = 0;
	u8PWM_P_state = DOWN;
	u8PWM_B_state = DOWN;
	u8PWM_S_state = DOWN;
	u8StartSwitch = STOP;
	u8AmplStatus = DOWN;
	
	// Output value initialization;
	mf16DCBusControllerOutput = 0;
}
/******************************************************************************
/	Controller parameters initialization.
/----------------------------------------------------------------------------*/
void ControllersInit(void)
{
    sPirLimDCBusParams.f16CC1Sc = FRAC16(0.90);
	sPirLimDCBusParams.f16CC2Sc = FRAC16(-0.899);
	sPirLimDCBusParams.ui16NShift = 0;
	sPirLimDCBusParams.f16UpperLim = FRAC16(PWMSTARTVAL);
	sPirLimDCBusParams.f16LowerLim = FRAC16(0.0);
	sPirLimDCBusParams.f16ErrorK_1 = 0;
	sPirLimDCBusParams.f32Acc = 0;
}
/******************************************************************************
/	Check the status of the START_SW.
/----------------------------------------------------------------------------*/
void CntrlSwitchTest(void)
{
	//-------------Check the START switch--------------------------------------
	if(u8StartSwitch == STOP)
	{
		Init_Variables();

		if((ioctl(GPIO_B, GPIO_READ_DATA, NULL) & START_SW) == 0)
		{
			u8StartSwitch = RAMP;
			u16LoopSwitch1Cnt = 200;
		}
	}
	//-----------------------------------------------------------
	if(u8StartSwitch == RAMP)						// debounce feature;
	{
		if(!u16LoopSwitch1Cnt) 
		{
			if((ioctl(GPIO_B, GPIO_READ_DATA, NULL) & START_SW) == 0)
			{
				f16DCBVoltSet = DCBVOLT_FRAC16;		// desired value of the DCBus Voltage;
				u8StartSwitch = RUN;
			}
			else u8StartSwitch = STOP;
		}
	}
//-----------------------------------------------------------------------------
	if(u8StartSwitch == RUN)
	{
		if((ioctl(GPIO_B, GPIO_READ_DATA, NULL) & START_SW) == START_SW)	// START_SW switched OFF;
		{
			u8StartSwitch = GO_DOWN;				// Controlled SWITCH_OFF process;
		}
	}
	//-------------END of Check the START switch-------------------------------
}
//*****************************************************************************

