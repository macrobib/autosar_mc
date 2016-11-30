#include "ee.h"



/***************************************************************************
 *
 * Stack definition for TriCore
 *
 **************************************************************************/
    #define STACK_1_SIZE 512 /* size = 512 bytes */

    EE_STACK_T EE_STACK_ATTRIB EE_tc_stack_1[EE_STACK_WLEN(STACK_1_SIZE)] EE_TC_FILL_STACK(EE_tc_stack_1);	/* Task 0 (Task1) */

    const EE_UREG EE_std_thread_tos[EE_MAX_TASK+1] = {
        0U,	/* dummy */
        1U,	/* Task1 */
        0U 	/* Task2 */
    };

    struct EE_TC_TOS EE_tc_system_tos[EE_TC_SYSTEM_TOS_SIZE] = {
        {0, 0U},	/* Task   (dummy), Task 1 (Task2) */
        {EE_STACK_INITP(EE_tc_stack_1), 0U} 	/* Task 0 (Task1) */
    };

    EE_UREG EE_tc_active_tos = 0U; /* dummy */

    EE_tc_task_save_data EE_tc_tasks_RA[EE_MAX_TASK+1];



/***************************************************************************
 *
 * HW counter definition
 *
 **************************************************************************/
    const EE_oo_counter_hw_ROM_type EE_counter_hw_ROM[EE_COUNTER_HW_ROM_SIZE] = {
        {1000U}         /* system_timer */
    };



/***************************************************************************
 *
 * Kernel ( CPU 0 )
 *
 **************************************************************************/
    /* Definition of task's body */
    DeclareTask(Task1);
    DeclareTask(Task2);

    const EE_THREAD_PTR EE_hal_thread_body[EE_MAX_TASK] = {
        &EE_oo_thread_stub,		 /* thread Task1 */
        &EE_oo_thread_stub 		 /* thread Task2 */

    };

    EE_UINT32 EE_terminate_data[EE_MAX_TASK];

    /* ip of each thread body (ROM) */
    const EE_THREAD_PTR EE_terminate_real_th_body[EE_MAX_TASK] = {
        &FuncTask1,
        &FuncTask2
    };
    /* ready priority */
    const EE_TYPEPRIO EE_th_ready_prio[EE_MAX_TASK] = {
        0x1U,		 /* thread Task1 */
        0x2U 		 /* thread Task2 */
    };

    const EE_TYPEPRIO EE_th_dispatch_prio[EE_MAX_TASK] = {
        0x1U,		 /* thread Task1 */
        0x2U 		 /* thread Task2 */
    };

    /* thread status */
    EE_TYPESTATUS EE_th_status[EE_MAX_TASK] = {
        SUSPENDED,
        SUSPENDED
    };

    /* next thread */
    EE_TID EE_th_next[EE_MAX_TASK] = {
        EE_NIL,
        EE_NIL
    };

    /* The first stacked task */
    EE_TID EE_stkfirst = EE_NIL;

    /* system ceiling */
    EE_TYPEPRIO EE_sys_ceiling= 0x0000U;

    /* remaining nact: init= maximum pending activations of a Task */
    /* MUST BE 1 for BCC1 and ECC1 */
    EE_TYPENACT   EE_th_rnact[EE_MAX_TASK] =
        { 1U, 1U};

    /* First task in the ready queue (initvalue = EE_NIL) */
    EE_TID EE_rq_first  = EE_NIL;

    #ifndef __OO_NO_CHAINTASK__
        /* The next task to be activated after a ChainTask. initvalue=all EE_NIL */
        EE_TID EE_th_terminate_nextask[EE_MAX_TASK] = {
            EE_NIL,
            EE_NIL
        };
    #endif



