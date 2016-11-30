/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2012  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation, 
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/*
 * Author: 2012,  Giuseppe Serano
 *         2014,  Christoph Kreuzberger
 */
#include "reg_sci.h"
#include "ee_mc_data.h"
#include "ee.h"
#include "ee_irq.h"
#include "sys_pmu.h"
#include <stdio.h>

#define UART scilinREG

#ifdef ENABLE_TIME_MEASUREMENT
/***********************Time measurement Components start ***************************/
volatile unsigned long cycles_PMU_start, cycles_PMU_end, cycles_PMU_measure;
uint8 buffer[20] = {0};
int i_updated = 0;
uint8 SPACE[3] = {' ','\n','\r'};
/*terminal verification data*/
#define  TSIZE2 18
uint8  TEXT2[TSIZE2]= {'M','I','C','R','O','C','O','N','T','R','O','L','L','E','R','S',' ',' '};


/*Initialize PMU measurement units*/
inline void init_time_measurement(){
	  _pmuEnableCountersGlobal_();
	  _pmuSetCountEvent_(pmuCOUNTER0, PMU_CYCLE_COUNT); // PMU_CYCLE_COUNT > PMU_INST_ARCH_EXECUTED
	  _pmuResetCounters_();
}

//#define UART scilinREG
inline void start_timer(){
	cycles_PMU_start = 0;
	cycles_PMU_end = 0;
	_pmuStartCounters_(pmuCOUNTER0);
	cycles_PMU_start = _pmuGetEventCount_(pmuCOUNTER0);
}

inline void stop_timer(){
	unsigned long temp = 0;
	_pmuStopCounters_(pmuCOUNTER0);
	cycles_PMU_end 	 = _pmuGetEventCount_(pmuCOUNTER0);
	cycles_PMU_measure = (cycles_PMU_end - cycles_PMU_start)/180;/*Measure in microseconds*/
	temp = cycles_PMU_measure;
	i_updated = 1;
	sprintf(&buffer[0],"%ld", cycles_PMU_measure);
//	sciSend(UART, TSIZE2, &TEXT2[0]);
}

/*inline void sciDisplayText(sciBASE_t *sci, uint8 *text,uint32 length)
{
	while(length--)
    {
        while ((UART->FLR & 0x4) == 4);  wait until busy
        sciSendByte(UART,*text++);       send out text
    };
}

inline void print_timer(){
	if(i_updated){
	i_updated = 0;
	sprintf(&buffer[0],"%ld", cycles_PMU_measure);
	sciDisplayText(UART, &buffer[0], 20);
	sciDisplayText(UART,&SPACE[0],3);
	}
}*/
/* ****************Time measurement Components End ************************************/
#endif


/* insert a stub for the functions not directly supported by __FP__ */
#if defined(__FP__) || defined(__EDF__)
__INLINE__ void __ALWAYS_INLINE__ DisableAllInterrupts(void)
{
  EE_hal_disableIRQ();
}

__INLINE__ void __ALWAYS_INLINE__ EnableAllInterrupts(void)
{
  EE_hal_enableIRQ();
}

__INLINE__ void __ALWAYS_INLINE__ TerminateTask(void)
{
}

#define OSDEFAULTAPPMODE 1
__INLINE__ void __ALWAYS_INLINE__ StartOS(int i)
{
}
#endif

/* EDF based implementation should provide a HAL Timer functionality*/
#if defined(__EDF__)
EE_TIME EE_Timer_Tick_Counter = 0;

EE_TIME EE_hal_gettime(void){
	return EE_Timer_Tick_Counter;
}
#endif

/* A few counters incremented at each event 
 * (alarm, button press or task activation...)
 */
volatile int timer_fired = 0;
volatile int button_fired = 0;
volatile int task1_fired = 0;
volatile int task2_fired = 0;

/* Let's remember the led status! 
 * Mutual exclusion on this variable is not included in the demo to make it
 * not too complicated; in general shared variables should be protected using
 * GetResource/ReleaseResource calls
 */
volatile EE_UINT8 led_status = 0;


/* Let's declare the tasks identifiers */
DeclareTask(Task1);
DeclareTask(Task2);

/* just a dummy delay */ 
#define ONEMILLION 1000
static void mydelay(void)
{
  int i,j;
  for (i = 0; i < ONEMILLION; i++)
    for (j = 0; j < ONEMILLION; j++)
    {
      ;	/* NOP */
    }
}


/* sets and resets a led configuration passed as parameter, leaving the other
 * bits unchanged
 * 
 * Note: led_blink is called both from Task1 and Task2. To avoid race 
 * conditions, we forced the atomicity of the led manipulation using IRQ
 * enabling/disabling. We did not use Resources in this case because the 
 * critical section is -really- small. An example of critical section using 
 * resources can be found in the osek_resource example.
 */
