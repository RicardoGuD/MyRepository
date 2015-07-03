/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %WindowLifter.c%
* Instance:         RPL_1
* %version:         2 %
* %created_by:      Ricardo Guerra %
* %date_created:    Fri jun 22  2015 %
*=============================================================================*/
/* DESCRIPTION : C source template file                                       */
/*============================================================================*/
/* FUNCTION COMMENT : This file describes the C source template according to  */
/* the new software platform                                                  */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 03/07/2015  |                               | Mr. Template     */
/* Integration under Continuus CM                                             */
/*============================================================================*/

/* Includes */
/* -------- */
#include "WindowLifter.h"

/* Functions macros, constants, types and datas         */
 	enum rub_WindowLevelState 
 		{
			LEVEL_0,
			LEVEL_1,
			LEVEL_2,
			LEVEL_3,
			LEVEL_4,
			LEVEL_5,
			LEVEL_6,
			LEVEL_7,
			LEVEL_8,
			LEVEL_9,
			LEVEL_10	
		};

/* ---------------------------------------------------- */
/* Functions macros */

/*==================================================*/ 
/* Definition of constants                          */
/*==================================================*/ 
/* BYTE constants */


/* WORD constants */


/* LONG and STRUCTURE constants */



/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTE RAM variables */
T_UBYTE lub_MinimumButtonTime;
T_UBYTE rub_CountButtonPinch= 0;
T_UBYTE rub_AutoModeUp;
T_UBYTE rub_AutoModeDown;
T_UBYTE rub_ManualModeUp;
T_UBYTE rub_ManualModeDown;
T_UBYTE rub_PinchState;
//T_UBYTE rub_WindowLevelState = 0;
/* WORD RAM variables */

T_UWORD ruw_CountButtonUp=0;
T_UWORD ruw_CountButtonDown=0;

/* LONG and STRUCTURE RAM variables */

 enum rub_WindowLevelState WindowLevel = LEVEL_0;

/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Private defines */


/* Private functions prototypes */
/* ---------------------------- */
void Delay(int);
void changeWindowLvAuto(void);
void pinchEnable(void);
void pinchDetect(void);
void manualDirectionDetector(void);
void automaticDirectionDetector(void);
void manualWindowLevel(void);
void automaticWindowLevel(void);



/* Exported functions prototypes */
/* ----------------------------- */

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : inline_func	2
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/


/* Private functions */
/**************************************************************
 *  Name                 :	pinchEnable
 *  Description          :	active the antipinch function
 *  Parameters           :  	[void]
 *  Return               :      void
 *  Critical/explanation :      [No]
 **************************************************************/
void pinchEnable(void)
	{
	if(rub_PinchState)
						{
						rub_AutoModeDown=ENABLE;
						rub_ManualModeUp=0;
						}
		Delay(400);
	}
/**************************************************************
 *  Name                 :	changeWindowLvAuto
 *  Description          :	change the current level of the window
 *  Parameters           :  	[void]
 *  Return               :      void
 *  Critical/explanation :      [No]
 **************************************************************/
void changeWindowLvAuto(void)
	{
		if(rub_AutoModeUp)
					{
					if(rub_PinchState)
						{
						rub_AutoModeDown=ENABLE;
						rub_AutoModeUp=0;
						}
					WindowLevel++;
					}
				else if(rub_AutoModeDown)
					WindowLevel--;
	}
/**************************************************************
 *  Name                 :	Delay
 *  Description          :	Produce a Delay with a one milisecond base
 *  Parameters           :  	[Time]
 *  Return               :      void
 *  Critical/explanation :      [No]
 **************************************************************/
void Delay(int time) 
 {
 STM.CNT.R=0;
 while(STM.CNT.R<(time*1000)){}
 }

/**************************************************************
 *  Name                 : pinchDetect
 *  Description          : Detect if the pinch flag is active
 *  Parameters           : [void]
 *  Return               : void
 *  Critical/explanation :  [No]
 **************************************************************/

void pinchDetect(void)
			{
T_UBYTE lub_MinimumButtonTimePinch = 0;
			
		while (!PUSH_BUTTON_PINCH & !lub_MinimumButtonTimePinch)
			{
			rub_CountButtonPinch++;
			Delay(1);		
			if(rub_CountButtonPinch >= MIN_TIME_PRESS )
				{
				rub_PinchState=ENABLE;
				lub_MinimumButtonTimePinch = ENABLE;
				}	
			}
			}
			
