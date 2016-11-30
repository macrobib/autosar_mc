/** 
* @file uwl_timer_dspic30.c
* @brief Timer Implementation for dsPIC33
* @author Christian Nastasi 2009
* @author Gianluca Franchino 2012
* @version 0.1
* @date 2009-06-22
*/
#include <hal/iedf_timer_dspic30.h>

static void (* volatile isr_callback)(void) = NULL;

int8_t iedf_timer_init(uint32_t period, uint32_t fcy) 
{
	uint32_t pr;

	IEDF_TIMER_INTERRUPT_ENABLE = 0;
	IEDF_TIMER_REG_CON = 0;
	if (fcy / 1000) {
		fcy = fcy / 1000;	/* Represent the frquency in 10^6 */
	} else if (period / 1000) {
		period = period / 1000; /* Represent the period in 10^-3 */
	} else if ((fcy / 100) && (period / 10)) {
		fcy = fcy / 100;	/* Represent the frquency in 10^5 */
		period = period / 10; 	/* Represent the period in 10^-5 */
	} else if ((fcy / 10) && (period / 100)) {
		fcy = fcy / 10;		/* Represent the frquency in 10^4 */
		period = period / 100; 	/* Represent the period in 10^-4 */
	} else {
		return -1;		/* Unable to represent!*/
	}
	pr = period * fcy;
	if (pr <= 0xFFFF) {
		IEDF_TIMER_REG_PERIOD = pr;
	} else if ((pr / 8) <= 0xFFFF) {
		IEDF_TIMER_REG_PERIOD = pr / 8;
		IEDF_TIMER_REG_CONbits.TCKPS = 1;
	} else if ((pr / 64) <= 0xFFFF) {
		IEDF_TIMER_REG_PERIOD = pr / 64;
		IEDF_TIMER_REG_CONbits.TCKPS = 2;
	} else if ((pr / 256) <= 0xFFFF) {
		IEDF_TIMER_REG_PERIOD = pr / 256;
		IEDF_TIMER_REG_CONbits.TCKPS = 3;
	} else {
		return -2;		/* Unable to have this period! */
	}
	IEDF_TIMER_INTERRUPT_PRIORITY = 5;
	IEDF_TIMER_INTERRUPT_FLAG = 0;
	IEDF_TIMER_REG_TMR = 0;
	return 1;
}

void iedf_timer_set_isr_callback(void (*func)(void))
{
	isr_callback = func;
} 

COMPILER_ISR(IEDF_TIMER_INTERRUPT_NAME) 
{
	IEDF_TIMER_INTERRUPT_FLAG = 0;
	if (isr_callback != NULL) 
		isr_callback();
}

