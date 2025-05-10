/*
 * ic_tester.h
 *
 *  Created on: Apr 28, 2025
 *Author @ Student:   Jayashree Baskaran
 * Professor: Prof. Linden McClure
 * Course:    ECEN 5613 - Spring 2025
 *            University of Colorado Boulder
 * Date:      05/05/25
 * LAB : FINAL PROJECT
 * */

#ifndef IC_TESTER_H_
#define IC_TESTER_H_

#include <stdint.h>
#include <string.h>
#include "io_configuration.h"

// Function prototypes
void process_keypad_input(char key);
void test_ic();
uint8_t compareArrays(const uint8_t* array1, const uint8_t* array2);

int test_7408();
int test_7432();
int test_7486();
int test_7400();
int test_7402();
int test_7404();
int test_7490();

#endif /* IC_TESTER_H_ */
