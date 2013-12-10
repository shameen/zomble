#include "stdio.h"
#include "string.h"

#include "Librairies Clean/uart_char.h"
#include "Librairies Clean/init_port.h"
#include "Librairies Clean/motors.h"
#include "Librairies Clean/led.h"
#include "Librairies Clean/ad_conv.h"

#include "other libs/followball.h"
#include "other libs/agenda.h"
#include "other libs/.h"
#include "library/a_d/advance_ad_scan/e_ad_conv.h"


#define PI 3.14159265358979

int love() {
	//system initialization 
	e_init_port();
	e_init_uart1();
	e_init_motors();
	e_init_ad_scan(ALL_ADC);

	//Reset if Power on (some problem for few robots)
	if (RCONbits.POR) {
		RCONbits.POR=0;
		__asm__ volatile ("reset");
	}
while(1){
	
		k2000_led();
		follow_neuron();
		e_start_agendas_processing();
	}

}