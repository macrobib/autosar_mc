/*Task definition to two different tables to be used.*/
#include "ScheduletableMode.h"
#include "ee_as_timing_prot.h"

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
    switch(context){
        case stage_1:
            {
                handle_stage_1_change(void);
            }
            break;
        case stage_2:
            {
                handle_stage_2_change(void);
            }
            break;
        case stage_3:
            {
                handle_stage_3_change(void);
            }
        case stage_4:
            {
                handle_stage_4_change(void);
            }
        case default:
            raise_schedule_error();
    }
}

/*Criticality change initiated, frame being low critical.*/
static void handle_stage_1_change(void){

}

/*Criticality change initiated, frame being high critical*/
static void handle_stage_2_change(void){

}
/**/
static void handle_stage_3_change(void){

}

/***/
static void handle_stage_4_change(void){

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

}

static void lower_criticality_amc_stabilize_disable(void){

}

static void lower_criticality_amc_stabilize_enable(void){

}

static void lower_criticality_ocbp(void){

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
