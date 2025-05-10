/*
 * io_configuration.c
 *
 *  Created on: Apr 30, 2025
 *    Author @ Student:   Jayashree Baskaran
 * Professor: Prof. Linden McClure
 * Course:    ECEN 5613 - Spring 2025
 *            University of Colorado Boulder
 * Date:      05/05/25
 * LAB : FINAL PROJECT
 */



#include "io_configuration.h"
/**
 * @brief Configure a specific pin on PORTC as input or output
 * @param pin: Pin number (0-15)
 * @param mode: Pin mode (0 for input, 1 for output)
 * @return None
 */
void setPinMode(int pinNumber, int Mode)
{
    // Enable clock for GPIOC
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    // Clear the mode bits for the specified pin (2 bits per pin)
    GPIOC->MODER &= ~(0x3U << (pinNumber * 2));

    if (Mode == 1) {
        // Set as output (01 in the 2-bit field)
        GPIOC->MODER |= (0x1U << (pinNumber * 2));

        // Configure as push-pull output
        GPIOC->OTYPER &= ~(0x1U << pinNumber); // Push-pull (0)

        // Configure high speed
        GPIOC->OSPEEDR &= ~(0x3U << (pinNumber * 2)); // Clear speed bits
        GPIOC->OSPEEDR |= (0x2U << (pinNumber * 2));  // High speed (10)
    }
    else if (Mode == 0) {
        // Pin is already configured as input (00 in the 2-bit field)
        // Configure pull-up/pull-down resistors (no pull-up/down)
        GPIOC->PUPDR &= ~(0x3U << (pinNumber * 2));
    }
}


/**
 * @brief Set a specific pin on PORTC to high or low
 * @param pin: Pin number (0-15)
 * @param state: Pin state (0 for low, 1 for high)
 * @return None
 */
void PORTC_WritePin(uint8_t pin, uint8_t state)
{
    if (state == 1) {
        // Set pin to high (1)
        GPIOC->BSRR = (1U << pin);
    }
    else if (state == 0) {
        // Set pin to low (0)
        // The BSRR register has reset bits in the upper 16 bits
        GPIOC->BSRR = (1U << (pin + 16));
    }
}


/**
 * @brief Read the status of a specific pin on PORTC
 * @param pin: Pin number (0-15)
 * @return uint8_t: Pin state (0 for low, 1 for high)
 */
uint8_t PORTC_ReadPin(uint8_t pin)
{
    // Read the input data register (IDR) and check the specific pin
    if ((GPIOC->IDR & (1U << pin)) != 0) {
        return 1;  // Pin is high
    }
    else {
        return 0;  // Pin is low
    }
}
