/*
 * lcd_i2c.h
 *
 *  Created on: Aug 12, 2019
 *      Author: Admin
 */

#ifndef _LCD_I2C_H_
#define _LCD_I2C_H_

#include "../i2c_dev/i2c_dev.h"

void lcd_init (void);   // initialize lcd

void lcd_send_cmd (char cmd);  // send command to the lcd

void lcd_send_data (char data);  // send data to the lcd

void lcd_send_string (char *str);  // send string to the lcd

void lcd_clear_display (void);	//clear display lcd

void lcd_goto_XY (int row, int col); //set proper location on screen

#endif /* EXTERNAL_LIBRARY_LCD_I2C_LCD_I2C_H_ */
