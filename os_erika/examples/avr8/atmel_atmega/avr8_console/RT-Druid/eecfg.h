#ifndef RTDH_EECFG_H
#define RTDH_EECFG_H


#define RTDRUID_CONFIGURATOR_NUMBER 1277



/***************************************************************************
 *
 * Common defines ( CPU 0 )
 *
 **************************************************************************/

    /* TASK definition */
    #define EE_MAX_TASK 1
    #define TaskSend 0

    /* MUTEX definition */
    #define EE_MAX_RESOURCE 0U

    /* ALARM definition */
    #define EE_MAX_ALARM 1
    #define AlarmSend 0

    /* COUNTER definition */
    #define EE_MAX_COUNTER 1
    #define myCounter 0

    /* APPMODE definition */
    #define EE_MAX_APPMODE 0U

    /* CPUs */
    #define EE_MAX_CPU 1
    #define EE_CURRENTCPU 0

    /* Number of isr 2 */
    #define EE_MAX_ISR2 0

#ifndef __DISABLE_EEOPT_DEFINES__


/***************************************************************************
 *
 * User options
 *
 **************************************************************************/
#define __LEDS_USED__
#define __ADD_LIBS__
#define __USE_UART__
#define USE_CONSOLE
#define USE_CONSOLE_SERIAL


/***************************************************************************
 *
 * Automatic options
 *
 **************************************************************************/
#define __RTD_CYGWIN__
#define __AVR5__
#define __ATMEGA128__
#define __TIMER0_CLK_DIV32__
#define __TIMER_0_USED__
#define __TIMER1_CLK_DIV256__
#define __TIMER_1_USED__
#define __TIMER2_CLK_DIV64__
#define __TIMER_2_USED__
#define __TIMER3_CLK_DIV64__
#define __TIMER_3_USED__
#define __TIMER_USED__
#define __XBOW_MIB5X0__ 
#define __FP__
#define __MONO__
#define __ALARMS__
#define __FP_NO_RESOURCE__

#endif



#endif