/**************************************************************
 *  Name                 : automaticDirectionDetector
 *  Description          : Find out what is the direction of the window in automatic mode
 *  Parameters           : [void]
 *  Return               : void
 *  Critical/explanation : [No]
 **************************************************************/	
void automaticDirectionDetector(void)
		{
		ruw_CountButtonUp=0;
		ruw_CountButtonDown=0;
		rub_CountButtonPinch=0;
		if(rub_AutoModeDown)
			{
			LED_DOWN_ON;
			LED_UP_OFF;
			}
		else if(rub_AutoModeUp)
			{
			LED_DOWN_OFF;
			LED_UP_ON;
			}
		}
/**************************************************************
 *  Name                 :	manualDirectionDetector
 *  Description          :	Find out what is the current direction of the window movement in manual mode
 *  Parameters           :	[void]
 *  Return               :	void
 *  Critical/explanation :	[No]
 **************************************************************/
void manualDirectionDetector(void)
	{
	
	if(rub_ManualModeDown | rub_ManualModeUp)	
		{
			if (!PUSH_BUTTON_UP)
				{
				if(WindowLevel == LEVEL_10)
					{
					WindowLevel = WindowLevel;	
					}
				else
					{
				WindowLevel++;
				LED_UP_ON;
				LED_DOWN_OFF;
				rub_ManualModeDown = 0;
				ruw_CountButtonDown=0;
				pinchDetect();
					}
				}
 
 	  else if (!PUSH_BUTTON_DOWN)
				{
				if(WindowLevel == LEVEL_0)
					{
					WindowLevel = WindowLevel;	
					}
				else
					{
				WindowLevel--;
				LED_DOWN_ON;
				LED_UP_OFF;
				rub_ManualModeUp = 0;
				ruw_CountButtonUp=0;
					}
				}
	
		else if (PUSH_BUTTON_UP & PUSH_BUTTON_DOWN)
				{
				LED_UP_OFF;
				LED_DOWN_OFF;
				rub_ManualModeDown=0;
				rub_ManualModeUp=0;
				ruw_CountButtonUp=0;
				ruw_CountButtonDown=0;
				}
		}
	}
/**************************************************************
 *  Name                 :	manualWindowLevel
 *  Description          :	Change the level of the window manually
 *  Parameters           :	[void]
 *  Return               :	void
 *  Critical/explanation :	[No]
 **************************************************************/
 void manualWindowLevel(void)
	{		
	switch(WindowLevel)
		{
		case LEVEL_0:
			PTA = LEVEL0;
			rub_ManualModeDown=0;
			break;
		case LEVEL_1:
				PTA = LEVEL1;
				pinchEnable();
			//	Delay(400);	
			break;
		case LEVEL_2:
				PTA = LEVEL2;
		pinchEnable();
		//	Delay(400);
			break;
		case LEVEL_3:
				PTA = LEVEL3;
		pinchEnable();
		//	Delay(400);
			break;
		case LEVEL_4:
				PTA = LEVEL4;
			pinchEnable();
			//Delay(400);
			break;
		case LEVEL_5:
 			PTA = LEVEL5;
			pinchEnable();
		//	Delay(400);
			break;
		case LEVEL_6:
				PTA = LEVEL6;
		pinchEnable();
		//	Delay(400);
			break;
		case LEVEL_7:
				PTA = LEVEL7;
			pinchEnable();
		//	Delay(400);
			break;
		case LEVEL_8:
				PTA = LEVEL8;
			pinchEnable();
		//	Delay(400);
			break;
		case LEVEL_9:
				PTA = LEVEL9;
			pinchEnable();
		//	Delay(400);
			break;
		case LEVEL_10:
				PTA = LEVEL10;
				rub_ManualModeUp=0;
			break;
		default:
			PTA = PTA;
			break;
		}	
		}
		
/**************************************************************
 *  Name                 : automaticWindowLevel
 *  Description          : change the current level of the window in automatic mode
 *  Parameters           : [void]
 *  Return               : void
 *  Critical/explanation :  [No]
 **************************************************************/		
