/*
 * auto_parking.c
 *
 *  Created on: Aug 12, 2019
 *      Author: Admin
 */

#include "auto_parking.h"

void NODE_init_node(NODE_PARKING *node, uint8_t node_id);
void NODE_link(NODE_PARKING *node, NODE_PARKING *next, NODE_PARKING *prev);

void NODE_init(void)
{
	NODE_init_node(&node_1, 1);
	NODE_init_node(&node_2, 2);
	NODE_init_node(&node_3, 3);
	NODE_init_node(&node_4, 4);
	NODE_init_node(&node_5, 5);

	NODE_link(&node_1, &node_2, &node_5);
	NODE_link(&node_2, &node_3, &node_1);
	NODE_link(&node_3, &node_4, &node_2);
	NODE_link(&node_4, &node_5, &node_3);
	NODE_link(&node_5, &node_1, &node_4);
}

void NODE_init_node(NODE_PARKING *node, uint8_t node_id)
{
	node->node_id = node_id;
	memset(node->card_id, 0, 5);
	node->has_car = false;
	node->step_acl = node->step_cl = 0;
	node->next = node->prev = NULL;
}

void NODE_link(NODE_PARKING *node, NODE_PARKING *next, NODE_PARKING *prev)
{
	node->next 	= next;
	node->prev	= prev;
}

NODE_PARKING *NODE_scan_empty(NODE_PARKING *node_base, uint32_t *step, GPIO_PinState *dir)
{
	uint32_t count_step_clk;
	uint32_t count_step_aclk;
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
		*step 	= count_node_clk;
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

NODE_PARKING *NODE_scan_car(NODE_PARKING *node_base, const char *card_id, uint32_t *step, GPIO_PinState *dir)
{
	uint32_t count_step_clk;
	uint32_t count_step_aclk;
	uint8_t count_node_clk;
	uint8_t count_node_aclk;
	NODE_PARKING *tmp_node_clk;
	NODE_PARKING *tmp_node_aclk;

	tmp_node_clk 	= node_base;
	count_step_clk 	= 0;
	count_node_clk 	= 0;
	while(node_base == tmp_node_clk->next)
	{
		if(true ==  tmp_node_clk->has_car)
		{
			if(memcmp(tmp_node_clk->card_id, card_id, 5) == 0)
			{
				break;
			}
		}
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
	while(node_base == tmp_node_aclk->prev)
	{
		if(true ==  tmp_node_aclk->has_car)
		{
			if(memcmp(tmp_node_aclk->card_id, card_id, 5) == 0)
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
		*step 	= count_node_clk;
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
