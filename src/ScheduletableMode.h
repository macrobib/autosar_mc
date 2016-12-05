/*
 * ScheduletableMode.h
 */

#ifndef SCHEDULETABLEMODE_H_
#define SCHEDULETABLEMODE_H_
#define EE_MC_VARIABLE short
#define EE_MC_TOLERANCE_LIMIT 1

typedef enum EE_as_enum_activ_crit_{
    EE_AS_LOW_CRIT,
    EE_AS_HIGH_CRIT,
    EE_AS_INVALID_CRIT
}EE_as_enum_activ_crit;

typedef enum EE_as_enum_transition_{
    EE_AS_TO_LOW,
    EE_AS_TO_HIGH,
    EE_AS_TO_INVALID
}EE_as_enum_transition;

typedef enum EE_as_enum_overrun_type_{
	EE_AS_BUDGET_OVERRUN,
	EE_AS_TIMEFRAME_OVERRUN
}EE_as_enum_overrun_type;

typedef enum EE_as_enum_schedule_error_{
	EE_TRANSITION_TO_HI_ERROR,
	EE_TRANISITON_TO_LO_ERROR,
	EE_TRANSITION_ERROR,
	EE_TRANSITION_WARNING
}EE_as_enum_schedule_error;

/**Represents the different level to transition to high criticality.
 * **/
typedef enum EE_as_enum_context_to_high_{
	EE_MC_HI_STAGE_1, /*Low crit overrun, no frame overrun.*/
	EE_MC_HI_STAGE_2, /*Low crit overrun, frame overrun.*/
	EE_MC_HI_STAGE_3, /*High crit overrun, no frame width overrun.*/
	EE_MC_HI_STAGE_4,  /*High crit overrun, frame width overrun. */
	EE_MC_HI_STAGE_INVALID /*Undefined case*/
}EE_as_enum_context_to_high;

/**Represents the different level to transition to low criticality.
 * **/
typedef enum EE_as_enum_context_to_low_{
	EE_MC_LO_STAGE1,  /*AMC Scheduling, stabilization enabled.*/
	EE_MC_LO_STAGE2,  /*AMC Scheduling, stabilization disabled.*/
	EE_MC_LO_STAGE3,   /*OCBP Frame scheduling.*/
	EE_MC_LO_STAGE_INVALID /*Undefined case*/
}EE_as_enum_context_to_low;

/**ACTIVE Schedule table criticality support**/
typedef enum EE_as_enum_high_crit_support_{
	EE_MC_HIGH_CRIT_SUPPORTED,
	EE_MC_HIGH_CRIT_NOT_SUPPORTED
};

/*If stabilization is enabled tolerance value indicates the accepted budget overrun.
 * */
EE_MC_VARIABLE  EE_mc_tolerance = 0;

EE_as_enum_activ_crit EE_as_active_crit = EE_AS_LOW_CRIT;
EE_as_enum_transition EE_as_active_trans = EE_AS_TO_INVALID;


/**Generic function to handle the schedulability error raised.**/
void raise_schedule_error(EE_as_enum_schedule_error err){
	switch(err){
	case EE_TRANSITION_ERROR:
		break;
	case EE_TRANISITON_TO_LO_ERROR:
		break;
	case EE_TRANSITION_TO_HI_ERROR:
		break;
	case default:
		break;
	}
}

#endif /* SCHEDULETABLEMODE_H_ */