void automaticWindowLevel(void)
		{
		switch(WindowLevel)
			{
			case LEVEL_0:
				PTA = LEVEL0;
				if(rub_AutoModeUp)
					{
					WindowLevel++;
					}
			else if (rub_AutoModeDown)
					{
					rub_AutoModeDown = 0;
					LED_DOWN_OFF;
				if(rub_PinchState)
						{
						rub_PinchState=0;
						Delay(5000);
						}
					}
				break;

			case LEVEL_1:
			PTA = LEVEL1;
				Delay(400);
				changeWindowLvAuto();
				break;
			case LEVEL_2:
				PTA = LEVEL2;
				Delay(400);
					changeWindowLvAuto();
				break;
			case LEVEL_3:
					PTA = LEVEL3;
				Delay(400);
				
					changeWindowLvAuto();
				break;
			case LEVEL_4:
					PTA = LEVEL4;
				Delay(400);
				
					changeWindowLvAuto();
				break;
			case LEVEL_5:
 					PTA = LEVEL5;
				Delay(400);

					changeWindowLvAuto();
				break;

			case LEVEL_6:
					PTA = LEVEL6;
				Delay(400);
			
				changeWindowLvAuto();
				break;
			case LEVEL_7:
					PTA = LEVEL7;
				Delay(400);

					changeWindowLvAuto();
				break;
			case LEVEL_8:
					PTA = LEVEL8;
				Delay(400);
			
				changeWindowLvAuto();
				break;
			case LEVEL_9:
					PTA = LEVEL9;
				Delay(400);
	
					changeWindowLvAuto();
				break;
			case LEVEL_10:
					PTA = LEVEL10;
				
				if(rub_AutoModeUp)
					{
					if(rub_PinchState)
						{
						rub_AutoModeDown=ENABLE;
						rub_AutoModeUp=0;
						}
					rub_AutoModeUp = 0;
					LED_UP_OFF;
					}
				else if(rub_AutoModeDown)
					WindowLevel--;
				break;
			default:
				PTA = PTA;
				rub_AutoModeDown=0;
				rub_AutoModeUp=0;
				break;
			}
		}
/*-------------------------------------------------------------------------------*/		
/* Exported functions */

/**************************************************************
 *  Name                 :	setPTAOUT
 *  Description          :	Set the pins from port A as output
 *  Parameters           :  	[void]
 *  Return               :	void
 *  Critical/explanation :      [No]
 **************************************************************/
void setPTAOUT(void)
	{
SIU.PCR[0].R = 0x0200; 
SIU.PCR[1].R = 0x0200; 
SIU.PCR[2].R = 0x0200; 
SIU.PCR[3].R = 0x0200; 
SIU.PCR[4].R = 0x0200; 
SIU.PCR[5].R = 0x0200;
SIU.PCR[6].R = 0x0200; 
SIU.PCR[7].R = 0x0200; 
SIU.PCR[8].R = 0x0200; 
SIU.PCR[9].R = 0x0200; 	
	}
/**************************************************************
 *  Name                 :	initModesAndClock
 *  Description          :	Enable the modes and clocks needed to work
 *  Parameters           :  	[void]
 *  Return               :	void
 *  Critical/explanation :      [No]
 **************************************************************/
void initModesAndClock(void) 
{
  ME.MER.R = 0x0000001D;          /* Enable DRUN, RUN0, SAFE, RESET modes */
                                  /* Initialize PLL before turning it on: */
  CGM.FMPLL_CR.R = 0x02400100;    /* 8 MHz xtal: Set PLL0 to 64 MHz */   
  ME.RUN[0].R = 0x001F0074;       /* RUN0 cfg: 16MHzIRCON,OSC0ON,PLL0ON,syclk=PLL0 */
  ME.RUNPC[1].R = 0x00000010; 	  /* Peri. Cfg. 1 settings: only run in RUN0 mode */
  ME.PCTL[32].R = 0x01; 	      /* MPC56xxB/P/S ADC 0: select ME.RUNPC[1] */	
  ME.PCTL[68].R = 0x01; 	      /* MPC56xxB/S SIU: select ME.RUNPC[1] */	
                                  /* Mode Transition to enter RUN0 mode: */
  ME.MCTL.R = 0x40005AF0;         /* Enter RUN0 Mode & Key */
  ME.MCTL.R = 0x4000A50F;         /* Enter RUN0 Mode & Inverted Key */  
  while (ME.GS.B.S_MTRANS) {}     /* Wait for mode transition to complete */    
                                  /* Note: could wait here using timer and/or I_TC IRQ */
  while(ME.GS.B.S_CURRENTMODE != 4) {} /* Verify RUN0 is the current mode */
}

