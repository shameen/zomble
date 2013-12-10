#include "Librairies Clean/init_port.h"
#include "Librairies Clean/motors.h"
#include "Librairies Clean/prox.h"
#include "Librairies Clean/led.h"

- void fear(void)
{
	long i;
	InitMotors();
	InitProx();
	LedClear();
	SetBodyLed(1);
	SetStepsRight(1);
	SetStepsLeft(1);
	int left = 100;
	int right = 100;
	SetSpeedRight(right);
	SetSpeedLeft(left);
	while (1) {

		// If any of the front 4 sensors are in the range
		if (GetProx(0) > 800 || GetProx(1) > 800 || GetProx(6) > 800 || GetProx(7) > 800) {
			
			// speed backwards for a period of time
			left= -1000;right=-1000;
			SetSpeedRight(right);
			SetSpeedLeft(left);
			LedFearFlash();
			for(i=0;i<160000;i++) {asm("nop");}
			
			// Do a 180 degree spin
			left=-800;right=800;
			SetSpeedRight(right);
			SetSpeedLeft(left);
			LedFearFlash();
			for(i=0;i<500000;i++) {asm("nop");}
			
			// Speed forwards for a period of time
			left=1000;right=1000;
			SetSpeedRight(right);
			SetSpeedLeft(left);
			LedFearFlash();
			for(i=0;i<160000;i++) {asm("nop");}
			
			// Back to normal speed
			left=100;right=100;
			SetSpeedRight(right);
			SetSpeedLeft(left); 
		}
		else if((GetProx(2) > 800 || GetProx(3) > 800 || GetProx(4) > 800 || GetProx(5) > 800)) {
			// Speed forwards for a period of time
			left=1000;right=1000;
			SetSpeedRight(right);
			SetSpeedLeft(left);
			LedFearFlash();
			for(i=0;i<160000;i++) {asm("nop");}
			
			// Back to normal speed
			left=100;right=100;
			SetSpeedRight(right);
			SetSpeedLeft(left);
		}
		else {
			LedClear();
		}
	}

}
