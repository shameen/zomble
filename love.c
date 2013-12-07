#include "p30f6014A.h"
#include "stdio.h"
#include "string.h"

#include "uart_char.h"
#include "init_port.h"
#include "init_port.h"
#include "motors.h"
#include "led.h"
#include "ad_conv.h"

#include "followball.h"

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