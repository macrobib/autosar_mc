/*
 * ABS_Wheelspeed.h
 */

#ifndef ABS_WHEELSPEED_H_
#define ABS_WHEELSPEED_H_
#include <math.h>
#define THRESHOLD_VAL = 0.025
double reference_slip = 0.0;

double abs_wheelspeed_bang_bang_controller(double input){
        double operator_val = sin(input);
        double new_val = THRESHOLD_VAL;
        if(operator_val < THRESHOLD_VAL){/*Truncate */
        	new_val = operator_val;
        }
        return new_val;
}

double abs_wheelspeed_hydraulic_lag(double input){

}

double abs_wheelspeed_brake_pressure(double brake_press){

}

double abs_wheelspeed_brake_force_torq(double Bp){

}

double abs_wheelspeed_measure(){

}

double abs_wheelspeed_gain(){

}

double abs_wheelspeed_integrator(){

}

double abs_wheelspeed_calculate(double input){

}

#endif /* ABS_WHEELSPEED_H_ */
