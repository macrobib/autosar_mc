/*
 * ee_mc_data.h
 *
 *
 */

#ifndef EE_MC_DATA_H_
#define EE_MC_DATA_H_
#include "ee.h"
#include "eecfg.h"
#define __MC__
#define ENABLE_TIME_MEASUREMENT
#define EE_TOTAL_CRIT 2

#if defined(__MC__)||defined(__EDF__)
#ifndef EE_TIME
#define EE_TIME EE_UINT32
#endif

#ifndef EE_STIME
#define EE_STIME EE_INT32
#endif
extern EE_TIME EE_hal_gettime(void);
#endif

#if defined(__MC__)
/*Paramter definition of the task structure*/
struct eeMCStruct{
	int taskid;
	int priority;
	int active_budget;
	int budget_low;
	int budget_high;
	int period;
	int deadline;
};

struct eeMCRelStruct{
	EE_TID taskid;
	int status;
};

typedef struct eeMCStruct EE_MC_Struct;

extern EE_MC_Struct EE_th_sched_params[EE_MAX_TASK];
extern EE_TIME EE_MC_Next_Activation;

/*Scratchpad to do the sorting during criticality change*/
extern EE_TID EE_th_scratchpad[EE_MAX_TASK];
extern inline void rearm_budget_timer(uint32 budget);
/*Probe for current system criticality*/
extern short EE_mc_get_system_criticality(void);
/*Set the system wide criticality value*/
extern void EE_mc_set_system_criticality(short criticality);
/*Wait for the next immediate activation and call schedule*/
extern short EE_mc_check_task_termination(EE_TID tid);

/*Update the termination status*/
extern void EE_mc_update_task_termination(EE_TID tid, short status);
#endif


#endif /* EE_MC_DATA_H_ */
