#include "Librairies Clean/init_port.h"
#include "Librairies Clean/motors.h"
#include "Librairies Clean/prox.h"
#include "Librairies Clean/led.h"

void love(void)
{
	long i = 0;						//loop counter
	int left = 0;					//speed of left wheel
	int right = 0;					//speed of right wheel
	long waitinterval = 40000;		//processor steps to wait between each iteration of the main loop
	
	long heartBeatInterval = 400000;	//Max interval before a heartbeat (in processor steps)
	long heartBeatCur = 0;			//Counts how many steps since last heartbeat
	int heartBeatLEDs = 0;			//0 for all off, 1 for all on
	
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
		
		/*adjusts wheel speed if something is near it in that direction*/
		for (i=0;i<7;i++) {
			//~1000 is about to touch
			//any less than 500 and it starts having false positives
			//note: could maybe make use of the ambient light function in 'prox'
			if (GetProx(i)>=500) {	
				switch (i) {
					//left side sensors
					case 0:left+=80;right+=50;break;
					case 1:left+=50;right-=50;break;
					case 2:left+=200;right-=300;break;
					//back sensors
					case 3:left+=300;right-=200;break;
					//case 4:left-=200;right+=300;break; //commented out because left priority below
					case 4:left+=300;right-=200;break;//testing left turn on both
					//right side sensors
					case 5:left-=300;right+=200;break;
					case 6:left-=50;right+=50;break;
					case 7:left+=80;right+=50;break;
				}
				SetLed(i,1);
			}
			else SetLed(i,0);
		}
        
        //too close
        if (GetProx(0)>800 || GetProx(7)>800) {
            left = -50;
            right = -50;
        }
        
		
		//heartbeat
		heartBeatCur++;
		//get mean average of both front sensors
		int frontProx = (GetProx(0) + GetProx(7)) / 2;
		if (frontProx < 1) frontProx = 1;
		//cool formula calculates maximum time for heartbeat
		int heartBeatMax = heartBeatInterval-frontProx*20;
		
		//if it's time to do heartbeat
		if (heartBeatCur*waitinterval > heartBeatMax) {
			//toggle between 0 and 1
			heartBeatLEDs = 1 - heartBeatLEDs;
			//set LEDs
			for (i=0;i<7;i++) {
				SetLed(i,heartBeatLEDs);
			}
			//reset timer
			heartBeatCur = 0;
		}
		
		
		
		
		
		//limit max speed (to 1000)
		if (left>1000) { left = 1000; }
		if (right>1000) { right = 1000; }
		if (left<-1000) { left = -1000; }
		if (right<-1000) { right = -1000; }
		
		/*wait*/for(i=0;i<waitinterval;i++) {asm("nop");}
		SetSpeedRight(right);
		SetSpeedLeft(left);
	}
}
