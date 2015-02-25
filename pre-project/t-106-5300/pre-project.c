/*
Note:
	Good tutorial for timer/counter:
		@http://maxembedded.com/2011/06/avr-timers-timer0/
	ATmega2560 runs:
		16MHz clocks
	Timer1/counter1 (16bits) will be chosen with scale of 256. So 3 second requies total:
		3*16M/1024 = 46875  =  0*2^16(--65536--) + 46875; 



	Using Timer3 Fast PWM Mode, in Channel A at pin5
	20ms each cycle in 16MHz using 256 prescaler, needs TOP(1250) count;
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
#define Remained_count 46875//56428

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
	//stop the timer first
	TCCR1B &= ~(_BV(CS12));
	TCCR1B &= ~(_BV(CS10));
	TCNT1 = 0; 

	//set up timer with scaler of 1024
	TCCR1B |= _BV(CS12);
	TCCR1B |= _BV(CS10);

	//enable overflow interrupt;
	TIMSK1 |= _BV(TOIE1);
	
	//enable golal interrupt
	sei();

	//initize the overflow counter
	total_overflow = 0;
}



void timer3_init(uint8_t status_pina){
	TCCR3A |= _BV(COM3A1); //initialize COM3A1 to 1 and COM3A0 to 0 to 
	TCCR3A &= ~(_BV(COM3A0)); //enable OC3A as the output
	
	//setup timer3 running in fast moodule(1110) (top: ICRn)
	TCCR3A &= ~(_BV(WGM30));
	TCCR3A |= _BV(WGM31);
	TCCR3B |= _BV(WGM32);
	TCCR3B |= _BV(WGM33);


	TCCR3B &= ~(_BV(CS32));
	TCCR3B &= ~(_BV(CS30));
	//initialize the counter
	TCNT3 = 0;

	ICR3 = 1250;//top value
	OCR3A = 0;//this value should change based on the button pressed
	
	if(status_pina == 0b01111111){
		OCR3A = 94;//1.5ms
	}
	else if(status_pina == 0b10111111){
		OCR3A = 109;// 1.75
	}


	//run in 256 scale
	TCCR3B |= _BV(CS32);
//	TCCR3B |= _BV(CS30);

//	TIMSK3 |= _BV(TOIE3);

}

//program setup
void setup(){
	LEDS_DDR = 0xff;
	BUTTON_DDR = 0x00;//Read from PORTA
	PORTA = 0xff; // Activate PULL UP resistor

	DDRE |= _BV(PE3);//set OC3A as output
	
}



int main(void){
	setup();

	//initialize the LED, check if all LEDs are working.
	LEDS_PORT = 0xff;
	_delay_ms(500);
	LEDS_PORT = 0x00;	
	uint8_t status_pina = PINA;

	while(1){
		//check PINA has changed or not
		if(PINA != status_pina && PINA != 0xff){
			status_pina = PINA; //if changed, store the PINA to status_pina;
			LEDS_PORT = ~PINA; //light the LED;
			timer1_init();    //initialize timer 1;
			timer3_init(status_pina);   //prepare for the PWM using timer 3;
			
			while(total_overflow < Required_overflow){
				//LEDS_PORT = total_overflow;			
			}

			while(TCNT1 != Remained_count){
				//sleep_mode();
			}
			//time is up, turn off the LED;
			LEDS_PORT = 0x00;
			
			//stop timer1
			TCCR1B &= ~(_BV(CS12));
			TCCR1B &= ~(_BV(CS10));
			TCNT1 = 0;
			total_overflow = 0;
			
			//stop timer3
			TCCR3B &= ~(_BV(CS32));
			TCCR3B &= ~(_BV(CS30));

		}



		//At the same time, turn the servo into corresponding position, disable servo control signal (do not generate/output PWM for servo) when the led is turned off
	}
	return 0;
}
