#include "init_port.h"
#include "motors.h"
#include "prox.h"
#include "led.h"

#include "aggressive.c"
#include "fear.c"
#include "curious.c"
#include "zomble.c"

int main(void)
{
	selector=getselector();
	switch (selector) {
		case 0:break;
		case 1:break;
		case 2:break;
		case 3:break;
		case 4:break;
		case 5:break;
		case 6:break;
		case 7:break;
		case 8:break;
		default:break;
		
	}
}

int getselector() {
	return SELECTOR0 + 2*SELECTOR1 + 4*SELECTOR2 + 8*SELECTOR3;
}