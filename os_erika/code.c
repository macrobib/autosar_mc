/* Implementation to extend timing protection to include the usage of mixed 
 * criticality in the language 
 * Main functions being a set of tasks with predefined scheduling tables and usage
 * of alternate scheduling tables to switch to during a change of the criticality 
 * Scheduler plugins : EDF-VD and AMC
 * */

#include "mc_data.h"

register int volatile cycle_count; /*A time keeping variable */
TickType volatile g_remaining_budget; /*Scratchpad to store the remaining budget*/



#ifdef __EE_MEMORY_PROTECTION

TASK(TaskPrio1){
    /* Task 1: Main functionalities to be to toggle a set of leds in a predefined manner */
    
}



#endif
