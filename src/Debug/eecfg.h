#ifndef EECFG_H
#define EECFG_H


#define RTDRUID_CONFIGURATOR_NUMBER 1278



    
    #define EE_MAX_TASK 2
    #define Task1 0
    #define Task2 1

    
    #define EE_MAX_RESOURCE 0U

    
    #define ButtonEvent 0x1U
    #define TimerEvent 0x2U

    
    #define EE_MAX_ALARM 0U

    
    #define EE_MAX_SCHEDULETABLE 2U
    #define SchedTab1 0U
    #define SchedTab2 1U

    
    #define EE_MAX_COUNTER_OBJECTS (EE_MAX_ALARM + EE_MAX_SCHEDULETABLE)

    
    #define EE_MAX_COUNTER 1U
    #define system_timer 0U

    
    #define EE_MAX_APPMODE 1U

    
    #define EE_MAX_CPU 1
    #define EE_CURRENTCPU 0

    
    #define EE_MAX_ISR2   0
    #define EE_MAX_ISR_ID 0

#ifndef __DISABLE_EEOPT_DEFINES__

#define __USE_SYSTICK__
#define __TI_DRIVER_LIB__
#define __ALLOW_NESTED_IRQ__
#define __USE_GIO__
#define __USE_LEDS__
#define __USE_HET__
#define __USE_SCI__
#define __CORTEX_RX__

#define __RTD_LINUX__

#endif



#endif

