

#ifndef ABS_H_
#define ABS_H_
/***Constant definition for the variables ****/
#define fspeed float
#define fyaw  float
/***Constant definition ends***/


typedef struct _absbrake_wheelspeed_t{
	fspeed angular_speed;
	fyaw   angular_variation;
}absbrake_wheelspeed_t;

#endif /* ABS_H_ */