void led_blink(EE_UINT8 theled)
{
  DisableAllInterrupts();
  EE_LED_On(theled);
  EnableAllInterrupts();

  mydelay();

  DisableAllInterrupts();
  EE_LED_Off(theled);
  EnableAllInterrupts();
}

/*
 * Program the SysTick to raise interrupts
 */
void systick_program(void)
{
  EE_systick_set_period(	/* Set the SysTick period to (1ms @ 10MHz)   */
    MILLISECONDS_TO_TICKS(1, 10000000)
  );
  EE_systick_enable_int();	/* Enable SysTick Interrupts		      */
  EE_systick_start();		/* Start SysTick			      */

}


/* This is an ISR Type 2 which is attached to the SysTick peripheral IRQ pin
 * The ISR simply calls CounterTick to implement the timing reference
 */
ISR2(systick_handler)
  {
  EE_systick_clr_int_flg();
  static int timer_divisor = 0;

  timer_divisor++;
  if (timer_divisor == 4000) {
    timer_divisor = 0;
    timer_fired++;
  }
//  EE_th_notify_next_activation();
}

/* Task1: just call the ChristmasTree */
TASK(Task1)
{
  EE_th_update_task_termination(Task1, 0);
  task1_fired++;
  
  /* First half of the christmas tree */
  led_blink(0);
  led_blink(1);
  led_blink(2);
  
  /* CONFIGURATION 3 and 4: we put an additional Schedule() here! */
#ifdef MYSCHEDULE
  Schedule();
#endif

  /* Second half of the christmas tree */
  led_blink(3);
  led_blink(4);
  led_blink(5);
  
  EE_th_update_task_termination(Task1, 1);
}


/* Task2: Print the counters on the LCD Display */
TASK(Task2)
{
  EE_th_update_task_termination(Task1, 0);
  /* count the number of Task2 activations */
  task2_fired++;
  int i = 0;
  led_blink(6);
  for(i = 0; i<10000; i++);

  /* prints a report
   * Note: after the first printf in main(), then only this task uses printf
   * In this way we avoid raceconditions in the usage of stdout.
   */
  EE_th_update_task_termination(Task1, 1);
}

/*DISPLAY_Clear(Black);
  DISPLAY_SetBackColor(Black);
  DISPLAY_SetTextColor(White);
  DISPLAY_DisplayString(0, 0, "Hardware: TI TMS570");
  DISPLAY_DisplayString(1, 0, "Software: Erika RTOS");
  DISPLAY_SetTextColor(Red);
  DISPLAY_DisplayString(9, 0, "by Chris Kreuzberger");
 * Programs User Buttons to rais interrupts.
 */
void buttons_program(void)
{
  rtiSetPeriod(rtiCOMPARE3, 1000000);
  rtiEnableNotification(rtiNOTIFICATION_COMPARE3);
}
/*
 * User Buttons Interrupts Handler which activates Task2.
 */

ISR2(rtiCompare3Interrupt)
{
  /* Clear Interrupt Sources */
  rtiREG1->INTFLAG = 8U;
  /* count the number of button presses */
  EE_Timer_Tick_Counter++;
  button_fired++;
if (CheckSwitch1() || CheckSwitch2()){
	if(button_fired == 10){
		button_fired = 0;
	  start_timer();
	  ActivateTask(Task2);
	  ActivateTask(Task1);
	  stop_timer();
	  sciSend(UART, 20, &buffer[0]);
	  sciSend(UART, 3, &SPACE[0]);
	}
  }
}


int main()
{ 
  /* MCU Initialization */

  EE_mcu_init();
  _pmuInit_();
  init_time_measurement();
  sciSetBaudrate(UART, 115200U);

//  EE_LED_INITAL(0xFFFFFFFF);
  /* Display Initialization */
  /*DISPLAY_Clear(Black);
  DISPLAY_SetBackColor(Black);
  DISPLAY_SetTextColor(White);
  DISPLAY_DisplayString(0, 0, "Hardware: TI TMS570");
  DISPLAY_DisplayString(1, 0, "Software: Erika RTOS");
  DISPLAY_SetTextColor(Red);
  DISPLAY_DisplayString(9, 0, "by Chris Kreuzberger");*/

  /* Programs SysTick to raise interrupts */
  systick_program();

  /* Programs User Buttons to raise interrupts */
  buttons_program();
  mydelay();
  ActivateTask(Task2);
  ActivateTask(Task1);
  /* let's start the multiprogramming environment...*/
  StartOS(OSDEFAULTAPPMODE);
  sciSend(UART, 20, &TEXT2[0]);

  /* now the background activities: in this case, we do nothing. */
  for (;;)
  {
//	  print_timer();
//	  sciDisplayText(UART,&TEXT2[0],TSIZE2);
    ;	/* NOP */
  }
  
  /* Warning: statement is unreachable */
  /* return 0; */

}
