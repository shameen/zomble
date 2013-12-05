/****************************************************************
* 			Initialization of port of e-puck			 		*
*			Version 1.0 november 2005							*
*			Michael Bonani, Francesco Mondada, Davis Dadie		*
*																*
****************************************************************/



#include "epuck_ports.h"

void InitPort(void)
{

/********************** OUTPUTS ***************************/
	/*LEDS*/
	LED0 = 0;
	LED1 = 0;
	LED2 = 0;
	LED3 = 0;
	LED4 = 0;
	LED5 = 0;
	LED6 = 0;
	LED7 = 0;
	LED0_dir = OUTPUT_PIN;
	LED1_dir = OUTPUT_PIN;
	LED2_dir = OUTPUT_PIN;
	LED3_dir = OUTPUT_PIN;
	LED4_dir = OUTPUT_PIN;
	LED5_dir = OUTPUT_PIN;
	LED6_dir = OUTPUT_PIN;
	LED7_dir = OUTPUT_PIN;
	
	front_LED = 0;
	front_LED_dir = OUTPUT_PIN;

	body_LED = 0;
	body_LED_dir = OUTPUT_PIN;

	/*IR*/
	pulse_IR0 = 0;
	pulse_IR1 = 0;
	pulse_IR2 = 0;
	pulse_IR3 = 0;
	pulse_IR0_dir = OUTPUT_PIN;
	pulse_IR1_dir = OUTPUT_PIN;
	pulse_IR2_dir = OUTPUT_PIN;
	pulse_IR3_dir = OUTPUT_PIN;

	/*basic audio*/
	audio_on = 0; /*turn of speaker and codec*/
	audio_on_dir = OUTPUT_PIN;
	
	/*motors*/
	motor1_pha = 0;
	motor1_phb = 0;
	motor1_phc = 0;
	motor1_phd = 0;
	motor2_pha = 0;
	motor2_phb = 0;
	motor2_phc = 0;
	motor2_phd = 0;
	motor1_pha_dir = OUTPUT_PIN;
	motor1_phb_dir = OUTPUT_PIN;
	motor1_phc_dir = OUTPUT_PIN;
	motor1_phd_dir = OUTPUT_PIN;
	motor2_pha_dir = OUTPUT_PIN;
	motor2_phb_dir = OUTPUT_PIN;
	motor2_phc_dir = OUTPUT_PIN;
	motor2_phd_dir = OUTPUT_PIN;
	
	/*camera*/
	CAM_reset=0;
	CAM_reset_dir = OUTPUT_PIN;
	
	/*I2C*/
	SIO_C=0;
	SIO_D=0;
	
	SIO_C_dir= OUTPUT_PIN;
	SIO_D_dir= OUTPUT_PIN;
	
/********************** INPUTS **************************/
	
	/*low battery signal active low when Vbatt<3.4V*/
	batt_low_dir = INPUT_PIN;
	
	/*IR TV receiver on normal extension*/
	remote_dir = INPUT_PIN;
	
	/* selector*/
	selector0_dir = INPUT_PIN;
	selector1_dir = INPUT_PIN;
	selector2_dir = INPUT_PIN;
	selector3_dir = INPUT_PIN;
	batt_low_dir = INPUT_PIN;
	
	/*camera*/
	CAM_y0_dir = INPUT_PIN;
	CAM_y1_dir = INPUT_PIN;
	CAM_y2_dir = INPUT_PIN;
	CAM_y3_dir = INPUT_PIN;
	CAM_y4_dir = INPUT_PIN;
	CAM_y5_dir = INPUT_PIN;
	CAM_y6_dir = INPUT_PIN;
	CAM_y7_dir = INPUT_PIN;	
}
