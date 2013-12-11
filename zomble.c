#include "Librairies Clean/init_port.h"
#include "Librairies Clean/motors.h"
#include "Librairies Clean/prox.h"
#include "Librairies Clean/led.h"

void zomble(void)
{
	long i = 0;                         // loop counter
	int left = 0;                       // speed of left wheel
	int right = 0;                      // speed of right wheel
	int waitlonger = 0;                 // if set to 1, will wait a bit longer in between each loop
	
	//variables
	int isZombie = 0;                   // 0 for human, 1 for zombie
	int maxspeed_zombie = 100;          // max speed for zombies (default: 100)
	int maxspeed_human = 200;           // max speed for humans  (default: 200)
	int maxspeed_zombiecharge = 700;    // speed that zombies charge at (default: 700)
	int zombieCurTurnSpeed = 5;         // speed that zombies turn to look around (default: 5)
	int infectExposure[8] = {'0','0','0','0','0','0','0','0'};
	int infectThreshold = 15;
	
	//setup
	InitMotors();
	InitProx();
	LedClear();
	//start with LEDs on
	for(i=0;i<8;i++) {
		SetLed(i,1);
	}
	SetStepsRight(1);
	SetStepsLeft(1);
	SetSpeedRight(100);
	SetSpeedLeft(100);
	
	while (1) {
		
		if (isZombie == 1) {
			for (i=0;i<7;i++) {
				//Zombie
				if (GetProx(i)>=500) {	
					switch (i) {
						//left side sensors
						case 0:left+=15;right+=10;break;
						case 1:left+=10;right-=10;break;
						case 2:left+=30;right-=40;break;
						//back sensors
						case 3:left+=40;right-=30;break;
						//case 4:left-=300;right+=40;break;
						case 4:left+=40;right-=30;break;//testing left turn on both
						//right side sensors
						case 5:left-=40;right+=30;break;
						case 6:left-=10;right+=10;break;
						case 7:left+=15;right+=10;break;
					}
					SetLed(i,1);
				}
				else SetLed(i,0);
			}
			//make zombie look around left and right
			//todo: maybe make it only peek side to side
			//todo: check maxspeed
			left -= zombieCurTurnSpeed;
			right += zombieCurTurnSpeed;
			if (right>=50 || right < -50) {
				zombieCurTurnSpeed = zombieCurTurnSpeed*-1;
			}
			
			int humanDetected = 0;
			//todo:search for green
			if (GetProx(0)>600 || GetProx(1)>600) {
				humanDetected = 1;
			}
			if (humanDetected == 1) {
				//todo: adjust speed accordingly if it isnt straight ahead
				left = maxspeed_zombiecharge;
				right = maxspeed_zombiecharge;
				/*wait*/for (i=0;i<2000000;i++) {asm("nop");}
				left=-100;
				right=-100;
				humanDetected = 0;
				waitlonger = 1;
			}
			
		}
		else { //is human
			
			{//modified fear
				//TODO: merge infinite loops? (optional)

				//opposite of aggressive
				left = left * 0.9;
				right = right * 0.9;
				left+=38;
				right+=38;
				for (i=0;i<7;i++) {
					//Human
					if (GetProx(i)>=500) {	
						switch (i) {
							//left side sensors
							case 0:left-=150;right-=100;break;
							case 1:left-=100;right-=200;break;
							case 2:left+=300;right-=400;break;
							//back sensors
							case 3:left+=400;right+=400;break;
							case 4:left+=400;right+=400;break;
							//right side sensors
							case 5:left-=400;right+=300;break;
							case 6:left-=100;right+=100;break;
							case 7:left-=150;right-=100;break;
						}
					}
				}
				


if (GetProx(0) > 800 || GetProx(1) > 800 || GetProx(6) > 800 || GetProx(7) > 800) {
			
			// speed backwards for a period of time
			left= -400;right=-400;
			SetSpeedRight(right);
			SetSpeedLeft(left);
			LedFearFlash();
			for(i=0;i<160000;i++) {asm("nop");}
			
			// Do a 180 degree spin
			left=-900;right=900;
			SetSpeedRight(right);
			SetSpeedLeft(left);
			LedFearFlash();
			for(i=0;i<700000;i++) {asm("nop");}
			
			// Speed forwards for a period of time
			left=400;right=400;
			SetSpeedRight(right);
			SetSpeedLeft(left);
			LedFearFlash();
			for(i=0;i<160000;i++) {asm("nop");}
			
			// Back to normal speed
			left=200;right=200;
			SetSpeedRight(right);
			SetSpeedLeft(left); 
		}
		else if((GetProx(2) > 800 || GetProx(3) > 800 || GetProx(4) > 800 || GetProx(5) > 800)) {
			// Speed forwards for a period of time
			left=400;right=400;
			SetSpeedRight(right);
			SetSpeedLeft(left);
			LedFearFlash();
			for(i=0;i<160000;i++) {asm("nop");}
			
			// Back to normal speed
			left=200;right=200;
			SetSpeedRight(right);
			SetSpeedLeft(left);
		}




				//limit max speed (note: will forget direction if its a fast slight curve)
				if (left>maxspeed_human) { left = maxspeed_human; }
				if (right>maxspeed_human) { right = maxspeed_human; }
				if (left<-maxspeed_human) { left = -maxspeed_human; }
				if (right<-maxspeed_human) { right = -maxspeed_human; }
				
				int becomingZombie = 0;
				//todo: detect attack from zombie
				for (i=0;i<7;i++) {
					//touching from the same direction for a short time leads to zombie
					if (GetProx(i)>=900) {	
						infectExposure[i]++;
						if (infectExposure[i]>infectThreshold)
							becomingZombie = 1;
					}
					else infectExposure[i]=0;
				}

				if (becomingZombie == 1) {
					
					//death 'animation'
					SetSpeedRight(5);
					SetSpeedLeft(5);
					LedClear();
					SetFrontLed(1);SetBodyLed(0);
					/*wait*/for (i=0;i<200000;i++) {asm("nop");}
					SetFrontLed(0);
					/*wait*/for (i=0;i<20000;i++) {asm("nop");}
					SetBodyLed(1);
					/*on*/for (i=0;i<7;i++) { SetLed(i,1); }
					/*wait*/for (i=0;i<200000;i++) {asm("nop");}
					SetBodyLed(0);
					LedClear();
					/*wait*/for (i=0;i<100000;i++) {asm("nop");}
					SetBodyLed(1);
					/*on*/for (i=0;i<7;i++) { SetLed(i,1); }

					isZombie = 1;
					break;
				}

			}
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
