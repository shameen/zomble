#include "Librairies Clean\init_port.h"
#include "Librairies Clean\motors.h"
#include "Librairies Clean\prox.h"
#include "Librairies Clean\led.h"
#include "other libs\utility.h"

#include "aggressive.h"
#include "fear.h"
#include "curious.h"
#include "love2.h"
#include "zomble.h"
//#include "soundz.h"

void test(void)
{
	InitPort();
	InitMotors();
	InitProx();
	long ambient = 0;
	long i;
	int left = 50;
	int right = 50;
	while (1) {
		LedClear();
		for (i=0;i<7;i++) {
			ambient = GetAmbientLight(i);
			if (ambient>3950) {
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
				SetLed(i,1);
			}	
			else SetLed(i,0);
		}
		SetSpeedRight(right);
		SetSpeedLeft(left);
		wait(10000);
	}
}

int main(void)
{
	int selector=getselector();
	switch (selector) {
		case 0:aggressive();break;
		case 1:fear();break;
		case 2:curious();break;
		case 3:love();break;
		case 4:maze();break;
		case 5:test();break;
		default:zomble();break;
	}
}
