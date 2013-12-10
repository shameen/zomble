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

			left =300;
			right = 300;
			left = left * 0.9;
			right = right * 0.9;

			/*wait*/for(i=0;i<40000;i++) {asm("nop");}
			SetSpeedRight(right);
			SetSpeedLeft(left);

			if(GetProx(0) >= 500 || GetProx(7) >= 500){
				left= -300;
				right= 300;
				for(i=0;i<40000;i++) {asm("nop");}
				SetSpeedRight(right);
				SetSpeedLeft(left);
				curious = 1;
			}
			
			if( GetProx(2) >= 500 ){
				for(j=0; j<= 10000; j++){
					curious = 1;
				}
			}
		}

		while (curious){

			if(GetProx(2) < 400){
				/*wait*/for(i=0;i<100000;i++) {asm("nop");}
				left = 300;
				right = 100;
				SetSpeedRight(right);
				SetSpeedLeft(left);
			}	
			while ( GetProx(0) >= 500 || GetProx(7) >= 1000 || GetProx(1) >= 800){
					
		
				/*wait*/for(i=0;i<40000;i++) {asm("nop");}
				left = -300;
				right = 300;
				SetSpeedRight(right);
				SetSpeedLeft(left);
				
			}
			if (GetProx(2) > 600){
				/*wait*/for(i=0;i<100000;i++) {asm("nop");}
				left = 100;
				right = 300;
				SetSpeedRight(right);
				SetSpeedLeft(left);			
			}
			if ( GetProx(2) >= 450 && GetProx(0) <= 500 && GetProx(7) <= 800 && GetProx(1) <= 800 && GetProx(6) <= 800 && GetProx(2) <= 550){
				for(i=0;i<100000;i++) {asm("nop");}

					left =300;
					right = 300;
					left = left * 0.9;
					right = right * 0.9;
		
					/*wait*/for(i=0;i<40000;i++) {asm("nop");}
					SetSpeedRight(right);
					SetSpeedLeft(left);
			}
			if (GetProx(5) > 600 || GetProx(6) > 600 ){
				/*wait*/for(i=0;i<100000;i++) {asm("nop");}
				left = 300;
				right = 0;
				SetSpeedRight(right);
				SetSpeedLeft(left);			
			}
		}
	}
}		

