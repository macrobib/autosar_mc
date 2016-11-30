

/*Added to extend the timer with logger functionality.
 * */

#include <ee.h>
#include <ee_irq.h>
#include <ee_internal.h>

/*This file is needed only if the System Timer is defined */
#if (defined(ENABLE_SYSTEM_TIMER) && defined(EE_SYSTEM_TIMER_DEVICE) )

/*Legut devices as system timer.*/
#define EE_CORTEX_RX_SYSTICK 1

/*Used for compiler error */
#define PREPROC(s) s

/*System Timer Handler */
ISR(EE_cortex_system_timer_handler)
{
#if defined(__OO_BCC1__) || defined(__OO_BCC2__) || defined(__OO_ECC1__) || \
    defined(__OO_ECC2__) || defined(__AS_SC4__)
    IncrementCounterHardware(EE_SYSTEM_TIMER);
#else
    CounterTick(EE_SYSTEM_TIMER);
#endif
}

/*System Timer Initialization */
void EE_cortex_rx_initialize_system_timer(void){
#if (EE_SYSTEM_TIMER_DEVICE == EE_CORTEX_RX_SYSTICK)
    /*OSTICKDURATION is defined as nanoseconds macro */
    EE_systick_set_period(MICROSECONDS_TO_TICKS(
                (OSTICKDURATION/1000U),
                EE_CPU_CLOCK)
            );
    EE_systick_enable_int();
    EE_systick_start();
#else
#error Unsupported device: PREPROC(EE_SYSTEM_TIMER_DEVICE) as System Timer.!
#endif
}


#endif /*ENABLE_SYSTEM_TIMER*/

