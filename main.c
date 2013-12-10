#include "Librairies Clean\init_port.h"
#include "Librairies Clean\motors.h"
#include "Librairies Clean\prox.h"
#include "Librairies Clean\led.h"
#include "other libs\utility.h"

/*
#include "aggressive.h"
#include "fear.h"
#include "curious.h"
#include "love.c"
#include "zomble.h"
*/

void aggressive()
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

void fear()
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
			//LedFearFlash();
			for(i=0;i<160000;i++) {asm("nop");}
			
			// Do a 180 degree spin
			left=-800;right=800;
			SetSpeedRight(right);
			SetSpeedLeft(left);
			//LedFearFlash();
			for(i=0;i<500000;i++) {asm("nop");}
			
			// Speed forwards for a period of time
			left=1000;right=1000;
			SetSpeedRight(right);
			SetSpeedLeft(left);
			//LedFearFlash();
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
			//LedFearFlash();
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

void curious()
{
	long i;
	InitMotors();
	InitProx();
	LedClear();
	SetBodyLed(1);
	SetStepsRight(1);
	SetStepsLeft(1);
	int left = 0;
	int right = 0;
//	int waitlonger = 0;
    int curious = 0;
	while(1){
		while (curious == 0) {
			int j;
			for(i=0;i<100000;i++) {asm("nop");}

			left =200;
			right = 200;
			left = left * 0.9;
			right = right * 0.9;

			/*wait*/for(i=0;i<40000;i++) {asm("nop");}
			SetSpeedRight(right);
			SetSpeedLeft(left);

			if(GetProx(0) >= 500 || GetProx(7) >= 500){
				for (j=0; j <=10000; j++){
					left= -200;
					right= 200;
					for(i=0;i<40000;i++) {asm("nop");}
					SetSpeedRight(right);
					SetSpeedLeft(left);
					curious = 1;
					if(j == 9999)
						j=0;	
					if( GetProx(2) >= 550 ){ 
						j=10000;
						return 0;
					}
				}
			}
		}

/*	while(curious==1){
				left =0;
				right =0;
			SetSpeedRight(right);
			SetSpeedLeft(left);
			    for(i=0;i<500000;i++) {asm("nop");}
				long intrestLevel = rand() % 2000000 + 2000000;
intrestLevel = 200000000; 
   			 	for(j=0;j<intrestLevel;j++){
							if(GetProx(0)>800 && GetProx(7)>800 && !(GetProx(2)>800) ){
								
								for(i=0;i<800000;i++) {asm("nop");}
  							}else if(GetProx(1)>800 && GetProx(0)>800   ){
								left=200;
								right=400;
							}else if(GetProx(2)>800 && GetProx(3)>800 ){
								left=400;
								right=400;
							}else if(GetProx(2)>800 ){
								left=300;
								right=320;
							}else if(GetProx(3)>800 ){
								left=350;
								right=300;
							}else{
								left=400;
								right=-400;
							//for(i=0;i<500000;i++) {asm("nop");}
							}
                 intrestLevel = intrestLevel -1;
                 //for(i=0;i<40000;i++) {asm("nop");}
				SetSpeedRight(right);
				SetSpeedLeft(left);
		          

			}
				curious = 0;

		}*/

	}
}

void zomble()
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
			left -= zombieCurTurnSpeed;
			right += zombieCurTurnSpeed;
			if (right>=maxspeed_zombie) {
				zombieCurTurnSpeed = zombieCurTurnSpeed*-1;
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
			
			fear();
			
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

int main(void)
{
	int selector=getselector();
	switch (selector) {
		case 0:aggressive();break;
		case 1:fear();break;
		case 2:curious();break;
		//case 3:love();break;
		case 4:break;
		case 5:break;
		case 6:break;
		case 7:break;
		case 8:zomble();break;
		default:break;
		
	}
}
