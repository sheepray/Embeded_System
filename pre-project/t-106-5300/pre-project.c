/*
Note:
	Good tutorial for timer/counter:
		@http://maxembedded.com/2011/06/avr-timers-timer0/
	ATmega2560 runs:
		16MHz clocks
	Timer1/counter1 (16bits) will be chosen with scale of 256. So 3 second requies total:
		0*2^16 + 62500; 

*/

#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

//#include "Arduino.h"


//port definition
#define LEDS_PORT PORTC
#define LEDS_DDR DDRC
#define LEDS_PIN PINC

#define BUTTON_DDR DDRA
#define Required_overflow 0
#define Remained_count 62500// 56428

volatile uint8_t total_overflow;

//interrupt handlers
ISR(TIMER1_OVF_vect){
	//remember how many interrupt has happened
	total_overflow++;
/*
if(total_overflow == 2){
	LEDS_PORT = 0xee;
	total_overflow = 0;
}
*/

}




void timer1_init(){
	//set up timer with scaler of 256
	TCCR1B |= _BV(CS12);

	//initialize counter
	TCNT1 = 0;

	//enable overflow interrupt;
	TIMSK1 |= _BV(TOIE1);
	
	//enable golal interrupt
	sei();

	//initize the overflow counter
	total_overflow = 0;
}







//program setup
void setup(){
	LEDS_DDR = 0xff;
	BUTTON_DDR = 0x00;//Read from PORTA
	PORTA = 0xff; // Activate PULL UP resistor

}



int main(void){
	setup();

	//initialize the LED
//	LEDS_PORT ^= LEDS_PORT;
	LEDS_PORT = 0xff;
	_delay_ms(500);
	LEDS_PORT = 0x00;	
	uint8_t status_pina = PINA;
//timer1_init();
	while(1){
		//check PINA has changed or not
		if(PINA != status_pina && PINA != 0xff){
			status_pina = PINA; //if changed, store the PINA to status_pina;
			LEDS_PORT = ~PINA; //light the LED;
			//enble the timer interrupt;
			timer1_init();

			while(total_overflow <= Required_overflow){
				//LEDS_PORT = total_overflow;			
			}

			while(TCNT1 != Remained_count){
				//sleep_mode();
			}
			//time is up, turn off the LED;
			LEDS_PORT = 0x00;
			TCNT0 = 0;
			total_overflow = 0;

		}



		//At the same time, turn the servo into corresponding position, disable servo control signal (do not generate/output PWM for servo) when the led is turned off
	}
	return 0;
}