/***************************************************************************
 *
 * Event handling
 *
 **************************************************************************/
    EE_TYPEEVENTMASK EE_th_event_active[EE_MAX_TASK] =
        { 0U, 0U};    /* thread event already active */

    EE_TYPEEVENTMASK EE_th_event_waitmask[EE_MAX_TASK] =
        { 0U, 0U};    /* thread wait mask */

    EE_TYPEBOOL EE_th_waswaiting[EE_MAX_TASK] =
        { 0U, 0U};

    const EE_TYPEPRIO EE_th_is_extended[EE_MAX_TASK] =
        { 1U, 0U};



/***************************************************************************
 *
 * Counters
 *
 **************************************************************************/
    const EE_oo_counter_ROM_type EE_counter_ROM[EE_COUNTER_ROM_SIZE] = {
        {2147483647U, 1U, 1U}         /* system_timer */
    };

    EE_oo_counter_RAM_type       EE_counter_RAM[EE_MAX_COUNTER] = {
        {0U, (EE_TYPECOUNTEROBJECT)-1}
    };


/***************************************************************************
 *
 * Counter Objects
 *
 **************************************************************************/
#if 0
/** These data structures represent a generic counter object. Object of this
    kind will build a counter's expire list */
typedef struct {
  /** The counter this counter is linked to */
  CounterType           c;
  /** ID specialized Id (In Alarm or Schedule Tables List) */
  CounterObjectType     spec_id;
  /** Which kind of Counter Object is this */
  CounterObjectKindType kind;
} EE_oo_counter_object_ROM_type;
#endif /* Comment */

  const EE_oo_counter_object_ROM_type EE_oo_counter_object_ROM[EE_COUNTER_OBJECTS_ROM_SIZE] = {
    {system_timer, SchedTab1, EE_SCHEDULETABLE},
    {system_timer, SchedTab2, EE_SCHEDULETABLE}
  };

  EE_oo_counter_object_RAM_type EE_oo_counter_object_RAM[EE_COUNTER_OBJECTS_ROM_SIZE];

#if 0
/** This data structure represent an counter object action */
typedef struct {
  ActionKindType    action_kind;
  TaskType          TaskID;
#if defined(__OO_ECC1__) || defined(__OO_ECC2__)
  EE_TYPEEVENTMASK  Mask;
#endif
  EE_VOID_CALLBACK  f;
    /* Counter to increment when the alarm expire.*/
  CounterType       inccount;
} EE_oo_action_ROM_type;
#endif /* Comment */


  const EE_oo_action_ROM_type   EE_oo_action_ROM[EE_ACTION_ROM_SIZE] = {
    {EE_ACTION_TASK, Task2, 0U, (EE_VOID_CALLBACK)NULL, INVALID_COUNTER },
    {EE_ACTION_EVENT, Task1, ButtonEvent, (EE_VOID_CALLBACK)NULL, INVALID_COUNTER },
    {EE_ACTION_EVENT, Task1, TimerEvent, (EE_VOID_CALLBACK)NULL, INVALID_COUNTER },
    {EE_ACTION_TASK, Task2, 0U, (EE_VOID_CALLBACK)NULL, INVALID_COUNTER },
    {EE_ACTION_TASK, Task2, 0U, (EE_VOID_CALLBACK)NULL, INVALID_COUNTER }
  };

#if 0
/** @typedef Structures that hold the information related to an expiry point */
typedef struct {
  /** Expiry point offset in its own schedule table */
  TickType                offset;
  /** Index of the first expiry point's action */
  ActionType              actions_first;
  /** Index of the last expiry point's action */
  ActionType              actions_last;
  /** Maximum value that can be subtracted from the expiry offset */
  TickType                max_shorten;
  /** Maximum value that can be added to the expiry point offset */
  TickType                max_lengthen;
} EE_as_Expiry_Point_ROM_type;
#endif /* Comment */

const EE_as_Expiry_Point_ROM_type EE_as_Expiry_Point_ROM[EE_EXPIRY_POINTS_ROM_SIZE] =
  {
    { 100, 0U, 1U, 0U, 0U },
    { 300, 2U, 2U, 0U, 0U },
    { 50,  3U, 3U, 0U, 0U },
    { 200, 4U, 4U, 0U, 0U }
  };