/**************************************************************
 *  Name                 :	disableWatchdog
 *  Description          :	Disable the watchdog function
 *  Parameters           :      [void]
 *  Return               :	void
 *  Critical/explanation :  	[No]
 **************************************************************/
void disableWatchdog(void) 
{
  SWT.SR.R = 0x0000c520;     /* Write keys to clear soft lock bit */
  SWT.SR.R = 0x0000d928; 
  SWT.CR.R = 0x8000010A;     /* Clear watchdog enable (WEN) */
}        
/**************************************************************
 *  Name                 :	initPeriClkGen
 *  Description          :	Enable the system's clock needed
 *  Parameters           :      [void]
 *  Return               :	void
 *  Critical/explanation :      [No]
 **************************************************************/
void initPeriClkGen(void) 
{
/* Use the following code as required for MPC56xxB or MPC56xxS:*/
  CGM.SC_DC[2].R = 0x80;   /* MPC56xxB/S: Enable peri set 3 sysclk divided by 1 */
}
/**************************************************************
 *  Name                 :	initEMIOS_0
 *  Description          :	Enable the channel 0 and register to use the internal timer STM
 *  Parameters           :  	[void]
 *  Return               :      void
 *  Critical/explanation :      [No]
 **************************************************************/
void initEMIOS_0(void)
 {
  STM.CR.R=0x00003F01;
  STM.CH[0].CCR.R=1;   /* Enable stopping channels when in debug mode */
 }

/**************************************************************
 *  Name                 :	buttonDetect
 *  Description          :	Detect the minimun required time to activate the window movement
 *  Parameters           :  [void]
 *  Return               :	void
 *  Critical/explanation :  [yes / No]
 **************************************************************/
void buttonDetect(void)
{

T_UBYTE lub_MinimumButtonTimeUp=0;
T_UBYTE lub_MinimumButtonTimeDown=0;

while (!PUSH_BUTTON_UP & !PUSH_BUTTON_DOWN)
	{
		LED_UP_OFF;
		LED_DOWN_OFF;
	}
	
while (!PUSH_BUTTON_UP & !lub_MinimumButtonTimeUp)
	{
	ruw_CountButtonUp++;
	Delay(1);
	if(ruw_CountButtonUp > MIN_TIME_PRESS & ruw_CountButtonUp <LIMIT_AUTO_MODE)
		{
		rub_AutoModeUp = ENABLE;
		rub_ManualModeUp = 0;
		}
	else if(ruw_CountButtonUp >= LIMIT_AUTO_MODE)
		{
		rub_ManualModeUp = ENABLE;
		rub_AutoModeUp = 0;
		lub_MinimumButtonTimeUp = ENABLE;	
		}
	}

	
while (!PUSH_BUTTON_DOWN & !lub_MinimumButtonTimeDown)
	{
	ruw_CountButtonDown++;
	Delay(1);
	if(ruw_CountButtonDown > MIN_TIME_PRESS & ruw_CountButtonDown <LIMIT_AUTO_MODE)
		{
		rub_AutoModeDown = ENABLE;
		rub_ManualModeDown = 0;
		}
	else if(ruw_CountButtonDown >= LIMIT_AUTO_MODE)
		{
		rub_ManualModeDown = ENABLE;
		rub_AutoModeDown = 0;
		lub_MinimumButtonTimeDown = ENABLE;
		}
	}
}

/**************************************************************
 *  Name                 :	manualMode
 *  Description          :	Close and open the window manually
 *  Parameters           :	[void]
 *  Return               :	void
 *  Critical/explanation :	[No]
 **************************************************************/
void manualMode(void)
	{
		manualDirectionDetector();
		manualWindowLevel();
	}
/**************************************************************
 *  Name                 :	automaticMode
 *  Description          :	Close and open the window automatically
 *  Parameters           :	[void]
 *  Return               :	void
 *  Critical/explanation :	[No]
 **************************************************************/
void automaticMode(void)
{
	while (rub_AutoModeDown | rub_AutoModeUp)
		{
	automaticDirectionDetector();
	
	pinchDetect();
	
	automaticWindowLevel();
	
		}
}
