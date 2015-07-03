#include "MPC5606B.h"
#include "WindowLifter.h"


int main(void) 
{
initModesAndClock();
disableWatchdog();
initPeriClkGen(); 
initEMIOS_0();
setPTAOUT();

INIT_PUSH_BUTTON1;
INIT_PUSH_BUTTON2; 
INIT_PUSH_BUTTON4;
INIT_LED1;
INIT_LED2;
LED_UP_OFF;
LED_DOWN_OFF;

while(1)
	{
	buttonDetect();
	manualMode();
	automaticMode(); 
	}

}

