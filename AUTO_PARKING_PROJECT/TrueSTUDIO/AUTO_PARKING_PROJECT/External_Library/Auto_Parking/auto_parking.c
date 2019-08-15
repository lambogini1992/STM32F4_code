/*
 * auto_parking.c
 *
 *  Created on: Aug 12, 2019
 *      Author: Admin
 */

#include "auto_parking.h"

NODE_PARKING *NODE_init_node(uint8_t node_id, uint64_t step_acl, uint64_t step_cl);
void NODE_link(NODE_PARKING *node, NODE_PARKING *next, NODE_PARKING *prev);
void NODE_park_car(NODE_PARKING *node, const uint8_t *card_id);
void NODE_take_car(NODE_PARKING *node, const uint8_t *card_id);

void NODE_init(void)
{
	node_1 = NODE_init_node(1, 200, 200);
	node_2 = NODE_init_node(2, 200, 200);
	node_3 = NODE_init_node(3, 200, 200);
	node_4 = NODE_init_node(4, 200, 200);
	node_5 = NODE_init_node(5, 200, 200);

	NODE_link(node_1, node_2, node_5);
	NODE_link(node_2, node_3, node_1);
	NODE_link(node_3, node_4, node_2);
	NODE_link(node_4, node_5, node_3);
	NODE_link(node_5, node_1, node_4);

	node_base = node_1;
}

NODE_PARKING *NODE_init_node(uint8_t node_id, uint64_t step_acl, uint64_t step_cl)
{
	NODE_PARKING *node;
	node 				= (NODE_PARKING *)malloc(sizeof(NODE_PARKING));
	node->node_id 		= node_id;
	node->has_car 		= false;
	node->step_acl 		= step_acl;
	node->step_cl 		= step_cl;
	node->next 			= NULL;
	node->prev 			= NULL;
	return node;
}

void NODE_link(NODE_PARKING *node, NODE_PARKING *next, NODE_PARKING *prev)
{
	node->next 	= next;
	node->prev	= prev;
}

NODE_PARKING *NODE_scan_empty(NODE_PARKING *node_base, uint64_t *step, GPIO_PinState *dir)
{
	uint64_t count_step_clk;
	uint64_t count_step_aclk;
	uint8_t count_node_clk;
	uint8_t count_node_aclk;
	NODE_PARKING *tmp_node_clk;
	NODE_PARKING *tmp_node_aclk;

	tmp_node_clk 	= node_base;
	count_step_clk 	= 0;
	count_node_clk 	= 0;
	while(true == tmp_node_clk->has_car)
	{
		tmp_node_clk 	= tmp_node_clk->next;
		count_step_clk 	+= tmp_node_clk->step_cl;
		count_node_clk++;
	}

	if(0 == count_node_clk)
	{
		*step 	= 0;
		*dir	= ROTATE_CLOCKWISE;
		return tmp_node_clk;
	}

	tmp_node_aclk 		= node_base;
	count_node_aclk		= 0;
	count_step_aclk		= 0;
	while(true == tmp_node_aclk->has_car)
	{
		tmp_node_aclk 		= tmp_node_aclk->prev;
		count_step_aclk 	+= tmp_node_aclk->step_acl;
		count_node_aclk++;
	}

	if(count_node_aclk > count_node_clk)
	{
		*step 	= count_step_clk;
		*dir	= ROTATE_CLOCKWISE;
		return tmp_node_clk;
	}
	else
	{
		*step 	= count_step_aclk;
		*dir	= ROTATE_ANTI_CLOCKWISE;
		return tmp_node_aclk;
	}
}

NODE_PARKING *NODE_scan_car(NODE_PARKING *node_base, const uint8_t *card_id, uint64_t *step, GPIO_PinState *dir)
{
	uint64_t count_step_clk;
	uint64_t count_step_aclk;
	uint8_t count_node_clk;
	uint8_t count_node_aclk;
	NODE_PARKING *tmp_node_clk;
	NODE_PARKING *tmp_node_aclk;

	tmp_node_clk 	= node_base;
	count_step_clk 	= 0;
	count_node_clk 	= 0;
	while(1)
	{
		if(true ==  tmp_node_clk->has_car)
		{
			if(memcmp(tmp_node_clk->card_id, card_id, CARD_ID_DATA_LEN) == 0)
			{
				break;
			}
		}
		tmp_node_clk 	= tmp_node_clk->next;
		count_step_clk 	+= tmp_node_clk->step_cl;
		count_node_clk++;
	}
//	if(0 == count_node_clk)
//	{
//		*step 	= 0;
//		*dir	= ROTATE_CLOCKWISE;
//		return tmp_node_clk;
//	}

	tmp_node_aclk 		= node_base;
	count_node_aclk		= 0;
	count_step_aclk		= 0;
	while(1)
	{
		if(true ==  tmp_node_aclk->has_car)
		{
			if(memcmp(tmp_node_aclk->card_id, card_id, CARD_ID_DATA_LEN) == 0)
			{
				break;
			}
		}
		tmp_node_aclk 		= tmp_node_aclk->prev;
		count_step_aclk 	+= tmp_node_aclk->step_acl;
		count_node_aclk++;
	}


	if(count_node_aclk > count_node_clk)
	{
		*step 	= count_step_clk;
		*dir	= ROTATE_CLOCKWISE;
		return tmp_node_clk;
	}
	else
	{
		*step 	= count_step_aclk;
		*dir	= ROTATE_ANTI_CLOCKWISE;
		return tmp_node_aclk;
	}
}

void NODE_park_car(NODE_PARKING *node, const uint8_t *card_id)
{
	node->has_car = true;
	node->card_id = (uint8_t *)malloc(CARD_ID_DATA_LEN);

	memcpy(node->card_id, card_id, CARD_ID_DATA_LEN);
}

void NODE_take_car(NODE_PARKING *node, const uint8_t *card_id)
{
	node->has_car = false;
	free(node->card_id);
}

void NODE_parking_car_proc(const uint8_t *card_id)
{
	NODE_PARKING *tmp_node;
	uint64_t count_step;
	GPIO_PinState dir;

//	uint8_t idx;

	tmp_node = node_base;
	count_step = 0;
	dir = GPIO_PIN_RESET;

	node_base = NODE_scan_empty(tmp_node, &count_step, &dir);
	rotate_motor(dir, count_step);
	NODE_park_car(node_base, card_id);
//	if((count_step != 0))
//	{
//		for(idx = 0; idx < 10; idx++)
//		{
//			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
//			HAL_Delay(200);
//		}
//	}
}

void NODE_taking_car_proc(const uint8_t *card_id)
{
	NODE_PARKING *tmp_node;
	uint64_t count_step;
	GPIO_PinState dir;

	tmp_node = node_base;
	count_step = 0;
	dir = GPIO_PIN_RESET;
	node_base = NODE_scan_car(tmp_node, card_id, &count_step, &dir);
	rotate_motor(dir, count_step);
	NODE_take_car(node_base, card_id);
}
