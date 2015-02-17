#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

//port definition
#define LEDS_PORT PORTC
#define LEDS_DDR DDRC
#define LEDS_PIN PINC

#define BUTTON_DDR DDRB



//interrupt handlers
ISR(LOWLEVEL_IO_PINS_vect){
	//Identify which button is pressed
	uint8_t Button_pressed = -1;
	uint8_t PORTB_BC = PORTB;
	for(uint8_t i = 0; i < 8; i++){
		if((PORTB_BC && 1) == 0){
			Button_pressed = i;
		}else{
			PORTB_BC = PORTB_BC >> 1;
		}
	}



	//turn corresponding LED on in LEDS_PORT
	if(Button_pressed != -1){
		uint8_t temp_value = 1;
		temp_value = temp_value << Button_pressed;
		LEDS_PORT |= temp_value;

		//sleep 3 seconds
		_delay_ms(3000);

		//turn off the light
		LEDS_PORT &= ~temp_value;
	}
}












//program setup
void setup(){
	LEDS_DDR = 0xff;
	BUTTON_DDR = 0x00;//Read from PORTB
}



int main(void){
	setup();
	while(1){
	sleep_mode();	
		//Read push-button until a button is pressed;
		//Switch ON coresponding LED for a while;
		//At the same time, turn the servo into corresponding position, disable servo control signal (do not generate/output PWM for servo) when the led is turned off
	}
	return 0;
}


