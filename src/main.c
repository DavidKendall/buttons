/*
 * @brief A program for the EA NXP LPC4088QSB to flash LED1, LED2, LED3 and LED4.
 *        LEDs are controlled by the joystick. LEFT -> LED1, DOWN -> LED2,
 *        UP -> LED3, RIGHT -> LED4, CENTER -> All LEDs
 * @author David Kendall
 * @date August 2015
 */

#include <stdint.h>
#include <stdbool.h>
#include <LPC407x_8x_177x_8x.h>

#define LED1PIN    (1UL << 18)
#define LED2PIN    (1UL << 13)
#define LED3PIN    (1UL << 13)
#define LED4PIN    (1UL << 19)

#define JOY_LEFT   (1UL << 0)
#define JOY_DOWN   (1UL << 1)
#define JOY_UP     (1UL << 2)
#define JOY_CENTER (1UL << 3)
#define JOY_RIGHT  (1UL << 4)

bool joyLeftPressed(void);
bool joyDownPressed(void);
bool joyUpPressed(void);
bool joyCenterPressed(void);
bool joyRightPressed(void);
void led1Toggle(void);
void led2Toggle(void);
void led3Toggle(void);
void led4Toggle(void);
void delay(uint32_t ms);


int main() {
	bool flashing1 = false;
	bool flashing2 = false;
	bool flashing3 = false;
	bool flashing4 = false;

	// Configure pins as GPIO
	LPC_IOCON->P0_13 = 0x80; // Ensure digital mode is selected for type 'A' pin
	LPC_IOCON->P1_13 = 0;
	LPC_IOCON->P2_19 = 0;
	LPC_IOCON->P2_10 = 0;
	LPC_IOCON->P5_0 = 0;
	LPC_IOCON->P5_1 = 0;
	LPC_IOCON->P5_2 = 0;
	LPC_IOCON->P5_3 = 0;
	LPC_IOCON->P5_4 = 0;
	
	// Set LED pins as OUTPUT
	LPC_GPIO1->DIR |= LED1PIN;
	LPC_GPIO0->DIR |= LED2PIN;
	LPC_GPIO1->DIR |= LED3PIN;
	LPC_GPIO2->DIR |= LED4PIN;
	
	// Set joystick pins as INPUT
	LPC_GPIO5->DIR &= ~(JOY_LEFT | JOY_DOWN | JOY_UP | JOY_CENTER | JOY_RIGHT);
	
	while (true) {
		if (joyLeftPressed()) {
			while (joyLeftPressed()) {
				/* skip */
			}
		  flashing1 = !flashing1;
		}
		if (joyDownPressed()) {
			while (joyDownPressed()) {
				/* skip */
			}
		  flashing2 = !flashing2;
		}
		if (joyUpPressed()) {
			while (joyUpPressed()) {
				/* skip */
			}
		  flashing3 = !flashing3;
		}
		if (joyRightPressed()) {
			while (joyRightPressed()) {
				/* skip */
			}
		  flashing4 = !flashing4;
		}
		if (joyCenterPressed()) {
			while (joyCenterPressed()) {
				/* skip */
			}
		  flashing1 = !flashing1;
		  flashing2 = !flashing2;
		  flashing3 = !flashing3;
		  flashing4 = !flashing4;
		}
		if (flashing1) {
			led1Toggle();
		}
		if (flashing2) {
			led2Toggle();
		}
		if (flashing3) {
			led3Toggle();
		}
		if (flashing4) {
			led4Toggle();
		}
		if (flashing1 || flashing2 || flashing3 || flashing4) {
			delay(1000);
		}		
	}
}

bool joyLeftPressed() {
	return ((LPC_GPIO5->PIN & JOY_LEFT) ? false : true);
}
bool joyDownPressed() {
	return ((LPC_GPIO5->PIN & JOY_DOWN) ? false : true);
}
bool joyUpPressed() {
	return ((LPC_GPIO5->PIN & JOY_UP) ? false : true);
}
bool joyCenterPressed() {
	return ((LPC_GPIO5->PIN & JOY_CENTER) ? false : true);
}
bool joyRightPressed() {
	return ((LPC_GPIO5->PIN & JOY_RIGHT) ? false : true);
}

void led1Toggle() {
	static bool led1On = false;
	
	if (led1On) {
		LPC_GPIO1->SET = LED1PIN;
		led1On = false;
	} 
	else {
		LPC_GPIO1->CLR = LED1PIN;
		led1On = true;
	}
}

void led2Toggle() {
	static bool led2On = false;
	
	if (led2On) {
		LPC_GPIO0->SET = LED2PIN;
		led2On = false;
	} 
	else {
		LPC_GPIO0->CLR = LED2PIN;
		led2On = true;
	}
}

void led3Toggle() {
	static bool led3On = false;
	
	if (led3On) {
		LPC_GPIO1->SET = LED3PIN;
		led3On = false;
	} 
	else {
		LPC_GPIO1->CLR = LED3PIN;
		led3On = true;
	}
}

void led4Toggle() {
	static bool led4On = false;
	
	if (led4On) {
		LPC_GPIO2->SET = LED4PIN;
		led4On = false;
	} 
	else {
		LPC_GPIO2->CLR = LED4PIN;
		led4On = true;
	}
}


/*
 * @brief Waits approximately for a specified delay period
 * @param ms - specifies a delay period in milliseconds
 * @return - None
 *
 * delay(ms) causes a delay of ms milliseconds by looping repeatedly,
 * so using CPU cycles, e.g. delay(1000) should give approximately
 * a 1 second delay. Note this depends on the CPU clock speed and 
 * gives only an approximate delay. There are better ways of doing
 * this.
 */
void delay(uint32_t ms) {
	volatile uint32_t i;
	volatile uint32_t j;
	
	for (i=ms; i>0; i--) {
		for (j=11850; j>0; j--) {
			/* skip */
		}
	}	
}

