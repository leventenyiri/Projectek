/*
 * DataProcessing.h
 *
 *  Created on: May 10, 2024
 *      Author: nyiri
 */

#ifndef INC_DATAPROCESSING_H_
#define INC_DATAPROCESSING_H_

#include <stdint.h>
#include <math.h>
#define TRUE 1
#define FALSE 0

//extern uint8_t zeroCrossing = 0;
extern uint8_t disp_usable;
extern uint8_t first_positive_velocity_detected;

double updateMeanAndCenterData(double newData);
double centerVelocity(double newData);
double calculateAverageAcceleration(double last_accel, double new_accel);
double updateAndFilterVelocity(double current_vel, double delta_t, double avg_accel, int *samples_collected);
double updateBaseline(double filtered_vel);
void updateVelocityAndDisplacement(double last_vel, double centered_vel, double delta_t, double* current_displacement);
void handleZeroCrossings(double last_vel, double centered_vel, uint8_t* zeroCrossing, double *current_displacement, double* max_displacement);
void update_motion(double new_acceleration, double new_time, double delta_t, uint8_t* zeroCrossing, double* current_displacement, double* max_displacement, double* centered_velocity);
void overflow_check();



#endif /* INC_DATAPROCESSING_H_ */
