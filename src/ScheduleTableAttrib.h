/*Attributes and parameter details for the system and individual schedule tables.
 * */
#include "ee.h"

/*Stack constant initializations.*/
#define STACK_1_SIZE 512
#define EE_STACK_ALIGN 0xFFFFFFF8U
#define EE_STACK_ALIGN_SIZE 8U
#define EE_STACK_FILL_PATTERN 0xA5A5A5A5U

/*Stack fill parameter for memory protection..*/
#define FILL_STACK(stack) \
	= {[0 ... (sizeof(stack)/sizeof(stack[0]) - 1U)] = EE_STACK_FILL_PATTERN}

/*Place stack in the right place section for memory protection and OSEK RUN TIME INTERFACE(ORTI) stack filling.*/
#define EE_STACK_ATTRIB EE_COMPILER_ALIGN(EE_STACK_ALIGN_SIZE)\
		EE_COMPILER_SECTION("ee_kernel_stack")

EE_STACK_T EE_STACK_ATTRIB EE_tc_stack_1[EE_STACK_WLEN(STACK_1_SIZE)] FILL_STACK(EE_tc_stack_1)


/******************************************************************************************************************/
/*						TASK BODY DEFINITIONS
/******************************************************************************************************************/
/**Kernel definition for the application member tasks**/
DeclareTask(Task1);
DeclareTask(Task2);

const EE_THREAD_PTR EE_hal_thread_body[EE_MAX_TASK] = {
		&EE_oo_thread_stub,
		&EE_oo_thread_stub
};

EE_UINT32 EE_terminate_data[EE_MAX_TASK];

/*ip of each thread body (ROM)****/
const EE_THREAD_PTR EE_terminate_real_th_body[EE_MAX_TASK] = {
		&FuncTask1,
		&FuncTask2
};

/*Ready priority of the tasks..*/
const EE_TYPEPRIO EE_th_ready_prio[EE_MAX_TASK] = {
		0x1U,
		0x2U
};

/**Dispatch priority of the tasks**/
const EE_TYPEPRIO EE_th_dispatch_prio[EE_MAX_TASK] = {
		0x1U,
		0x2U
};

/**Thread status storage..**/
EE_TYPESTATUS EE_th_status[EE_MAX_TASK] = {
		SUSPENDED,
		SUSPENDED
};

/**Data structure to store next thread to be executed..**/
EE_TID EE_th_next[EE_MAX_TASK] = {
		EE_NIL,
		EE_NIL
};

EE_TID EE_th_next_hi[EE_MAX_TASK] = {
		EE_NIL,
		EE_NIL
};

/**First stacked task..**/
EE_TID EE_stkfirst[SCHED_TABLE_COUNT] = {
    EE_NIL,
    EE_NIL
};

/**Schedule Table active states**/
EE_TID EE_sched_table_status[SCHED_TABLE_COUNT] = {
    EE_NIL,
    EE_NIL
};

/**System cieling parameter**/
EE_TYPEPRIO EE_sys_ceiling = 0x0000U;

/**Maximum pending activation allowed for a given task.
 * Currently only one job of a task is allowed to be active at a given time.
 ***/
EE_TYPENACT EE_th_rnact[EE_MAX_TASK] = {
		1U,
		1U
};

/**First task in the ready queue...**/
EE_TID EE_rq_first[SCHED_TABLE_COUNT] = {
    EE_NIL,
    EE_NIL
};

/**Support for chained task if allowed..**/
#ifndef __OO_NO_CHAINTASK__
/*The next task to be activated after a chain task..*/
EE_TID EE_th_terminate_nextask[EE_MAX_TASK] = {
		EE_NIL,
		EE_NIL
};


/******************************************************************************************************************/
/*						EVENT HANDLING MECHANISMS
******************************************************************************************************************/

/*Thead event already active*/
EE_TYPE_EVENTMASK EE_th_event_active[EE_MAX_TASK] =
{
		0U,
		0U
};

EE_TYPEVENTMASK EE_th_event_waitmask[EE_MAX_TASK] =
{
		0U,
		0U
};

const EE_TYPEPRIO EE_th_is_extended[EE_MAX_TASK] =
{
		1U,
		0U
};

/******************************************************************************************************************/
/*						COUNTERS
/******************************************************************************************************************/

/*System timer definition*/
const EE_oo_counter_ROM_type EE_counter_ROM[EE_MAX_TASKS] = {
		2147483647U,
		1U,
		1U
};