#if 0
/**
 * @typedef EE_as_Schedule_Table_ROM_type
 *
 * This is the data structure used to describe the constant part of a
 * schedule table. */
typedef struct {
  /** Index of the first schedule table's expiry point. */
  ExpiryPointType               expiry_point_first;
  /** Index of the last schedule table's expiry point. */
  ExpiryPointType               expiry_point_last;
  /** Schedule table synchronization strategy */
  SynchStrategyType             sync_strategy;
  /** The length of the schedule table in ticks */
  TickType                      duration;
  /** Minimum deviation from synchronization source to be synchronized */
  TickType                      precision;
  /** TRUE if the schedule table shall be repeated after the last expiry point,
      FALSE if the schedule table is single-shot */
  EE_TYPEBOOL                   repeated;
} EE_as_Schedule_Table_ROM_type;
#endif /* Comment */

const EE_as_Schedule_Table_ROM_type EE_as_Schedule_Table_ROM[EE_MAX_SCHEDULETABLE] = {
  { 0U, 1U, EE_SCHEDTABLE_SYNC_NONE, 400 /* Chosen by me it could be 300 at least */ ,INVALID_SCHEDULETABLE_PRECISION, 0U },
  { 2U, 3U, EE_SCHEDTABLE_SYNC_NONE, 250 /* Chosen by me it could be 200 at least */ ,INVALID_SCHEDULETABLE_PRECISION, 0U }
};

#if 0 
/**
 * @typedef EE_as_Schedule_Table_RAM_type
 *
 * Data structure to store variable informations about a schedule table.
 */
typedef struct {
  /** Schedule Table current status */
  ScheduleTableStatusType status;
  /** Expiry point to be processed in the schedule table */
  EE_UREG                 position;
  /** Deviation of the schedule table from synchronization */
  TickType                deviation;
  /** ID of next schedule table to be started */
  ScheduleTableType       next_table;
} EE_as_Schedule_Table_RAM_type;
#endif /* Comment */

EE_as_Schedule_Table_RAM_type EE_as_Schedule_Table_RAM[EE_MAX_SCHEDULETABLE]  = {
  { SCHEDULETABLE_STOPPED, INVALID_SCHEDULETABLE_POSITION, 0, INVALID_SCHEDULETABLE},
  { SCHEDULETABLE_STOPPED, INVALID_SCHEDULETABLE_POSITION, 0, INVALID_SCHEDULETABLE}
};


/***************************************************************************
 *
 * AppMode
 *
 **************************************************************************/
    EE_TYPEAPPMODE EE_ApplicationMode;


/***************************************************************************
 *
 * Auto Start (TASK)
 *
 **************************************************************************/
    static const EE_TID EE_oo_autostart_task_mode_OSDEFAULTAPPMODE[EE_OO_AUTOSTART_TASK_MODE_OSDEFAULTAPPMODE_SIZE] = 
        { Task1 };

    const struct EE_oo_autostart_task_type EE_oo_autostart_task_data[EE_MAX_APPMODE] = {
        { 1U, EE_oo_autostart_task_mode_OSDEFAULTAPPMODE}
    };


/***************************************************************************
 *
 * Auto Start (SCHEDULE TABLE)
 *
 **************************************************************************/
    static const EE_as_schedule_table_autostart_data EE_as_autostart_schedule_table_mode_OSDEFAULTAPPMODE[EE_AS_AUTOSTART_SCHEDULE_TABLE_MODE_OSDEFAULTAPPMODE_SIZE] = 
        { { SchedTab1, EE_ST_START_ABSOLUTE, 0U} };

    const EE_as_schedule_table_autostart_type EE_as_schedule_table_autostart[EE_MAX_APPMODE] = {
        { 1U, EE_as_autostart_schedule_table_mode_OSDEFAULTAPPMODE}
    };

