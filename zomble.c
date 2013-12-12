#include "Librairies Clean/init_port.h"
#include "Librairies Clean/motors.h"
#include "Librairies Clean/prox.h"
#include "Librairies Clean/led.h"

void zomble(void)
{
    long i = 0;                  // loop counter
    int left = 0;                // speed of left wheel
    int right = 0;               // speed of right wheel
    int waitlonger = 0;          // if set to 1, will wait a bit longer in between each loop

    //variables
    int isZombie = 0;                // 0 for human, 1 for zombie
    int maxspeed_zombie = 100;       // max speed for zombies (default: 100)
    int maxspeed_human = 400;        // max speed for humans  (default: 200)
    int maxspeed_zombiecharge = 700; // speed that zombies charge at (default: 700)
    int zombieTurnSpeed = 20;        // speed that zombies turn to look around (default: 5)
    int zombieCurTurn = 0;           // counter
    int infectExposure[8] = { '0', '0', '0', '0', '0', '0', '0', '0' };
    int infectThreshold = 10;

    //setup
    InitMotors();
    InitProx();
    LedClear();
    SetBodyLed(1);
    SetStepsRight(1);
    SetStepsLeft(1);
    SetSpeedRight(100);
    SetSpeedLeft(100);
	for (i = 0; i < 7; i++) {
		SetLed(i,1);
	}

    while (1) {

        if (isZombie == 1) {
            left = left * 0.9;
            right = right * 0.9;
			left+=38;right+=38;

            /*make zombie look around left and right*/
            //todo: maybe make it only peek side to side
            //todo: check maxspeed
            /*zombieCurTurn += zombieTurnSpeed;
			left -= zombieCurTurn;
            right += zombieCurTurn;
            if (zombieCurTurn > zombieTurnSpeed * 5 || zombieCurTurn < -(zombieTurnSpeed * 5)) {
                zombieTurnSpeed = zombieTurnSpeed * -1;
            }*/

			/*ZOMBIE AMBIENT LIGHT FIELD
			for (i=0;i<7;i++) {
				int ambient = GetAmbientLight(i);
				if (ambient<3900) {
					switch (i) {
	                    //left side sensors
	                    case 0: left += 50;right += 25;break;
	                    case 1: left += 50;right -= 50;break;
	                    case 2: left += 50;right -= 50;break;
	                    //back sensors
	                   	case 3: left += 100; right -= 100;break;
	                   	case 4:left += 100;right -= 100;break;
	                    //right side sensors
	                    case 5:left -= 50;right += 50;break;
	                    case 6:left -= 50;right += 50;break;
	                    case 7:left += 50;right += 25;break;
	                   }	
					SetLed(i,1);
				}	
				else SetLed(i,0);
			}*/
			//ZOMBIE PROXIMITY SENSOR FIELD
            for (i = 0; i < 7; i++) {
                if (GetProx(i) >= 700) {
                    switch (i) {
                        switch (i) {
	                        //front sensors
		                    case 0:case 7:
								left = 250;right = 250;break;
							case 1:left=300;right = -200;break;
							case 6:left=-200;right = 300;break;
	                        //back sensors
	                    	case 3:
	                    	case 4:left = 800;right = 800;break;
	                        //side sensors
							case 2:left = 300;right = 100;break;
		                    case 5:left = 100;right = 300;break;
	                    }
                    }
                }

            }

            int humanDetected = 0;
            //hit in front
            if (GetProx(0) > 700 || GetProx(7) > 700) {
				//check if it's giving light
                if (GetAmbientLight(0)<4080 || GetAmbientLight(7)<4080) {
					humanDetected==1;
				}
				else {
					// Turn around
					left=-900;right=900;
					SetSpeedRight(right);
					SetSpeedLeft(left);
					LedFearFlash();
					for(i=0;i<550000;i++) {asm("nop");}
					
					// Speed forwards for a period of time
					left=600;right=600;
					SetSpeedRight(right);
					SetSpeedLeft(left);
					LedFearFlash();
					for(i=0;i<160000;i++) {asm("nop");}
				}
            }
            if (humanDetected == 1) {
                //todo: adjust speed accordingly if it isnt straight ahead
				for (i=0;i<7;i++) { SetLed(i,1); }
                SetSpeedLeft(600);
                SetSpeedRight(600);
                /*wait */ for (i = 0; i < 1000000; i++) {asm("nop");}
                left = -100;
                right = -100;
                humanDetected = 0;
                waitlonger = 1;
            }
            /*limit max speed (note: will forget direction if its a fast slight curve)
            if (left > maxspeed_zombie) {
                left = maxspeed_zombie;
            }
            if (right > maxspeed_zombie) {
                right = maxspeed_zombie;
            }
            if (left < -maxspeed_zombie) {
                left = -maxspeed_zombie;
            }
            if (right < -maxspeed_zombie) {
                right = -maxspeed_zombie;
            }*/

        } else {







//=======================================================================
//=======================================================================
//human






            {                        
				//modified fear
                left = left * 0.9;
	            right = right * 0.9;
	            left += 38;
	            right += 38;
				for (i = 0; i < 7; i++) {
	                if (GetProx(i) >= 400) {
	                    switch (i) {
	                        //left side sensors
		                    case 0:case 7:
								left = 450;right = -450;break;
							case 1:left=-350;right = 350;break;
							case 6:left=350;right = -350;break;
	                        //back sensors
	                    	case 3:
	                    	case 4:left = 200;right = 200;break;
	                        //side sensors
							case 2:left = 150;right = 350;break;
		                    case 5:left = 350;right = 150;break;
	                    }
	                }
				}


                if (GetProx(0) > 800 || GetProx(1) > 800 || GetProx(6) > 800 || GetProx(7) > 800) {

                    left = -250;
                    right = -800;
					waitlonger=1;
                } else if ((GetProx(2) > 800 || GetProx(3) > 800 || GetProx(4) > 800 || GetProx(5) > 800)) {
                    // Speed forwards for a period of time
                    left = 300;
                    right = 300;
                }



                /*limit max speed (note: will forget direction if its a fast slight curve)
                if (left > maxspeed_human) {
                    left = maxspeed_human;
                }
                if (right > maxspeed_human) {
                    right = maxspeed_human;
                }
                if (left < -maxspeed_human) {
                    left = -maxspeed_human;
                }
                if (right < -maxspeed_human) {
                    right = -maxspeed_human;
                }*/

                int becomingZombie = 0;
                //todo: detect attack from zombie
                for (i = 0; i < 7; i++) {
                    //touching from the same direction for a short time leads to zombie
                    if (GetProx(i) >= 700) {
                        infectExposure[i]++;
                        if (infectExposure[i] > infectThreshold)
                            becomingZombie = 1;
                    } else
                        infectExposure[i] = 0;
                }

                if (becomingZombie == 1) {

                    //death 'animation'
                    SetSpeedRight(5);
                    SetSpeedLeft(5);
                    LedClear();
                    SetFrontLed(1);
                    /*wait */ for (i = 0; i < 100000; i++) {asm("nop");}
                    SetLed(0, 0);
                    /*wait */ for (i = 0; i < 100000; i++) {asm("nop");}
                    SetLed(7, 0);
                    SetLed(1, 0);
                    /*wait */ for (i = 0; i < 100000; i++) {asm("nop");}
                    SetLed(2, 0);
                    SetLed(6, 0);
                    /*wait */ for (i = 0; i < 100000; i++) {asm("nop");}
                    SetLed(3, 0);
                    SetLed(5, 0);
                    /*wait */ for (i = 0; i < 100000; i++) {asm("nop");}
                    SetLed(4, 0);
                    /*wait */ for (i = 0; i < 100000; i++) {asm("nop");}
					SetFrontLed(0);
                    isZombie = 1;
                }

            }
        }







        /*wait */ for (i = 0; i < 40000; i++) {
            asm("nop");
        }
        SetSpeedRight(right);
        SetSpeedLeft(left);

        if (waitlonger == 1) {
            /*wait */ for (i = 0; i < 100000; i++) {
                asm("nop");
            }
            waitlonger = 0;
        }
    }
}
