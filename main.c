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

int main(void)
{
	int selector=getselector();
	switch (selector) {
		case 0:aggressive();break;
		case 1:fear();break;
		case 2:curious();break;
		case 3:love();break;
		case 4:maze();break;
		default:zomble();break;
	}
}
