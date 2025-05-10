/*
 * keypad.c
 *
 *  Created on: Apr 28, 2025
 * Author @  Student:   Jayashree Baskaran
 * Professor: Prof. Linden McClure
 * Course:    ECEN 5613 - Spring 2025
 *            University of Colorado Boulder
 * Date:      05/05/25
 * LAB : FINAL PROJECT
 */

#include "stm32f4xx.h"
#include "keypad.h"
#include "lcd.h"

void keypad_init()
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    GPIOB->MODER &= ~(0xFF);
    GPIOB->PUPDR &= ~(0xFF);
    GPIOB->PUPDR |= (0x55);

    GPIOB->MODER &= ~(0xFF00);
    GPIOB->MODER |= (0x5500);
}

char keypad_scan()
{
    GPIOB->BSRR = (0xF0 << 16);
    GPIOB->BSRR = (1 << 4) | (1 << 5) | (1 << 6);
    delay_us(5);
    if ((GPIOB->IDR & 0xF) == 0x0E) return '*';
    if ((GPIOB->IDR & 0xF) == 0x0D) return '3';
    if ((GPIOB->IDR & 0xF) == 0x0B) return '2';
    if ((GPIOB->IDR & 0xF) == 0x07) return '1';

    GPIOB->BSRR = (0xF0 << 16);
    GPIOB->BSRR = (1 << 4) | (1 << 5) | (1 << 7);
    delay_us(5);
    if ((GPIOB->IDR & 0xF) == 0x0E) return '0';
    if ((GPIOB->IDR & 0xF) == 0x0D) return '6';
    if ((GPIOB->IDR & 0xF) == 0x0B) return '5';
    if ((GPIOB->IDR & 0xF) == 0x07) return '4';

    GPIOB->BSRR = (0xF0 << 16);
    GPIOB->BSRR = (1 << 4) | (1 << 6) | (1 << 7);
    delay_us(5);
    if ((GPIOB->IDR & 0xF) == 0x0E) return '#';
    if ((GPIOB->IDR & 0xF) == 0x0D) return '9';
    if ((GPIOB->IDR & 0xF) == 0x0B) return '8';
    if ((GPIOB->IDR & 0xF) == 0x07) return '7';

    return 0;
}

