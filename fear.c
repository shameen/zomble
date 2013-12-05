#include "init_port.h"
#include "motors.h"
#include "prox.h"
#include "led.h"

/* 13/11/13: this is just a slightly adjusted version of the current aggressive.c */

/* TODO: see if we can get a quick 180 degree turn */
int fear()
{
	long i;
	InitMotors();
	InitProx();
	LedClear();
	SetBodyLed(1);
	SetStepsRight(5);
	SetStepsLeft(5);
	int left = 0;
	int right = 0;
	while (1) {
			int j;
			
			/*light up led if something is near it in that direction*/
			left = left * 0.9;
			right = right * 0.9;
			left+=30;
			right+=30;

			for (j=0;j<7;j++) {
				if (GetProx(j)>=300) {	
					switch (j) {
						case 0:left-=150;right-=100;break;
						case 1:left-=200;right+=100;break;
						case 2:/*left-=250;right+=200;*/break;
						case 3:left-=300;right+=300;break;
						case 4:left+=300;right-=300;break;
						case 5:left+=300;right-=300;break;
						case 6:left+=100;right-=100;break;
						case 7:right-=150;left-=100;break;
					}
					SetLed(j,1);
				}
				else SetLed(j,0);
			}
			if (GetProx(0)>800 || GetProx(7)>800) {
				left  = 1000 - GetProx(7);
				right = 1000 - GetProx(0);
				/*wait*/for(i=0;i<10000;i++) {asm("nop");}
			}
			if (left+right>=-100 && left+right<=100) {
				//too slow
				if (left > right) {
					left = 200;
					right = -200;
				}
				else if (right > left){
					left = -200;
					right = 200;
				}
				else {
					//spin around in panic
					left = 1000;
					right = -1000;
				}
				/*wait*/for(i=0;i<80000;i++) {asm("nop");}
			}
			
			/*wait*/for(i=0;i<40000;i++) {asm("nop");}
			SetSpeedRight(right);
			SetSpeedLeft(left);
	}
}
