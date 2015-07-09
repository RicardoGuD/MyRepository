/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        %template.h%
* Instance:         RPL_1
* %version:         1 %
* %created_by:      uid02495 %
* %date_created:    Fri Feb 28 13:41:01 2003 %
*=============================================================================*/
/* DESCRIPTION : Header file template                                         */
/*============================================================================*/
/* FUNCTION COMMENT : contains only symbols which are exported to internal    */
/* platform modules. This will not be delivered with the library              */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | DD/MM/YYYY  | SAR/SIF/SCN_xxx               | Mr. Template     */
/* Integration under Continuus CM                                             */
/*============================================================================*/

#ifndef TEMPLATE_H                               /* To avoid double inclusion */
#define TEMPLATE_H

/* Includes */
#include "MPC5606B.h"
/* -------- */


/* Exported types and constants */
/* ---------------------------- */

/* Types definition */
/* typedef */
typedef volatile unsigned char T_UBYTE;
typedef volatile unsigned short T_UWORD;


/*==================================================*/ 
/* Declaration of exported constants                */
/*==================================================*/ 
/* BYTE constants */


/* WORD constants */


/* LONG and STRUCTURE constants */



/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTES */


/* WORDS */


/* LONGS and STRUCTURES */


/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Exported functions prototypes and macros */
/* ---------------------------------------- */

/* Functions prototypes */

void initModesAndClock(void);
void disableWatchdog(void);
void initPeriClkGen(void);
void initEMIOS_0(void); 
void setPTAOUT(void);
void buttonDetect(void);
void manualMode(void);
void automaticMode(void);


/* Functions macros */

#define LED_UP_ON SIU.GPDO[68].R = 1
#define LED_DOWN_ON SIU.GPDO[69].R = 1

#define LED_UP_OFF SIU.GPDO[68].R = 0
#define LED_DOWN_OFF SIU.GPDO[69].R = 0

#define INIT_PUSH_BUTTON1 SIU.PCR[64].R = 0x0100 
#define INIT_PUSH_BUTTON2 SIU.PCR[65].R = 0x0100 
#define INIT_PUSH_BUTTON4 SIU.PCR[67].R = 0x0100 
  
#define INIT_LED1 SIU.PCR[68].R = 0x0200 
#define INIT_LED2 SIU.PCR[69].R = 0x0200 

/* Exported defines */
#define ENABLE 1
#define DISABLE 0

#define MIN_TIME_PRESS 10
#define LIMIT_AUTO_MODE 500

#define LEVEL0 0x00000000;
#define LEVEL1 0x80000000;
#define LEVEL2 0xC0000000;
#define LEVEL3 0xE0000000;
#define LEVEL4 0xF0000000;
#define LEVEL5 0xF8000000;
#define LEVEL6 0xFC000000;
#define LEVEL7 0xFE000000;
#define LEVEL8 0xFF000000;
#define LEVEL9 0xFF800000;
#define LEVEL10 0xFFC00000;

#define PUSH_BUTTON_UP SIU.GPDI[64].R
#define PUSH_BUTTON_DOWN SIU.GPDI[65].R
#define PUSH_BUTTON_PINCH SIU.GPDI[67].R

#define PTA14 SIU.GPDO[14].R 
#define PTA15 SIU.GPDO[15].R
#define PTA SIU.PGPDO[0].R
#endif


