/*
 * DataProcessing.c
 *
 *  Created on: May 10, 2024
 *      Author: nyiri
 */

#include "DataProcessing.h"

// Update mean and center data dynamically
double updateMeanAndCenterData(double newData) {
	static double runningTotal = 0.0;
	static int count = 0;
	static double currentMean = 0;
    runningTotal += newData;
    count++;
    currentMean = runningTotal / (double)count;
    return newData - currentMean;
}

double calculateAverageAcceleration(double last_accel, double new_accel) {
    return (last_accel + new_accel) / 2.0;
}


double updateAndFilterVelocity(double current_vel, double delta_t, double avg_accel, int *samples_collected) {
    static double filtered_velocity = 0;
    const double alpha = 0.98;

    if (*samples_collected == 0) {
        filtered_velocity = current_vel;
    } else {
        filtered_velocity = alpha * current_vel + (1 - alpha) * filtered_velocity;
    }

    return filtered_velocity;
}


double updateBaseline(double filtered_vel) {
    static double baseline = 0;
    const double beta = 0.02;

    baseline = beta * filtered_vel + (1 - beta) * baseline;
    return baseline;
}


void updateVelocityAndDisplacement(double last_vel, double centered_vel, double delta_t, double* current_displacement) {
    double average_velocity = (last_vel + centered_vel) / 2.0;
    double abs_velocity = (fabs(last_vel) + fabs(centered_vel)) / 2.0;
    *current_displacement += abs_velocity * delta_t;
}


void handleZeroCrossings(double last_vel, double centered_vel, uint8_t* zeroCrossing, double *current_displacement, double* max_displacement) {
    if ((last_vel > 0 && centered_vel < 0) || (last_vel < 0 && centered_vel > 0)) {
        (*zeroCrossing)++;
    }

    if (*zeroCrossing == 2) {
        *max_displacement = *current_displacement;
        *current_displacement = 0;
        *zeroCrossing = 0;
        disp_usable = TRUE;
    }
}


void update_motion(double new_acceleration, double new_time, double delta_t, uint8_t* zeroCrossing, double* current_displacement, double* max_displacement, double* centered_velocity) {
    static int samples_collected = 0;
    const double VELOCITY_THRESHOLD = 10000.0;  // Velocity threshold to start displacement
    static double last_acceleration = 0.0;
    static double last_velocity = 0.0;
    static double current_velocity = 0.0;
    // Calculate average and filtered velocities
    double avg_acceleration = calculateAverageAcceleration(last_acceleration, new_acceleration);
    current_velocity += avg_acceleration * delta_t;
    double filtered_velocity = updateAndFilterVelocity(current_velocity, delta_t, avg_acceleration, &samples_collected);
    double baseline = updateBaseline(filtered_velocity);

    // Center the velocity by subtracting the baseline
    *centered_velocity = filtered_velocity - baseline;

    // Start updating displacement only if the centered velocity exceeds the threshold
    // and it's the first time it's detected
    if (!first_positive_velocity_detected && (*centered_velocity) > VELOCITY_THRESHOLD) {
        first_positive_velocity_detected = TRUE;
        *current_displacement = 0;  // This is needed to make sure the displacement
        //period starts with a positive velocity
    }

    // Only update displacement if the first positive velocity has been detected
    if (first_positive_velocity_detected) {
        updateVelocityAndDisplacement(last_velocity, *centered_velocity, delta_t, current_displacement);
        handleZeroCrossings(last_velocity, *centered_velocity, zeroCrossing, current_displacement, max_displacement);
    }



    // Update last values for the next iteration
    last_acceleration = new_acceleration;
    last_velocity = *centered_velocity;
    //read_idx = (read_idx + 1) % BUFFER_SIZE;
}
/*
void overflow_check(){
	if(write_idx-read_idx >= 100){
		CombineAndSendNEW(0xFFFF,red);
	}
}
*/
