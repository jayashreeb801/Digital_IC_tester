/*
 * lcd.c
 * Updated: May 2025
 * Created on : 28th April 2025
  * Author @ Student:   Jayashree Baskaran
 * Professor: Prof. Linden McClure
 * Course:    ECEN 5613 - Spring 2025
 *            University of Colorado Boulder
 * Date:      05/05/25
 * LAB : FINAL PROJECT
 */

#include "stm32f4xx.h"
#include "lcd.h"

void delay_us(uint32_t us)
{
    us *= (SystemCoreClock / 1000000);  // Scale delay to CPU speed
    while(us--) __NOP();
}

void lcd_pulse_enable()
{
    GPIOA->BSRR = (1 << 1);           // E = HIGH
    delay_us(5);                      // >=1µs
    GPIOA->BSRR = (1 << (1 + 16));    // E = LOW
    delay_us(5);
}

void lcd_send_nibble(uint8_t nibble)
{
    GPIOA->BSRR = (0xF << (2 + 16));              // Clear PA6–PA2 (D7–D4)
    GPIOA->BSRR = ((nibble & 0x0F) << 2);          // Set PA6–PA2
    lcd_pulse_enable();
}

void lcd_send_cmd(uint8_t cmd)
{
    GPIOA->BSRR = (1 << (0 + 16));  // RS = 0 (command)
    lcd_send_nibble(cmd >> 4);      // High nibble
    lcd_send_nibble(cmd & 0x0F);    // Low nibble
    delay_us(50);
}

void lcd_send_data(uint8_t data)
{
    GPIOA->BSRR = (1 << 0);         // RS = 1 (data)
    lcd_send_nibble(data >> 4);
    lcd_send_nibble(data & 0x0F);
    delay_us(50);
}

void lcd_init()
{
    // Enable GPIOA clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // Set PA0–PA6 as output (RS, E, D4–D7)
    GPIOA->MODER &= ~(0x3FFF);    // Clear MODER for PA0–PA6
    GPIOA->MODER |=  (0x1555);    // Set PA0–PA6 as General Purpose Output

    delay_us(40000); // LCD power-on wait

    // Initialization sequence for 4-bit mode
    lcd_send_nibble(0x03);
    delay_us(5000);
    lcd_send_nibble(0x03);
    delay_us(5000);
    lcd_send_nibble(0x03);
    delay_us(5000);
    lcd_send_nibble(0x02); // Set to 4-bit
    delay_us(5000);

    lcd_send_cmd(0x28); // Function set: 4-bit, 2 lines, 5x8 font
    delay_us(2000);
    lcd_send_cmd(0x0C); // Display ON, Cursor OFF
    delay_us(2000);
    lcd_send_cmd(0x06); // Entry mode: Increment cursor
    delay_us(2000);
    lcd_send_cmd(0x01); // Clear display
    delay_us(2000);
}

void lcd_set_cursor(uint8_t row, uint8_t col)
{
    uint8_t addr[] = {0x00, 0x40, 0x10, 0x50};
    lcd_send_cmd(0x80 | (addr[row] + col));
    delay_us(2000);
}

void lcd_display_string(const char* str)
{
    while(*str)
    {
        lcd_send_data(*str++);
    }
}
