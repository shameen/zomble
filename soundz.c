//#include "Librairies Clean/motors.h"
//#include "Librairies Clean/prox.h"
#include "Librairies Clean/led.h"


#include "library/codec/e_sound.h"
//#include "library/motor_led/e_init_port.h"

int soundz(void)
	{
		e_init_port();
		e_init_sound();
	SetLed(7,1);
	/*	while(1)
			{
			long i;
			e_play_sound(0, 2112); //sound 1
			for(i=0; i<4000000; i++) {asm("nop");}
			e_play_sound(2116, 1760); //sound 2
			for(i=0; i<4000000; i++) {asm("nop");}
			e_play_sound(3878, 3412); //sound 3
			for(i=0; i<4000000; i++) {asm("nop");}
			e_play_sound(7294, 3732); //sound 4
			for(i=0; i<4000000; i++) {asm("nop");}
			e_play_sound(11028, 8016); //sound 5
			for(i=0; i<4000000; i++) {asm("nop");}
			}
	*/

	 e_play_sound(7294,3732);
	}

