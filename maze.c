#include "Librairies Clean/init_port.h"
#include "Librairies Clean/motors.h"
#include "Librairies Clean/prox.h"
#include "Librairies Clean/led.h"

void maze(void)
{
	long i;
//long j;
	InitMotors();
	InitProx();
	LedClear();
	SetLed(4,1);
	SetStepsRight(1);
	SetStepsLeft(1);
	int left = 0;
	int right = 0;
//	int waitlonger = 0;
    int curious = 0;
	int distance;
	while(1){
		while (curious == 0) {
			int j;
			for(i=0;i<100000;i++) {asm("nop");}

			left =300;
			right = 300;
			left = left * 0.9;
			right = right * 0.9;

			/*wait*/for(i=0;i<40000;i++) {asm("nop");}
			SetSpeedRight(right);
			SetSpeedLeft(left);

			if (GetProx(0) >= 600 || GetProx(7) >= 600){
				left= -300;
				right= 300;
				SetSpeedRight(right);
				SetSpeedLeft(left);
				for(i=0;i<20000;i++) {asm("nop");}
				curious = 1;
			}
			
			if( GetProx(2) >= 500 ){
				for(j=0; j<= 10000; j++){
					curious = 1;
				}
			}
		}

		while(curious==1){
			if(GetProx(2) < 400){
				left = 300; 
				right = 100; 
				SetSpeedRight(right); 
				SetSpeedLeft(left); 
				/*wait*/for(i=0;i<40000;i++) {asm("nop");}
			}
			while (GetProx(0) >= 500 || GetProx(7) >= 600 || GetProx(1) >= 400){
				//sharp turn left
				left = -300; 
				right = 300; 
				SetSpeedRight(right); 
				SetSpeedLeft(left); 
				/*wait*/for(i=0;i<40000;i++) {asm("nop");} 
			} 
			if (GetProx(2) > 600){ 
				//turn left
				left = 0; 
				right = 300; 
				SetSpeedRight(right); 
				SetSpeedLeft(left); 
				/*wait*/for(i=0;i<40000;i++) {asm("nop");} 
			} 	
			if ( GetProx(2) >= 400 && GetProx(0) < 500 && GetProx(7) < 600 && GetProx(1) < 400 && GetProx(6) <= 800 && GetProx(2) <= 600){ 
				//go forwards
				left = 300; 
				right = 300; 
				left = left * 0.9; 
				right = right * 0.9; 
				SetSpeedRight(right); 
				SetSpeedLeft(left); 
				/*wait*/for(i=0;i<40000;i++) {asm("nop");} 
			} 
			if (GetProx(5) > 600 || GetProx(6) > 600 ){ 
				left = 300; 
				right = -300; 
				SetSpeedRight(right); 
				SetSpeedLeft(left); 
				/*wait*/for(i=0;i<40000;i++) {asm("nop");} 
			}
			if (GetAmbientLight(0)<4050 || GetAmbientLight(7)<4050) {
				SetSpeedLeft(0);
				SetSpeedRight(0);
				int j;
				for (j=0;j<5;j++) {
					for (i=0;i<7;i++)
						SetLed(i,1);
					/*wait*/for(i=0;i<80000;i++) {asm("nop");}
					LedClear();
					/*wait*/for(i=0;i<80000;i++) {asm("nop");}
				}
				
				while (1);
			}
		}
	}		
}
