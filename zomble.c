#include "init_port.h"
#include "motors.h"
#include "prox.h"
#include "led.h"

int zomble()
{
	long i = 0;                         // loop counter
	int left = 0;                       // speed of left wheel
	int right = 0;                      // speed of right wheel
	int waitlonger = 0;                 // if set to 1, will wait a bit longer in between each loop
	
	//variables
	int isZombie = 0;                   // 0 for human, 1 for zombie
	int maxspeed_zombie = 100;          // max speed for zombies (default: 100)
	int maxspeed_human = 200;           // max speed for humans  (default: 200)
	int maxspeed_zombiecharge = 800;    // speed that zombies charge at (default: 800)
	int zombieCurTurnSpeed = 5;         // speed that zombies turn to look around (default: 5)
	
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
			
			//make zombie look around left and right
			//todo: maybe make it only peek side to side
			//todo: check maxspeed
			left -= zombieturnspeed;
			right += zombieturnspeed;
			if (right>=maxspeed_zombie) {
				zombieturnspeed = zombieturnspeed*-1;
			}
			
			int humanDetected = 0;
			//todo:search for red
			if (humanDetected == 1) {
				//todo: adjust speed accordingly if it isnt straight ahead
				left = maxspeed_zombiecharge;
				right = maxspeed_zombiecharge;
			}
			
		}
		else { //is human
			
			//BEGIN FEAR (todo: check maxspeed)
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
			//END FEAR
			
			int becomingZombie = 0;
			//todo: detect attack from zombie
			if (becomingZombie == 1) {
				LedClear();
				SetBodyLed(1);
				isZombie = 1;
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
