#include "Librairies Clean/init_port.h"
#include "Librairies Clean/motors.h"
#include "Librairies Clean/prox.h"
#include "Librairies Clean/led.h"

void aggressive(void)
{
	long i = 0;			//loop counter, mainly for waiting
	int left = 0;		//speed of left wheel
	int right = 0;		//speed of right wheel
	int waitlonger = 0;	//if set to 1, will wait a bit longer in between each loop
	
	//setup
	InitMotors();
	InitProx();
	LedClear();
	//start with body light on and moving forwards
	SetBodyLed(1);
	SetStepsRight(1);
	SetStepsLeft(1);
	SetSpeedRight(100);
	SetSpeedLeft(100);
	
	while (1) {
		//smooth
		left = left * 0.9;
		right = right * 0.9;
		left+=38;
		right+=38;

		/*light up led if something is near it in that direction*/
		/*and also adjusts wheel speed depending on which ones are lit up*/
		for (i=0;i<7;i++) {
			//~1000 is about to touch
			//any less than 500 and it starts having false positives
			//note: could maybe make use of the ambient light function in 'prox'
			if (GetProx(i)>=500) {	
				switch (i) {
					//left side sensors
					case 0:left+=150;right+=100;break;
					case 1:left+=100;right-=100;break;
					case 2:left+=300;right-=400;break;
					//back sensors
					case 3:left+=400;right-=300;break;
					//case 4:left-=300;right+=400;break;
					case 4:left+=400;right-=300;break;//testing left turn on both
					//right side sensors
					case 5:left-=400;right+=300;break;
					case 6:left-=100;right+=100;break;
					case 7:left+=150;right+=100;break;
				}
				SetLed(i,1);
			}
			else SetLed(i,0);
		}

		/*
		//back sensors
		if (GetProx(3)>800 || GetProx(4)>800) {
			//spin around in panic
			left = 700;
			right = -800;
			waitlonger = 1;
			
		*/
		
		//front sensors
		//todo: blindly charges straight forwards, is that what we want?
		//		if not, then adjust slightly based on sensors
		if (GetProx(0)>800 || GetProx(7)>800) {
			//light up
			for (i=0;i<7;i++) {
				SetLed(i,1);
			}
			SetFrontLed(1);
			//push for a while
			SetSpeedRight(1000);
			SetSpeedLeft(1000);
			/*wait*/for(i=0;i<800000;i++) {asm("nop");}
			
			LedClear();
			//reverse after pushing
			left = -900;
			right = -900;
			waitlonger = 1;
		}
		
		//max speed
		if (left>1000) {
			left = 1000;
		}
		if (right>1000) {
			right = 1000;
		}
		if (left<-1000) {
			left = -1000;
		}
		if (right<-1000) {
			right = -1000;
		}
		
		/*wait*/for(i=0;i<40000;i++) {asm("nop");}
		SetSpeedRight(right);
		SetSpeedLeft(left);
		
		if (waitlonger == 1) {
			/*wait*/for(i=0;i<100000;i++) {asm("nop");}
			waitlonger = 0;
		}
	}
}
