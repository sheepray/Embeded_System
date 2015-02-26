/*
Note:
	Good tutorial for timer/counter:
		@http://maxembedded.com/2011/06/avr-timers-timer0/
	ATmega2560 runs:
		16MHz clocks
	Timer3/counter3 (16bits) will be chosen with scale of 1024. So 3 second requies total:
		3*16M/1024 = 46875  =  0*2^16(--65536--) + 46875; 



	Using Timer1 Fast PWM Mode
	20ms each cycle in 16MHz using 256 prescaler, needs TOP(1250) count;
*/

#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

//port definition
#define LEDS_PORT PORTC
#define LEDS_DDR DDRC
#define LEDS_PIN PINC

#define BUTTON_DDR DDRA
#define Required_overflow 0
#define Remained_count 46875//56428

volatile uint8_t total_overflow;

//interrupt handlers
ISR(TIMER3_OVF_vect){
	//remember how many interrupt has happened
	total_overflow++;

}




void timer1_init(uint8_t status_pina){
	total_overflow = 0;
	
	TCCR1A |= _BV(COM1A1); //initialize COM1A1 to 1 and COM1A0 to 0 to 
        TCCR1A &= ~(_BV(COM1A0)); //enable OC1A as the output

        //setup timer1 running in fast moodule(1110) (top: ICRn)
        TCCR1A &= ~(_BV(WGM10));
        TCCR1A |= _BV(WGM11);
        TCCR1B |= _BV(WGM12);
        TCCR1B |= _BV(WGM13);


	ICR1 = 1250;//top value
        OCR1A = 0;//this value should change based on the button pressed

        if(status_pina == 0b01111111){
                OCR1A = 77;//1.25ms
        }
        else if(status_pina == 0b101111111){
                OCR1A = 81;
        }
	else if(status_pina == 0b110111111){
                OCR1A = 85;
        }
	else if(status_pina == 0b11101111){
                OCR1A = 89;
        }
	else if(status_pina == 0b11110111){
                OCR1A = 103;
        }
	else if(status_pina == 0b11111011){
                OCR1A = 104;
        }
	else if(status_pina == 0b11111101){
                OCR1A = 107;
        }
	else if(status_pina == 0b11111110){
                OCR1A = 109;// 1.75ms
        }




	//set up timer with scaler of 256
	TCCR1B |= _BV(CS12);
	TCNT1 = 0;
}



void timer3_init(){
	TCCR3B &= ~(_BV(CS32));
	TCCR3B &= ~(_BV(CS30));
	//initialize the counter
	TCNT3 = 0;


	//run in 1024 scale
	TCCR3B |= _BV(CS32);
	TCCR3B |= _BV(CS30);

	TIMSK3 |= _BV(TOIE3);
	sei();
}

//program setup
void setup(){
	LEDS_DDR = 0xff;
	BUTTON_DDR = 0x00;//Read from PORTA
	PORTA = 0xff; // Activate PULL UP resistor
	
	DDRB |= _BV(PB5);//set OC1A as output	
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
			timer1_init(status_pina);    //initialize timer 1;
			timer3_init();   //prepare for the PWM using timer 3;
			
			while(total_overflow < Required_overflow){
			}

			while(TCNT3 <= Remained_count){	
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
			TCNT3 = 0;

		}

	}
	return 0;
}
