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

}

void NODE_init_node(NODE_PARKING *node, uint8_t node_id)
{
	node->node_id = node_id;
	memset(node->card_id, 0, 5);
	node->has_car = false;
	node->step_acl = node->step_cl = 0;
	node->next = node->prev = NULL;
}
