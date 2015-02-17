/*
 * Simple example on how to turn on, turn off, toggle
 * single pins (leds in example) and how to change state
 * of multiple pins at once.
 *
 * This example contains a lot of comments so that you can
 * get hints on how to write C code for AVR.
 * Note also that this file is overly commented and you
 * should not comment every single line on your code.
 *
 * This file goes through the basics and also contains
 * some optimization hints to those who are used to writing C.
 */

/* As you should know, these are the include statements */
#include <inttypes.h> /* definitions for uint8_t and others */
#include <avr/io.h>   /* definitions for all PORT* and other registers. You absolutely will need this one */

/* following line is needed only when _delay_ms is used
 * read the comment about _delay_ms from the main function */
#include <util/delay.h>


/* It is common to write following kind of definitions
 * so when your hardware or wiring changes, you just need to edit these.
 * Of course this isn't the case with this project as you are not allowed
 * to change the hardware.
 * Any case it makes reading the code easier (if you choose good variables)
 */
#define LEDS_PORT PORTC
#define LEDS_DDR  DDRC
#define LEDS_PIN  PINC


/* you should use macros instead of integer literals
 * when addressing pins (even though PC2 is always 2)
 * This is also good in the documentation perspective as
 * we can differentiate between PC2 and PE2
 */
#define BLINK_LED PC2
#define OTHER_LED PC0


/* For setting up the initial values for the registers
 * it is sometimes good to use helper functions (gcc will optimise
 * these function calls away (inlines them) so not overhead is generated)
 * This is very nice at least when your code is in multiple files
 */
void setup_leds(void)
{
	/* Configure the leds port as output
	 * DDR* registers define GPIO pin direction (1 means output and 0 input)
	 * Refer atmega 2560 datasheet for more about this
	 */
	LEDS_DDR = 0xff;
}


/* Remember that in C you need to prototype functions,
 * when they are referenced before defined.
 * It is good practice to prototype all used functions in start of the file
 */
uint8_t rotate_online_led(uint8_t);
void toggle_blink_led(void);


int main(void)
{
	/* In start of the main function you would do
	 * Hardware setup/initialization as main function
	 * is run only once after microcontroller is started
	 */

	setup_leds();

	/* Variables defined here are bit faster than global
	 * variables. Sometimes it's better for the
	 * code readability to us global variables instead.
	 */
	uint8_t state = 0x80;

	for (;;)
	{
		/* The infinite loop of your code
		 * All repeated logic should be here
		 */

		/* Write 1 to leds port register in other leds pin,
		 * this will turn other led on (left most led)
		 */
		LEDS_PORT |= _BV(OTHER_LED);

		/* call helper function to toggle led */
		toggle_blink_led();

		/* call helper function to another task */
		state = rotate_online_led(state);

		/* You should avoid using _delay_ms
		 * For example using it to generate servo PWM
		 * is invalid and wrong solution
		 *
		 * _delay_ms is good to be used for debuging time related
		 * problems, but should be always replaced by some other
		 * solution when the real problem is found.
		 *
		 * This example is another ok purpose for it (as blinkid the led
		 * is only thing we do)
		 */
		_delay_ms(200); /* delay code execution for 200 ms */

		/* Write 0 to leds port register in other leds pin,
		 * this will turn other led off
		 * Notice that we need to "mask wanted pin off", compiler will
		 * translate this into single processor instruction
		 */
		LEDS_PORT &= ~_BV(OTHER_LED);
		_delay_ms(200);
	}

	/* when you exit from the main function, the MCU will enter
	 * an infinite loop (note. the MCU is not rebooted)
	 * Normally you code should never exit the main function.
	 */
	return 0;
}


uint8_t rotate_online_led(uint8_t state)
{
	/* Following commented line would be optimal for this
	 * function, but it would broke toggle_blink_led
	 * so we need to do bit more complex way, but this
	 * shows you bit more what you could do
	 */
	// LEDS_PORT = state;

	/* Read the current port value (this is different than
	 * what you need for reading button state)
	 */
	uint8_t current_value = LEDS_PORT;
	/* mask the pins we control to be off */
	current_value &= 0x0f; /* 0b00001111 */
	/* put the state pin up */
	current_value |= state;
	/* update port register (online led will change after this line) */
	LEDS_PORT = current_value;

	/* Above could be written with just single line of code */
	// LEDS_PORT = (LEDS_PORT & 0x0f) | state;

	/* Update the state byte */
	state >>= 1;
	if (state <= 0x08) /* 0b00001000 */
		state = 0x80;  /* 0b10000000 */
	return state;
}


void toggle_blink_led(void)
{
	/* There is no easy way to pass register to a function
	 * in a way that would be optimal.
	 * When you are passing register to the function,
	 * you are trying to do too generic code for this task.
	 * You should avoid this during this exercise.
	 *
	 * Instead hard code registers into the functions
	 * and use C macros to help change the code.
	 */

	/* Most atmega MCU can toggle output state when 1 is
	 * written to the PIN* register */
	LEDS_PIN |= _BV(BLINK_LED);

	/* _BV is macro defined in avr/io.h
	 *    #define _BV(bit) (1 << (bit))
	 * so above is identical to
	 */
	// LEDS_PIN |= 1 << BLINK_LED;
}