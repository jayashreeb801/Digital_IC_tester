/*
 * lcd.h
 *
 *  Created on: Apr 28, 2025
 *  Author @    Student:   Jayashree Baskaran
 * Professor: Prof. Linden McClure
 * Course:    ECEN 5613 - Spring 2025
 *            University of Colorado Boulder
 * Date:      05/05/25
 * LAB : FINAL PROJECT
 */

#ifndef LCD_H
#define LCD_H

#include "stm32f4xx.h"

void lcd_init(void);
void lcd_send_cmd(uint8_t cmd);
void lcd_send_data(uint8_t data);
void lcd_set_cursor(uint8_t row, uint8_t col);
void delay_us(uint32_t us);
void lcd_display_string(const char* str);

#endif
