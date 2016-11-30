#ifndef RTDH_EECFG_H
#define RTDH_EECFG_H


#define RTDRUID_CONFIGURATOR_NUMBER 1278



/***************************************************************************
 *
 * Common defines ( CPU 0 )
 *
 **************************************************************************/

    /* TASK definition */
    #define EE_MAX_TASK 2
    #define Task1 0
    #define Task2 1

    /* MUTEX definition */
    #define EE_MAX_RESOURCE 0U

    /* EVENT definition */
    #define ButtonEvent 0x1U
    #define TimerEvent 0x2U

    /* ALARM definition */
    #define EE_MAX_ALARM 0U

    /* SCHEDULING TABLE definition */
    #define EE_MAX_SCHEDULETABLE 2U
    #define SchedTab1 0U
    #define SchedTab2 1U

    /* COUNTER OBJECTS definition */
    #define EE_MAX_COUNTER_OBJECTS (EE_MAX_ALARM + EE_MAX_SCHEDULETABLE)

    /* CPU CLOCK definition */
    #define EE_CPU_CLOCK      200000000U

    /* COUNTER definition */
    #define EE_MAX_COUNTER 1U
    #define system_timer 0U

    /* APPMODE definition */
    #define EE_MAX_APPMODE 1U

    /* CPUs */
    #define EE_MAX_CPU 1
    #define EE_CURRENTCPU 0

    /* Number of isr 2 */
    #define EE_MAX_ISR2   1
    #define EE_MAX_ISR_ID 2

#ifndef __DISABLE_EEOPT_DEFINES__


/***************************************************************************
 *
 * User options
 *
 **************************************************************************/
#define EE_DEBUG
#define __ASSERT__
#define EE_EXECUTE_FROM_RAM
#define EE_SAVE_TEMP_FILES


/***************************************************************************
 *
 * Automatic options
 *
 **************************************************************************/
#define __RTD_CYGWIN__
#define EE_TRIBOARD_TC2X5
#define EE_TRICORE__
#define EE_TC27X__
#define EE_GNU__
#define ENABLE_SYSTEM_TIMER
#define __OO_ORTI_LASTERROR__
#define __OO_ORTI_SERVICETRACE__
#define __OO_ORTI_PRIORITY__
#define __OO_ORTI_RES_LOCKER_TASK__
#define __OO_ORTI_RES_ISLOCKED__
#define __OO_ORTI_STACK__
#define __OO_ORTI_ALARMTIME__
#define __OO_ORTI_RUNNINGISR2__
#define __OO_ECC1__
#define __OO_EXTENDED_STATUS__
#define __OO_HAS_SHUTDOWNHOOK__
#define __MULTI__
#define EE_AS_SCHEDULETABLES__
#define __OO_NO_ALARMS__
#define __OO_NO_RESOURCES__
#define __OO_AUTOSTART_TASK__
#define EE_AS_AUTOSTART_SCHEDULETABLE__
#define __ALLOW_NESTED_IRQ__

#endif

    /* System stack size */
    #define EE_SYS_STACK_SIZE     8192



/***************************************************************************
 *
 * HW counter definition
 *
 **************************************************************************/
#define EE_MAX_COUNTER_HW 1
#define EE_SYSTEM_TIMER   system_timer
#define EE_SYSTEM_TIMER_DEVICE   EE_TC_STM_SR0

#define EE_TC_1_ISR EE_tc_system_timer_handler
#define EE_TC_1_ISR_PRI EE_ISR_PRI_1
#define EE_TC_1_ISR_CAT 2
#define EE_ISR2_ID_EE_tc_system_timer_handler 1

/* Max ISR priority */
#define EE_TC_MAX_ISR_ID     EE_ISR_PRI_1



/***************************************************************************
 *
 * Counter defines
 *
 **************************************************************************/
#define OSMAXALLOWEDVALUE_system_timer 2147483647U
#define OSTICKSPERBASE_system_timer    1U
#define OSMINCYCLE_system_timer        1U

#define OSMAXALLOWEDVALUE 2147483647U
#define OSTICKSPERBASE    1U
#define OSMINCYCLE        1U
#define OSTICKDURATION    1000000U



/***************************************************************************
 *
 * Vector size defines
 *
 **************************************************************************/
    #define EE_ACTION_ROM_SIZE 5
    #define EE_AS_AUTOSTART_SCHEDULE_TABLE_MODE_OSDEFAULTAPPMODE_SIZE 1
    #define EE_COUNTER_HW_ROM_SIZE 1
    #define EE_COUNTER_OBJECTS_ROM_SIZE 2
    #define EE_COUNTER_ROM_SIZE 1
    #define EE_EXPIRY_POINTS_ROM_SIZE 4
    #define EE_OO_AUTOSTART_TASK_MODE_OSDEFAULTAPPMODE_SIZE 1
    #define EE_TC_SYSTEM_TOS_SIZE 2


#endif

