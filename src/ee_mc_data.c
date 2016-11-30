/*
 * ee_mc_data.c
 * This class provides the basic functionality of defining and handling the MC functionality.
 *
 *  */
#include "ee_mc_data.h"

/*System wide criticality value: Currently two criticality levels supported*/
static short EE_MC_Current_Criticality = 0; /*Initalized to low criticality*/

/*Next activation time*/
EE_TIME EE_MC_Next_Activation = 0;


#define EE_MC_PARAM_Count (5)

/*Sample input for MC Scheduling
 * TODO: Integration of the data array definition from
 * the OIL parser.
 * TODO: Extending the OIL parameter values to handle MC definition
 * */
int data[EE_MAX_TASK][EE_MC_PARAM_Count] = {
		{1,2,5,8,1},{2,4,10,16,2}
};

short task_termination_status[EE_MAX_TASK] = {1};

/*Scratchpad memory to do the sorting during criticality change*/
EE_TID EE_th_scratchpad[EE_MAX_TASK] = {EE_th_ready_prio -1 };


/*parameter storage structure*/
EE_MC_Struct EE_th_sched_params[EE_MAX_TASK];

/*Populate the storage structure with task params
 * TODO: Need to interface xml based generation of the table.
 * */
void EE_init_task_table(void){
	int i = 0;
	int j = 0;
	for(i=0; i< EE_MAX_TASK; i++){
		EE_th_sched_params[i].budget_low    = data[i][0];
		EE_th_sched_params[i].budget_high   = data[i][1];
#ifdef IMPLICIT_TASKS
		EE_th_sched_params[i].deadline = data[i][2];
		EE_th_sched_params[i].period = data[i][2];
#else
		EE_th_sched_params[i].deadline  = data[i][2];
		EE_th_sched_params[i].period = data[i][3];
#endif
		for(j=0; j<EE_TOTAL_CRIT; j++){
			EE_th_sched_params[i].priority = data[i][4];
		}
	}
}

short EE_th_get_system_criticality(void){
	return EE_MC_Current_Criticality;
}

void EE_th_set_system_criticality(short criticality){
	EE_MC_Current_Criticality = criticality;
}

/*Task will update the termination bitmap on exit*/
short EE_th_check_task_termination(EE_TID tid)
{
	short ee_status = -1;
	if((tid >= 0)&&(tid < EE_MAX_TASK))
			ee_status = task_termination_status[tid];

	return ee_status;
}

/*Update task termination flag, set to 1 on termination and 0 on run*/
void EE_th_update_task_termination(EE_TID tid, short status)
{
	if((tid >= 0)&&(tid < EE_MAX_TASK))
		task_termination_status[tid] = status;
}
