/*
 * io_configuration.h
 *
 *  Created on: Apr 30, 2025
 *  Author @     Student:   Jayashree Baskaran
 * Professor: Prof. Linden McClure
 * Course:    ECEN 5613 - Spring 2025
 *            University of Colorado Boulder
 * Date:      05/05/25
 * LAB : FINAL PROJECT
 */

#ifndef INC_IO_CONFIGURATION_H_
#define INC_IO_CONFIGURATION_H_


#include "stm32f4xx.h"

void setPinMode(int pinNumber, int Mode);
void PORTC_WritePin(uint8_t pin, uint8_t state);
uint8_t PORTC_ReadPin(uint8_t pin);

#endif /* INC_IO_CONFIGURATION_H_ */
