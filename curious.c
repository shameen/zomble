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
	int waitlonger = 0;
    int curious = 0;
	while(1){
		while (curious == 0) {
			int j;
			for(i=0;i<100000;i++) {asm("nop");}

			left+=38;
			right+=38;
			left = left * 0.9;
			right = right * 0.9;

			/*light up led if something is near it in that direction*/
			/*and also adjusts wheel speed depending on which ones are lit up*/
			for (j=0;j<7;j++) {
				if (GetProx(j)>=500) {	
					switch (j) {
						case 0:left+=150;right+=100;break;
						case 1:left+=100;right-=100;break;
						case 2:left+=300;right-=400;break;
						case 3:left+=400;right-=300;break;
						case 4:left-=300;right+=400;break;
						case 5:left-=400;right+=300;break;
						case 6:left-=100;right+=100;break;
						case 7:right+=150;left+=100;break;
					}
					SetLed(j,1);
				}
				else SetLed(j,0);
			}

			//back sensors
			if (GetProx(3)>800 || GetProx(4)>800) {
				//spin around in panic
				left = 700;
				right = -800;
				for(i=0;i<100000;i++) {asm("nop");}
				 
			}
			//front sensors
			if (GetProx(0)>800 || GetProx(7)>800)  {
               curious = 1;
				
			}	
			
			
			/*wait*/for(i=0;i<40000;i++) {asm("nop");}
			SetSpeedRight(right);
			SetSpeedLeft(left);

			
		}

	while(curious==1){
				left =0;
				right =0;
			SetSpeedRight(right);
			SetSpeedLeft(left);
			    for(i=0;i<500000;i++) {asm("nop");}
			
					while(1){
						if(GetProx(2)>800 && GetProx(3)>800 ){
							left=400;
							right=400;
						}else if(GetProx(2)>800 ){
							left=300;
							right=300;

					
						
						}else if(GetProx(3)>800 ){
							left=350;
							right=300;

					
						}	else if(GetProx(0)>800 || GetProx(7)>800   ){
							left=-300;
							right=400;
						for(i=0;i<800000;i++) {asm("nop");}
  }else if(GetProx(1)>800 || GetProx(0)>800   ){
							left=200;
							right=400;
						
						}
						else  {
						
							left=500;
							right=-400;
							//for(i=0;i<500000;i++) {asm("nop");}
						}
                 /*wait*/for(i=0;i<40000;i++) {asm("nop");}
				SetSpeedRight(right);
							SetSpeedLeft(left);
		

			}
				curious = 0;

		}

	}
}
