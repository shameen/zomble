#include "init_port.h"
#include "motors.h"
#include "prox.h"
#include "led.h"
#include "stdlib.h"

int curious()
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