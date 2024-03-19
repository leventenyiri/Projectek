/*
 * functions.h
 *
 *  Created on: Oct 2, 2023
 *      Author: nyiri
 */

#ifndef SRC_FUNCTIONS_H_
#define SRC_FUNCTIONS_H_

SegmentLCD_UpperCharSegments_TypeDef upperCharSegments[SEGMENT_LCD_NUM_OF_UPPER_CHARS];
SegmentLCD_LowerCharSegments_TypeDef lowerCharSegments[SEGMENT_LCD_NUM_OF_LOWER_CHARS];

typedef struct {
	int minidisplay; //selecting one of the 14segment displays
	char segment; //selecting one of the segment of the chosen minidisplay

}position;

typedef enum {
  RIGHT = 1,
  UP = 2,
  LEFT = 3,
  DOWN = 4
}direction; //we will decide which way we are turning by incrementing or decrementing its value

#define BUTTON0 9
#define BUTTON1 10


void display_position(position* active_segments, int length);

void delay(int divider);

void start_init(position* starting_segments, position* starting_food);

position calculate_new_head(direction snake_direction, direction previous_direction , position* snake);

void move(position* snake, int snake_length, position snake_head);

direction update_direction(direction previous_direction, bool left, bool right);

void generate_food(position* food, position* snake);

char convert_int_to_char(int randsegment);

position G_snake_direction(direction snake_direction, direction previous_direction , position* snake);

position M_snake_direction(direction snake_direction, direction previous_direction , position* snake);

position A_snake_direction(direction snake_direction, direction previous_direction , position* snake);

position D_snake_direction(direction snake_direction, direction previous_direction , position* snake);

position F_snake_direction(direction snake_direction, direction previous_direction , position* snake);

position E_snake_direction(direction snake_direction, direction previous_direction , position* snake);

position C_snake_direction(direction snake_direction, direction previous_direction , position *snake);

position B_snake_direction(direction snake_direction, direction previous_direction , position *snake);

bool collision_with_snake(position* snake, int length);

int collision_with_food(position* snake, int snake_length, position* food);

void number_decoder(int length, int display_num);

void display_length(int length);

void blink_dots();

void upperCharSegments_0();

#endif /* SRC_FUNCTIONS_H_ */
