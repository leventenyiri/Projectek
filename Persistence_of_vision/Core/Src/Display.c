/*
 * Display.c
 *
 *  Created on: May 11, 2024
 *      Author: nyiri
 */

#include "Display.h"

void OutputEnable() {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET); // Set PB2 low to enable output
}

void OutputDisable() {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET); // Set PB2 high to disable output
}

void LatchEnable() {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);   // Set PB1 high
}

void LatchDisable() {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
}


void SendLEDData(uint8_t *data) {
	LatchDisable();
	for (int i = 5; i >= 0; i--) {  // Loop through data array backward
		HAL_SPI_Transmit(&hspi2, &data[i], 1, 100);  // Send 1 byte per driver
	}
	LatchEnable();
}

void CombineLEDData(uint8_t *result, uint8_t ledIdx) {

	for (int j = 0; j < 6; j++) {   // Each LED configuration is 6 bytes
		result[j] |= LED_ARRAY[ledIdx][j];
	}

}

void ShiftLEDData(uint8_t *result, uint8_t ledIdx) {

	for (int j = 0; j < 6; j++) {
		result[j] += LED_ARRAY[ledIdx][j];
	}

}

void CombineAndSendNEW(uint16_t ledMask,uint8_t color) {


	//if the value of a variable is 1, concatenate that LED into the sum
	char a = (ledMask & 0b1000000000000000) >> 15;
	char b = (ledMask & 0b0100000000000000) >> 14;
	char c = (ledMask & 0b0010000000000000) >> 13;
	char d = (ledMask & 0b0001000000000000) >> 12;
	char e = (ledMask & 0b0000100000000000) >> 11;
	char f = (ledMask & 0b0000010000000000) >> 10;
	char g = (ledMask & 0b0000001000000000) >> 9;
	char h = (ledMask & 0b0000000100000000) >> 8;
	char i = (ledMask & 0b0000000010000000) >> 7;
	char j = (ledMask & 0b0000000001000000) >> 6;
	char k = (ledMask & 0b0000000000100000) >> 5;
	char l = (ledMask & 0b0000000000010000) >> 4;
	char m = (ledMask & 0b0000000000001000) >> 3;
	char n = (ledMask & 0b0000000000000100) >> 2;
	char o = (ledMask & 0b0000000000000010) >> 1;
	char p = (ledMask & 0b0000000000000001);

	uint8_t LED[6] = { 0 };
/*
	if(color == red){

		for (int j = 0; j < 6; j++) {   // Each LED configuration is 6 bytes
				LED[j] |= 1;
			}
	}

	if(color == green){
		CombineLEDData(LED,green);
	}
*/

	if (a) {
		CombineLEDData(LED, 0);
	}
	if (b) {
		CombineLEDData(LED, 3);
	}
	if (c) {
		CombineLEDData(LED, 6);
	}
	if (d) {
		CombineLEDData(LED, 9);
	}
	if (e) {
		CombineLEDData(LED, 12);
	}
	if (f) {
		CombineLEDData(LED, 15);
	}
	if (g) {
		CombineLEDData(LED, 18);
	}
	if (h) {
		CombineLEDData(LED, 21);
	}
	if (i) {
		CombineLEDData(LED, 24);
	}
	if (j) {
		CombineLEDData(LED, 27);
	}
	if (k) {
		CombineLEDData(LED, 30);
	}
	if (l) {
		CombineLEDData(LED, 33);
	}
	if (m) {
		CombineLEDData(LED, 36);
	}
	if (n) {
		CombineLEDData(LED, 39);
	}
	if (o) {
		CombineLEDData(LED, 42);
	}
	if (p) {
		CombineLEDData(LED, 45);
	}

	SendLEDData(LED);

}

uint8_t calculateDisplayIndex(double displacement, double max_displacement, double* start_point, uint8_t last_direction) {
    double k = max_displacement / 154.0; // Total range divided into 90 segments (77 each way)
    uint8_t range_index;

    // Calculate relative displacement from the current start point
    double relative_displacement = displacement - *start_point;

    if (last_direction == 0) { // Forward motion
        range_index = (int)(relative_displacement / k);
    } else { // Backward motion
        range_index = 77 - (int)(relative_displacement / k);  // Reverse index for backward motion
    }

    // Clamping the range index to allowed values
    if (range_index < 0) range_index = 0;
    if (range_index > 77) range_index = 77;  // Clamp to max index for 45 segments

    return range_index;
}

void sendDisplayData(uint16_t (*ASCII)[11], int index) {
    int disp_array_idx = index / 11;
    int send_index = index % 11;

    CombineAndSendNEW(ASCII[disp_array_idx][send_index], red);

}

void Display(uint16_t (*ASCII)[11], double max_displacement, double centered_velocity, double current_displacement, double* start_point) {
    // Check and handle velocity zero crossing
	static uint8_t last_direction = 0;
	uint8_t range_index;
    uint8_t current_direction = (centered_velocity > 0) ? 0 : 1;  // 0 for positive, 1 for negative
    if (current_direction != last_direction) {
        *start_point = current_displacement;
        last_direction = current_direction;
    }

    // Calculate the index for display based on the updated start point and current displacement
    range_index = calculateDisplayIndex(current_displacement, max_displacement, start_point, last_direction);

    // Send the character data corresponding to the calculated index to the display
    sendDisplayData(ASCII, range_index);

}
