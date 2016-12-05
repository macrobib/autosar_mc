/*Task definition to two different tables to be used.*/
#include "ScheduletableMode.h"
#include "ee_as_timing_prot.h"

/*Determine the high critical transitiion context*/
static EE_as_enum_context_to_high check_hi_transition_context(void){
	EE_as_enum_context_to_high hi_context = EE_MC_HI_STAGE_INVALID;
	return hi_context;
}

/*Determine the low critical transition context*/
static EE_as_enum_context_to_low check_lo_transition_context(void){
	EE_as_enum_context_to_low lo_context = EE_MC_LO_STAGE_INVALID;
	return lo_context;
}

static void update_schedule_table_RAM(){
	if(EE_as_active_sched_table == EE_MC_HIGH_CRIT_SUPPORTED){
		/*Update the schedule table next expiry point*/

	}
}

/*Low crit overrun, no frame overrun.*/
static void handle_stage_1_change(void){

}

/*High crit overrun, no frame width overrun.*/
static void handle_stage_2_change(void){

}
/*High crit overrun, frame width overrun. */
static void handle_stage_3_change(void){

}

/*AMC Scheduling, stabilization enabled.*/
static void handle_stage_4_change(void){

}

/*AMC Scheduling, stabilization disabled.*/
static void lower_criticality_amc_tolerance_disabled(void){

}

/*AMC Scheduling, stabilization enabled.*/
static void lower_criticality_amc_tolerance_enabled(void){

}

/*OCBP Frame scheduling.*/
static void lower_criticality_ocbp(void){

}

/**
 * Summary of tasks:
 * 1. Check if the frame being executed is a low criticality frame.
 * 2. If its a low criticality frame and the frame edges are not triggered, continue execution by dropping current low crits.
 * 3. If dropping the low crit tasks, initiate transition hook to do cleanup and adjustments if any.
 * 4.1 If the task is a high criticality frame,then first initiate the transition hook to do cleanup.
 * 4.2 Switch to shadow table which provides increased running time to frame.
 * 4.3 If the high criticality is triggered beyond the width of the initial frame, then transition next frames to high crit.
 * 4.4 If the next frame to run is low criticality frame, switch it to idle run.
 * **/
void EE_as_mc_raise_criticality(void){

	EE_as_enum_context_to_high context = check_hi_transition_context();
	EE_as_active_trans = EE_AS_TO_HIGH;

	/*If with in tolerance limit, increment the tolerance counter and exit.*/
	if(EE_mc_tolerance < EE_MC_TOLERANCE_LIMIT){
		EE_mc_tolerance += 1;
		return;
	}

	/*If a repeat transition has been triggered, log it and exit.*/
	if(EE_as_active_trans == EE_AS_TO_HIGH){
		raise_schedule_error(EE_TRANSITION_WARNING);
		return;
	}
    switch(context){
        case EE_MC_HI_STAGE_1:
            {
                handle_stage_1_change();
            }
            break;
        case EE_MC_HI_STAGE_2:
            {
                handle_stage_2_change();
            }
            break;
        case EE_MC_HI_STAGE_3:
            {
                handle_stage_3_change();
            }
            break;
        case EE_MC_HI_STAGE_4:
            {
                handle_stage_4_change();
            }
        case default:
            raise_schedule_error(EE_TRANSITION_TO_HI_ERROR);
            break;
    }
}


/**Summary of tasks:
 * 1. Lowering of criticality based on multiple knobs.
 * 2. If the AMC is active and stabilization of lower criticality is enabled, scheduler is marked to lower criticality
 *    when the active background lower criticality frame completes within its frame width.
 * 3. If the stabilization is disabled, and idle instance is hit, the next immediate schedule table boundary is marked for
 *    lower criticality.
 * 4. If OCBP is employed to extend the frame width, if idle instance is hit and tolerance is hit, next immediate frame in
 *    queue will be started in lower criticality.
 * **/
void EE_as_mc_lower_criticality(void){

	EE_as_enum_context_to_low context =  check_lo_transition_context();
	if(EE_as_active_trans == EE_AS_TO_LOW){
		raise_schedule_error(EE_TRANSITION_WARNING);
		return;
	}
	EE_as_active_trans = EE_AS_TO_LOW;
	switch(context){
	case EE_MC_LO_STAGE1:
		lower_criticality_amc_tolerance_disabled();
		break;
	case EE_MC_LO_STAGE2:
		lower_criticality_amc_tolerance_enabled();
		break;
	case EE_MC_LO_STAGE3:
		lower_criticality_ocbp();
		break;
	case default:
		raise_schedule_error(EE_TRANISITON_TO_LO_ERROR);
	}
}


void EE_as_mc_handle_overrun(EE_as_enum_overrun_type overrun){

	switch(overrun){
	case EE_AS_BUDGET_OVERRUN:
		break;
	case EE_AS_TIMEFRAME_OVERRUN:
		EE_as_mc_raise_criticality();
		break;
	case default:
		raise_schedule_error(EE_TRANSITION_ERROR):
	}

}

/*****************************
 * BSW Application definition.
 * ***************************/

/*Definition of ACC Application*/
void SWcApplication1Definition(){

}

/*Definition of ASC Application*/
void SWcApplication2Definition(){

}

/*Definition of HA Application*/
void SWcApplication3Definition(){

}

/*Definition of ABS Application*/
void SWcApplication4Definition(){

}


void EE_as_mc_timing_monitor_handler(){

}
