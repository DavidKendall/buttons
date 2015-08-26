/*
 * @brief A program for the EA NXP LPC4088QSB to flash LED1, LED2, LED3 and LED4.
 * @author David Kendall
 * @date July 2015
 */

#include <stdint.h>
#include <stdbool.h>
#include <LPC407x_8x_177x_8x.h>



#define LED1PIN    (1UL << 18)
#define LED2PIN    (1UL << 13)
#define LED3PIN    (1UL << 13)
#define LED4PIN    (1UL << 19)

void delay(uint32_t ms);

int main() {
	LPC_IOCON->P1_18 &= ~0x1FUL;
	LPC_IOCON->P0_13 &= ~0x1FUL;
	LPC_IOCON->P1_13 &= ~0x1FUL;
	LPC_IOCON->P2_19 &= ~0x1FUL;
	LPC_GPIO1->DIR |= LED1PIN;
	LPC_GPIO0->DIR |= LED2PIN;
	LPC_GPIO1->DIR |= LED3PIN;
	LPC_GPIO2->DIR |= LED4PIN;
	while (true) {
		LPC_GPIO1->SET = LED1PIN;
		LPC_GPIO0->SET = LED2PIN;
		LPC_GPIO1->CLR = LED3PIN;
		LPC_GPIO2->CLR = LED4PIN;
		delay(1000);
		LPC_GPIO1->CLR = LED1PIN;
		LPC_GPIO0->CLR = LED2PIN;
		LPC_GPIO1->SET = LED3PIN;
		LPC_GPIO2->SET = LED4PIN;
		delay(1000);
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

