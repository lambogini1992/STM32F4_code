/*
 * auto_parking.h
 *
 *  Created on: Aug 12, 2019
 *      Author: Admin
 */

#ifndef _AUTO_PARKING_H_
#define _AUTO_PARKING_H_

#include "stm32f1xx_hal.h"
#include "../stepper_motor_ctrl/stepper_ctrl.h"
#include "../rc522_rfid/rcc522.h"

#define CARD_ID_DATA_LEN		5

typedef struct _node_parking_
{
	uint8_t *card_id;
	bool has_car;
	uint8_t node_id;
	uint64_t step_cl;
	uint64_t step_acl;
	struct _node_parking_ *next;
	struct _node_parking_ *prev;
}NODE_PARKING;

NODE_PARKING *node_1;
NODE_PARKING *node_2;
NODE_PARKING *node_3;
NODE_PARKING *node_4;
NODE_PARKING *node_5;

NODE_PARKING *node_base;

void NODE_init(void);
void NODE_parking(void);

NODE_PARKING *NODE_scan_empty(NODE_PARKING *node_base, uint64_t *step, GPIO_PinState *dir);
NODE_PARKING *NODE_scan_car(NODE_PARKING *node_base, const uint8_t *card_id, uint64_t *step, GPIO_PinState *dir);

void NODE_taking_car_proc(const uint8_t *card_id);
void NODE_parking_car_proc(const uint8_t *card_id);

#endif /* EXTERNAL_LIBRARY_AUTO_PARKING_AUTO_PARKING_H_ */