const EE_oo_counter_RAM_type EE_counter_RAM[EE_MAX_TASKS] = {
		0U,
		(EE_TYPECOUNTEROBJECT)-1
};

/******************************************************************************************************************/
/*						COUNTER OBJECT DEFINITIONS.
/******************************************************************************************************************/
const EE_oo_counter_object_ROM_type EE_oo_counter_object_ROM[EE_COUNTER_OBJECT_ROM_SIZE] = {
		{system_timer, SchedTab1, EE_SCHEDULETABLE},
		{system_timer, SchedTab2, EE_SCHEDULETABLE}
};

EE_oo_counter_object_RAM_type EE_oo_counter_object_RAM[EE_COUNTER_OBJECT_ROM_SIZE];

const EE_oo_action_ROM_type EE_oo_action_ROM[EE_ACTION_ROM_SIZE] = {
		{EE_ACTION_TASK, Task2, 0U, (EE_VOID_CALLBACK)NULL, INVALID_COUNTER},
		{EE_ACTION_EVENT, Task1, ButtonEvent, (EE_VOID_CALLBACK)NULL, INVALID_COUNTER},
		{EE_ACTION_EVENT, Task1, TimerEvent, (EE_VOID_CALLBACK)NULL, INVALID_COUNTER},
		{EE_ACTION_TASK, Task2, 0U, (EE_VOID_CALLBACK)NULL, INVALID_COUNTER},
		{EE_ACTION_TASK, Task2, 0U, (EE_VOID_CALLBACK)NULL, INVALID_COUNTER}
};

const EE_as_Expiry_Point_ROM_type EE_as_Expiry_Point_ROM[EE_EXPIRY_POINTS_ROM_SIZE] =
{
		{100, 0U, 1U, 0U, 0U},
		{300, 2U, 2U, 0U, 0U},
		{50,  3U, 3U, 0U, 0U},
		{200, 4U, 4U, 0U, 0U}
};

/***Schedule table definition***/
const EE_as_Schedule_Table_ROM_type EE_as_Schedule_Table_ROM[EE_MAX_SCHEDULETABLE]={
		{0U, 1U, EE_SCHEDULETABLE_SYNC_NONE, 400, INVALID_SCHEDULETABLE_PRECISION, 0U},
		{2U, 3U, EE_SCHEDULETABLE_SYNC_NONE, 250, INVALID_SCHEDULETABLE_PRECISION, 0U}
};

cost EE_as_Schedule_Table_ROM_type EE_as_Schedule_Table_high_ROM[EE_MAX_SCHEDULETABLE] = {
		{0U, 1U, EE_SCHEDULETABLE_SYNC_NONE, 400, INVALID_SCHEDULETABLE_PRECISION, 0U},
		{0U, 0U, EE_SCHEDULETABLE_SYNC_NONE, -1, INVALID_SCHEDULETABLE_PRECISION, 0U}
};

EE_as_Schedule_Table_RAM_type EE_as_Schedule_Table_RAM[EE_MAX_SCHEDULETABLE] = {
		{SCHEDULETABLE_STOPPED, INVALID_SCHEDULETABLE_POSITION, 0, INVALID_SCHEDULETABLE},
		{SCHEDULETABLE_STOPPED, INVALID_SCHEDULETABLE_POSITION, 0, INVALID_SCHEDULETABLE}
};

/***App Mode***/
EE_TYPEAPPMODE EE_ApplicationMode;

/*** Autostart parameter for tasks. ***/
static const EE_TID EE_oo_autostart_task_mode_OSDEFAULTAPPMODE[EE_OO_AUTOSTART_TASK_MODE_OSDEFAULTAPPMODE_SIZE] = {
		Task1
};

const struct EE_oo_autostart_task_type EE_oo_autostart_task_data[EE_MAX_APPMODE] = {
		{1U, EE_oo_autostart_task_mode_OSDEFAULTAPPMODE}
};


/*** *****************************Autostart parameters for schedule table******************************/
static const EE_as_schedule_table_autostart_data EE_as_autostart_schedule_table_mode_OSDEFAULTAPPMODE[EE_AS_AUTOSTART_SCHEDULE_TABLE_MODE_OSDEFAULTAPPMODE_SIZE] = {
		{SchedTab1, EE_ST_START_ABSOLUTE, 0U}
};

const EE_as_schedule_table_autostart_type EE_as_schedule_table_autostart[EE_MAX_APPMODE] = {
		{1U, EE_as_autostart_schedule_table_mode_OSDEFAULTAPPMODE}
};


/**Definitions of HA, ABS, ASP, ACC.***/
