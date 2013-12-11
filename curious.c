#include "Librairies Clean\init_port.h"
#include "Librairies Clean\motors.h"
#include "Librairies Clean\prox.h"
#include "Librairies Clean\led.h"
#include "stdlib.h"

void curious(void)
{
	long i;
	long ran = 0;
    long rantime = 0;
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
			if (GetProx(0)>500 && GetProx(7)>500)  {
               curious = 2;
			    left =0;
				right =0;
			}	
			
			
			/*wait*/for(i=0;i<40000;i++) {asm("nop");}
			SetSpeedRight(right);
			SetSpeedLeft(left);
            ran++;
			ran++;
			ran++;
			
		}

	while(curious==1){
			
			   if(GetProx(2) < 400){
				
				left = 300;
				right = 50;
				SetSpeedRight(right);
				SetSpeedLeft(left);
				/*wait*/for(i=0;i<40000;i++) {asm("nop");}
	            ran--;
			}	
			while ( GetProx(0) >= 500 || GetProx(7) >= 1000 || GetProx(1) >= 800){
				left = -300;
				right = 300;
				SetSpeedRight(right);
				SetSpeedLeft(left);
				/*wait*/for(i=0;i<40000;i++) {asm("nop");}
				ran--;
			}
			if (GetProx(2) > 600){
				left = 250;
				right = 300;
				SetSpeedRight(right);
				SetSpeedLeft(left);		
                 /*wait*/for(i=0;i<40000;i++) {asm("nop");}	
                			 
			}
			if ( GetProx(2) >= 400 && GetProx(0) <= 500 && GetProx(7) <= 800 && GetProx(1) <= 800 && GetProx(6) <= 800 && GetProx(2) <= 600){


					left =300;
					right = 300;
					left = left * 0.9;
					right = right * 0.9;
		
					
					SetSpeedRight(right);
					SetSpeedLeft(left);
					/*wait*/for(i=0;i<40000;i++) {asm("nop");}
					
			}
			if (GetProx(5) > 600 || GetProx(6) > 600 ){
				
				left = 300;
				right = 250;
				SetSpeedRight(right);
				SetSpeedLeft(left);		
			/*wait*/for(i=0;i<40000;i++) {asm("nop");}	
			}
			ran--;
			if(ran<0){
curious=3;
}

		}

	while(curious==2){
			if(ran % 2 == 0){
				
				left=-400;
                right=-400;
				SetSpeedRight(right);
				SetSpeedLeft(left);	
				
			for(i=0;i<500000;i++) {asm("nop");}
			left=-400;
            right=400;
			SetSpeedRight(right);
		    SetSpeedLeft(left);	
			for(i=0;i<250000;i++) {asm("nop");}
			curious=0;
			ran=0;
			}else{
			    curious=1;
				rantime = rand() % 5 + 2;
                ran = ((ran * rantime)* rantime);
				
			
			}
	}

if(curious==3){
	int k;
	for (k=0;k<7;k++) {
		SetLed(k,1);
	}
	ran=0;
	curious=0; 
	left=-400;
	right=400;
	SetSpeedRight(right);
	SetSpeedLeft(left);	
	for(i=0;i<480000;i++) {asm("nop");}
	for (k=0;k<7;k++) {
		SetLed(k,0);
	}
	left=300;
	right=300;
	SetSpeedRight(right);
	SetSpeedLeft(left);	
    for(i=0;i<240000;i++) {asm("nop");}
		}
	}
}