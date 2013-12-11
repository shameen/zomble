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
    int infectThreshold = 20;

    //setup
    InitMotors();
    InitProx();
    LedClear();
    SetBodyLed(1);
    SetStepsRight(1);
    SetStepsLeft(1);
    SetSpeedRight(100);
    SetSpeedLeft(100);

    while (1) {

        if (isZombie == 1) {
            left = left * 0.9;
            right = right * 0.9;
            left += 38;
            right += 38;
            for (i = 0; i < 7; i++) {
                //Zombie
                if (GetProx(i) >= 600) {
                    switch (i) {
                        //left side sensors
	                    case 0: left += 100;right += 50;break;
	                    case 1: left += 100;right -= 100;break;
	                    case 2: left += 100;right -= 100;break;
                        //back sensors
                    	case 3: left += 200; right -= 200;break;
                        //case 4:left-=300;right+=40;break;
                    	case 4:left += 200;right -= 200;break;
                        //right side sensors
	                    case 5:left -= 100;right += 100;break;
	                    case 6:left -= 50;right += 50;break;
	                    case 7:left += 100;right += 50;break;
                    }
                }

            }
            //make zombie look around left and right
            //todo: maybe make it only peek side to side
            //todo: check maxspeed
            zombieCurTurn += zombieTurnSpeed;
			left -= zombieCurTurn;
            right += zombieCurTurn;
            if (zombieCurTurn > zombieTurnSpeed * 50 || zombieCurTurn < -(zombieTurnSpeed * 50)) {
                zombieTurnSpeed = zombieTurnSpeed * -1;
            }

            int humanDetected = 0;
            //todo:search for green
            if (GetProx(0) > 600 || GetProx(7) > 600) {
                humanDetected = 1;
            }
            if (humanDetected == 1) {
                //todo: adjust speed accordingly if it isnt straight ahead
                SetSpeedLeft(maxspeed_zombiecharge);
                SetSpeedRight(maxspeed_zombiecharge);
                /*wait */ for (i = 0; i < 2000000; i++) {
                    asm("nop");
                }
                left = -100;
                right = -100;
                humanDetected = 0;
                waitlonger = 1;
            }
            //limit max speed (note: will forget direction if its a fast slight curve)
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
            }

        } else {
//=======================================================================
//human

            {                        
				//modified fear
                left = left * 0.9;
	            right = right * 0.9;
	            left += 38;
	            right += 38;
				for (i = 0; i < 7; i++) {
	                if (GetProx(i) >= 500) {
	                    switch (i) {
	                        //left side sensors
		                    case 0:left += 100;right -= 50;break;
		                    case 1:left -= 100;right += 100;break;
		                    case 2:left -= 100;right += 100;break;
	                        //back sensors
	                    	case 3:left -= 200; right += 200;break;
	                    	case 4:left -= 200;right += 200;break;
	                        //right side sensors
		                    case 5:left += 100;right -= 100;break;
		                    case 6:left += 50;right -= 50;break;
		                    case 7:left -= 100;right -= 50;break;
	                    }
	                }
				}


                if (GetProx(0) > 800 || GetProx(1) > 800 || GetProx(6) > 800 || GetProx(7) > 800) {

                    left = -250;
                    right = -800;
                } else if ((GetProx(2) > 800 || GetProx(3) > 800 || GetProx(4) > 800 || GetProx(5) > 800)) {
                    // Speed forwards for a period of time
                    left = 300;
                    right = 300;
                }



                //limit max speed (note: will forget direction if its a fast slight curve)
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
                }

                int becomingZombie = 0;
                //todo: detect attack from zombie
                for (i = 0; i < 7; i++) {
                    //touching from the same direction for a short time leads to zombie
                    if (GetProx(i) >= 800) {
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
                    /*wait */ for (i = 0; i < 200000; i++) {
                        asm("nop");
                    }
                    SetLed(0, 1);
                    /*wait */ for (i = 0; i < 100000; i++) {
                        asm("nop");
                    }
                    SetLed(7, 1);
                    SetLed(1, 1);
                    /*wait */ for (i = 0; i < 100000; i++) {
                        asm("nop");
                    }
                    SetLed(2, 1);
                    SetLed(6, 1);
                    /*wait */ for (i = 0; i < 100000; i++) {
                        asm("nop");
                    }
                    SetLed(3, 1);
                    SetLed(5, 1);
                    /*wait */ for (i = 0; i < 100000; i++) {
                        asm("nop");
                    }
                    SetLed(4, 1);
                    /*wait */ for (i = 0; i < 100000; i++) {
                        asm("nop");
                    }
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
