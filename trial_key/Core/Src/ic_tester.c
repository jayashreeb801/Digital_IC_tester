/*
 * Created on : 28th April 2025
  * Author @ Student:   Jayashree Baskaran
 * Professor: Prof. Linden McClure
 * Course:    ECEN 5613 - Spring 2025
 *            University of Colorado Boulder
 * Date:      05/05/25
 * LAB : FINAL PROJECT
 */


#include "stdio.h"
#include "stm32f4xx_hal.h"
#include "ic_tester.h"
#include "lcd.h"
#include "keypad.h"
#include "io_configuration.h"


// Buffer for IC number input
char ic_number[5] = {0};
uint8_t input_pos = 0;
uint8_t pinState;
uint8_t final[4];
//truth table for gates
uint8_t Gate1_Output[4];
    uint8_t Gate2_Output[4];
    uint8_t Gate3_Output[4];
    uint8_t Gate4_Output[4];



// Function to process keypad input and build IC number
void process_keypad_input(char key) {
    if (key >= '0' && key <= '9' && input_pos < 4) {
        // Add digit to IC number
        ic_number[input_pos++] = key;
        ic_number[input_pos] = '\0';

        // Display on LCD - Fixed cursor position
        lcd_set_cursor(0, 11 + input_pos - 1);
        lcd_send_data(key);
    }
    else if (key == '*' && input_pos > 0) {
        // Backspace
        input_pos--;
        ic_number[input_pos] = '\0';

        // Clear digit on LCD - Fixed cursor position
        lcd_set_cursor(0, 11 + input_pos);
        lcd_send_data(' ');
        lcd_set_cursor(0, 11 + input_pos);
    }
    else if (key == '#' && input_pos > 0) {
        // Enter key - process the IC number
        test_ic();

        // Reset for next entry
        input_pos = 0;
        ic_number[0] = '\0';

        // Clear display and show prompt again
        lcd_send_cmd(0x01);
        delay_us(2000);
        lcd_set_cursor(0, 0);
        lcd_display_string("Enter IC No:");
    }
}

// Initialize IC tester GPIO pins with proper output strength
int test_7408()
{
	 uint8_t and_truth_table[4] = {0, 0, 0, 1};

    setPinMode(0,1);
    setPinMode(1,1);
    setPinMode(2,0);

    setPinMode(3,1);
    setPinMode(4,1);
    setPinMode(5,0);

    setPinMode(6,1);
    PORTC_WritePin(6,0);


    setPinMode(7,0);
    setPinMode(8,1);
    setPinMode(9,1);

    setPinMode(10,0);
    setPinMode(11,1);
    setPinMode(12,1);

    PORTC_WritePin(0,0);
    PORTC_WritePin(1,0);
    HAL_Delay(1000);

   pinState = PORTC_ReadPin(2);
    Gate1_Output[0] = pinState;
    PORTC_WritePin(0,0);
    PORTC_WritePin(1,1);
    HAL_Delay(1000);
     pinState = PORTC_ReadPin(2);
     Gate1_Output[1] = pinState;
    PORTC_WritePin(0,1);
    PORTC_WritePin(1,0);
    HAL_Delay(1000);
     pinState = PORTC_ReadPin(2);
     Gate1_Output[2] = pinState;

    PORTC_WritePin(0,1);
    PORTC_WritePin(1,1);
    HAL_Delay(1000);
     pinState = PORTC_ReadPin(2);
     Gate1_Output[3] = pinState;

    PORTC_WritePin(3,0);
        PORTC_WritePin(4,0);
        HAL_Delay(1000);

        pinState = PORTC_ReadPin(5);
        Gate2_Output[0] = pinState;
        PORTC_WritePin(3,0);
        PORTC_WritePin(4,1);
        HAL_Delay(1000);
         pinState = PORTC_ReadPin(5);
         Gate2_Output[1] = pinState;

        PORTC_WritePin(3,1);
        PORTC_WritePin(4,0);
        HAL_Delay(1000);
         pinState = PORTC_ReadPin(5);
         Gate2_Output[2] = pinState;

        PORTC_WritePin(3,1);
        PORTC_WritePin(4,1);
        HAL_Delay(1000);
         pinState = PORTC_ReadPin(5);
         Gate2_Output[3] = pinState;



         PORTC_WritePin(9,0); PORTC_WritePin(8,0); HAL_Delay(1000);
                Gate3_Output[0] = PORTC_ReadPin(7);
                PORTC_WritePin(9,0); PORTC_WritePin(8,1); HAL_Delay(1000);
                Gate3_Output[1] = PORTC_ReadPin(7);
                PORTC_WritePin(9,1); PORTC_WritePin(8,0); HAL_Delay(1000);
                Gate3_Output[2] = PORTC_ReadPin(7);
                PORTC_WritePin(9,1); PORTC_WritePin(8,1); HAL_Delay(1000);
                Gate3_Output[3] = PORTC_ReadPin(7);

                PORTC_WritePin(12,0); PORTC_WritePin(11,0); HAL_Delay(1000);
                Gate4_Output[0] = PORTC_ReadPin(10);
                PORTC_WritePin(12,0); PORTC_WritePin(11,1); HAL_Delay(1000);
                Gate4_Output[1] = PORTC_ReadPin(10);
                PORTC_WritePin(12,1); PORTC_WritePin(11,0); HAL_Delay(1000);
                Gate4_Output[2] = PORTC_ReadPin(10);
                PORTC_WritePin(12,1); PORTC_WritePin(11,1); HAL_Delay(1000);
                Gate4_Output[3] = PORTC_ReadPin(10);

                 final[0] = compareArrays(and_truth_table,Gate1_Output );
                 final[1] = compareArrays(and_truth_table,Gate2_Output );
                 final[2] = compareArrays(and_truth_table,Gate3_Output );
                 final[3] = compareArrays(and_truth_table,Gate4_Output );
                 for (uint8_t i = 0; i < 4; i++)
                    {
                        if (final[i] != 1)
                        {
                            return 0;  // Arrays are different
                        }
                        // If we reach here, all elements are the same

                    }

               return 1;

}
int test_7432() // OR GATE
{
    uint8_t or_truth_table[4] = {0, 1, 1, 1};
    setPinMode(0,1); setPinMode(1,1); setPinMode(2,0);
    setPinMode(3,1); setPinMode(4,1); setPinMode(5,0);
    setPinMode(6,1); PORTC_WritePin(6,0);
    setPinMode(7,0);setPinMode(8,1);setPinMode(9,1);
    setPinMode(10,0);setPinMode(11,1);setPinMode(12,1);

    PORTC_WritePin(0,0); PORTC_WritePin(1,0); HAL_Delay(1000);
    Gate1_Output[0] = PORTC_ReadPin(2);
    PORTC_WritePin(0,0); PORTC_WritePin(1,1); HAL_Delay(1000);
    Gate1_Output[1] = PORTC_ReadPin(2);
    PORTC_WritePin(0,1); PORTC_WritePin(1,0); HAL_Delay(1000);
    Gate1_Output[2] = PORTC_ReadPin(2);
    PORTC_WritePin(0,1); PORTC_WritePin(1,1); HAL_Delay(1000);
    Gate1_Output[3] = PORTC_ReadPin(2);

    PORTC_WritePin(3,0); PORTC_WritePin(4,0); HAL_Delay(1000);
    Gate2_Output[0] = PORTC_ReadPin(5);
    PORTC_WritePin(3,0); PORTC_WritePin(4,1); HAL_Delay(1000);
    Gate2_Output[1] = PORTC_ReadPin(5);
    PORTC_WritePin(3,1); PORTC_WritePin(4,0); HAL_Delay(1000);
    Gate2_Output[2] = PORTC_ReadPin(5);
    PORTC_WritePin(3,1); PORTC_WritePin(4,1); HAL_Delay(1000);
    Gate2_Output[3] = PORTC_ReadPin(5);

    PORTC_WritePin(9,0); PORTC_WritePin(8,0); HAL_Delay(1000);
    Gate3_Output[0] = PORTC_ReadPin(7);
    PORTC_WritePin(9,0); PORTC_WritePin(8,1); HAL_Delay(1000);
    Gate3_Output[1] = PORTC_ReadPin(7);
    PORTC_WritePin(9,1); PORTC_WritePin(8,0); HAL_Delay(1000);
    Gate3_Output[2] = PORTC_ReadPin(7);
    PORTC_WritePin(9,1); PORTC_WritePin(8,1); HAL_Delay(1000);
    Gate3_Output[3] = PORTC_ReadPin(7);

    PORTC_WritePin(12,0); PORTC_WritePin(11,0); HAL_Delay(1000);
    Gate4_Output[0] = PORTC_ReadPin(10);
    PORTC_WritePin(12,0); PORTC_WritePin(11,1); HAL_Delay(1000);
    Gate4_Output[1] = PORTC_ReadPin(10);
    PORTC_WritePin(12,1); PORTC_WritePin(11,0); HAL_Delay(1000);
    Gate4_Output[2] = PORTC_ReadPin(10);
    PORTC_WritePin(12,1); PORTC_WritePin(11,1); HAL_Delay(1000);
    Gate4_Output[3] = PORTC_ReadPin(10);

    final[0] = compareArrays(or_truth_table, Gate1_Output);
    final[1] = compareArrays(or_truth_table, Gate2_Output);
    final[2] = compareArrays(or_truth_table, Gate3_Output);
    final[3] = compareArrays(or_truth_table, Gate4_Output);

    for (uint8_t i = 0; i < 4; i++) {
        if (final[i] != 1) return 0;
    }
    return 1;
}
int test_7486() // XOR GATE
{
    uint8_t xor_truth_table[4] = {0, 1, 1, 0};

    setPinMode(0,1); setPinMode(1,1); setPinMode(2,0);
    setPinMode(3,1); setPinMode(4,1); setPinMode(5,0);
    setPinMode(6,1); PORTC_WritePin(6,0);
    setPinMode(7,0);setPinMode(8,1);setPinMode(9,1);
      setPinMode(10,0);setPinMode(11,1);setPinMode(12,1);


    PORTC_WritePin(0,0); PORTC_WritePin(1,0); HAL_Delay(1000);
    Gate1_Output[0] = PORTC_ReadPin(2);
    PORTC_WritePin(0,0); PORTC_WritePin(1,1); HAL_Delay(1000);
    Gate1_Output[1] = PORTC_ReadPin(2);
    PORTC_WritePin(0,1); PORTC_WritePin(1,0); HAL_Delay(1000);
    Gate1_Output[2] = PORTC_ReadPin(2);
    PORTC_WritePin(0,1); PORTC_WritePin(1,1); HAL_Delay(1000);
    Gate1_Output[3] = PORTC_ReadPin(2);

    PORTC_WritePin(3,0); PORTC_WritePin(4,0); HAL_Delay(1000);
    Gate2_Output[0] = PORTC_ReadPin(5);
    PORTC_WritePin(3,0); PORTC_WritePin(4,1); HAL_Delay(1000);
    Gate2_Output[1] = PORTC_ReadPin(5);
    PORTC_WritePin(3,1); PORTC_WritePin(4,0); HAL_Delay(1000);
    Gate2_Output[2] = PORTC_ReadPin(5);
    PORTC_WritePin(3,1); PORTC_WritePin(4,1); HAL_Delay(1000);
    Gate2_Output[3] = PORTC_ReadPin(5);

    PORTC_WritePin(9,0); PORTC_WritePin(8,0); HAL_Delay(1000);
           Gate3_Output[0] = PORTC_ReadPin(7);
           PORTC_WritePin(9,0); PORTC_WritePin(8,1); HAL_Delay(1000);
           Gate3_Output[1] = PORTC_ReadPin(7);
           PORTC_WritePin(9,1); PORTC_WritePin(8,0); HAL_Delay(1000);
           Gate3_Output[2] = PORTC_ReadPin(7);
           PORTC_WritePin(9,1); PORTC_WritePin(8,1); HAL_Delay(1000);
           Gate3_Output[3] = PORTC_ReadPin(7);

           PORTC_WritePin(12,0); PORTC_WritePin(11,0); HAL_Delay(1000);
           Gate4_Output[0] = PORTC_ReadPin(10);
           PORTC_WritePin(12,0); PORTC_WritePin(11,1); HAL_Delay(1000);
           Gate4_Output[1] = PORTC_ReadPin(10);
           PORTC_WritePin(12,1); PORTC_WritePin(11,0); HAL_Delay(1000);
           Gate4_Output[2] = PORTC_ReadPin(10);
           PORTC_WritePin(12,1); PORTC_WritePin(11,1); HAL_Delay(1000);
           Gate4_Output[3] = PORTC_ReadPin(10);

    final[0] = compareArrays(xor_truth_table, Gate1_Output);
    final[1] = compareArrays(xor_truth_table, Gate2_Output);
    final[2] = compareArrays(xor_truth_table, Gate3_Output);
    final[3] = compareArrays(xor_truth_table, Gate4_Output);

        for (uint8_t i = 0; i < 4; i++) {
            if (final[i] != 1) return 0;
        }
        return 1;
    }
int test_7400() // NAND GATE
{
    uint8_t nand_truth_table[4] = {1, 1, 1, 0};

    setPinMode(0,1); setPinMode(1,1); setPinMode(2,0);
    setPinMode(3,1); setPinMode(4,1); setPinMode(5,0);
    setPinMode(6,1); PORTC_WritePin(6,0);
    setPinMode(7,0);setPinMode(8,1);setPinMode(9,1);
      setPinMode(10,0);setPinMode(11,1);setPinMode(12,1);


    PORTC_WritePin(0,0); PORTC_WritePin(1,0); HAL_Delay(1000);
    Gate1_Output[0] = PORTC_ReadPin(2);
    PORTC_WritePin(0,0); PORTC_WritePin(1,1); HAL_Delay(1000);
    Gate1_Output[1] = PORTC_ReadPin(2);
    PORTC_WritePin(0,1); PORTC_WritePin(1,0); HAL_Delay(1000);
    Gate1_Output[2] = PORTC_ReadPin(2);
    PORTC_WritePin(0,1); PORTC_WritePin(1,1); HAL_Delay(1000);
    Gate1_Output[3] = PORTC_ReadPin(2);

    PORTC_WritePin(3,0); PORTC_WritePin(4,0); HAL_Delay(1000);
    Gate2_Output[0] = PORTC_ReadPin(5);
    PORTC_WritePin(3,0); PORTC_WritePin(4,1); HAL_Delay(1000);
    Gate2_Output[1] = PORTC_ReadPin(5);
    PORTC_WritePin(3,1); PORTC_WritePin(4,0); HAL_Delay(1000);
    Gate2_Output[2] = PORTC_ReadPin(5);
    PORTC_WritePin(3,1); PORTC_WritePin(4,1); HAL_Delay(1000);
    Gate2_Output[3] = PORTC_ReadPin(5);

    PORTC_WritePin(9,0); PORTC_WritePin(8,0); HAL_Delay(1000);
       Gate3_Output[0] = PORTC_ReadPin(7);
       PORTC_WritePin(9,0); PORTC_WritePin(8,1); HAL_Delay(1000);
       Gate3_Output[1] = PORTC_ReadPin(7);
       PORTC_WritePin(9,1); PORTC_WritePin(8,0); HAL_Delay(1000);
       Gate3_Output[2] = PORTC_ReadPin(7);
       PORTC_WritePin(9,1); PORTC_WritePin(8,1); HAL_Delay(1000);
       Gate3_Output[3] = PORTC_ReadPin(7);

       PORTC_WritePin(12,0); PORTC_WritePin(11,0); HAL_Delay(1000);
       Gate4_Output[0] = PORTC_ReadPin(10);
       PORTC_WritePin(12,0); PORTC_WritePin(11,1); HAL_Delay(1000);
       Gate4_Output[1] = PORTC_ReadPin(10);
       PORTC_WritePin(12,1); PORTC_WritePin(11,0); HAL_Delay(1000);
       Gate4_Output[2] = PORTC_ReadPin(10);
       PORTC_WritePin(12,1); PORTC_WritePin(11,1); HAL_Delay(1000);
       Gate4_Output[3] = PORTC_ReadPin(10);

    final[0] = compareArrays(nand_truth_table, Gate1_Output);
    final[1] = compareArrays(nand_truth_table, Gate2_Output);
    final[2] = compareArrays(nand_truth_table, Gate3_Output);
    final[3] = compareArrays(nand_truth_table, Gate4_Output);

    for (uint8_t i = 0; i < 4; i++) {
        if (final[i] != 1) return 0;
    }
    return 1;
}

int test_7402() // NOR GATE
{
    uint8_t or_truth_table[4] = {1, 0, 0, 0};


    setPinMode(0,0); setPinMode(1,1); setPinMode(2,1);
    setPinMode(3,0); setPinMode(4,1); setPinMode(5,1);

    setPinMode(6,1); PORTC_WritePin(6,0); //ground

    setPinMode(7,1); setPinMode(8,1); setPinMode(9,0);
    setPinMode(10,1); setPinMode(11,1); setPinMode(12,0);

    PORTC_WritePin(1,0); PORTC_WritePin(2,0); HAL_Delay(1000);
    Gate1_Output[0] = PORTC_ReadPin(0);
    PORTC_WritePin(1,0); PORTC_WritePin(2,1); HAL_Delay(1000);
    Gate1_Output[1] = PORTC_ReadPin(0);
    PORTC_WritePin(1,1); PORTC_WritePin(2,0); HAL_Delay(1000);
    Gate1_Output[2] = PORTC_ReadPin(0);
    PORTC_WritePin(1,1); PORTC_WritePin(2,1); HAL_Delay(1000);
    Gate1_Output[3] = PORTC_ReadPin(0);

    PORTC_WritePin(4,0); PORTC_WritePin(5,0); HAL_Delay(1000);
    Gate2_Output[0] = PORTC_ReadPin(3);
    PORTC_WritePin(4,0); PORTC_WritePin(5,1);  HAL_Delay(1000);
    Gate2_Output[1] = PORTC_ReadPin(3);
    PORTC_WritePin(4,1); PORTC_WritePin(5,0); HAL_Delay(1000);
    Gate2_Output[2] = PORTC_ReadPin(3);
    PORTC_WritePin(4,1); PORTC_WritePin(5,1);  HAL_Delay(1000);
    Gate2_Output[3] = PORTC_ReadPin(3);

    PORTC_WritePin(7,0); PORTC_WritePin(8,0); HAL_Delay(1000);
    Gate3_Output[0] = PORTC_ReadPin(9);
    PORTC_WritePin(7,0); PORTC_WritePin(8,1); HAL_Delay(1000);
    Gate3_Output[1] = PORTC_ReadPin(9);
    PORTC_WritePin(7,1); PORTC_WritePin(8,0); HAL_Delay(1000);
    Gate3_Output[2] = PORTC_ReadPin(9);
    PORTC_WritePin(7,1); PORTC_WritePin(8,1); HAL_Delay(1000);
    Gate3_Output[3] = PORTC_ReadPin(9);

    PORTC_WritePin(10,0); PORTC_WritePin(11,0); HAL_Delay(1000);
    Gate4_Output[0] = PORTC_ReadPin(12);
    PORTC_WritePin(10,0); PORTC_WritePin(11,1); HAL_Delay(1000);
    Gate4_Output[1] = PORTC_ReadPin(12);
    PORTC_WritePin(10,1); PORTC_WritePin(11,0); HAL_Delay(1000);
    Gate4_Output[2] = PORTC_ReadPin(12);
    PORTC_WritePin(10,1); PORTC_WritePin(11,1); HAL_Delay(1000);
    Gate4_Output[3] = PORTC_ReadPin(12);

    final[0] = compareArrays(or_truth_table, Gate1_Output);
    final[1] = compareArrays(or_truth_table, Gate2_Output);
    final[2] = compareArrays(or_truth_table, Gate3_Output);
    final[3] = compareArrays(or_truth_table, Gate4_Output);

    for (uint8_t i = 0; i < 4; i++) {
        if (final[i] != 1) return 0;
    }
    return 1;
}


int test_7404() // NOT GATE - HEX INVERTER
{
	uint8_t final_not[6];
    uint8_t not_truth_table[2] = {1, 0};
    uint8_t Gate1_Output_not[2];
        uint8_t Gate2_Output_not[2];
        uint8_t Gate3_Output_not[2];
        uint8_t Gate4_Output_not[2];
        uint8_t Gate5_Output_not[2];
        uint8_t Gate6_Output_not[2];

    setPinMode(0,1); setPinMode(1,0);
    setPinMode(2,1);setPinMode(3,0);
    setPinMode(4,1); setPinMode(5,0);
    setPinMode(6,1); PORTC_WritePin(6,0);/// ground
    setPinMode(7,0); setPinMode(8,1);
    setPinMode(9,0); setPinMode(10,1);
    setPinMode(11,0); setPinMode(12,1);


    PORTC_WritePin(0,0);  HAL_Delay(1000);
    Gate1_Output_not[0] = PORTC_ReadPin(1);
    PORTC_WritePin(0,1); HAL_Delay(1000);
    Gate1_Output_not[1] = PORTC_ReadPin(1);

    PORTC_WritePin(2,0);  HAL_Delay(1000);
    Gate2_Output_not[0] = PORTC_ReadPin(3);
    PORTC_WritePin(2,1);  HAL_Delay(1000);
    Gate2_Output_not[1] = PORTC_ReadPin(3);

    PORTC_WritePin(4,0);  HAL_Delay(1000);
    Gate3_Output_not[0] = PORTC_ReadPin(5);
    PORTC_WritePin(4,1);  HAL_Delay(1000);
    Gate3_Output_not[1] = PORTC_ReadPin(5);

    PORTC_WritePin(8,0);  HAL_Delay(1000);
    Gate4_Output_not[0] = PORTC_ReadPin(7);
    PORTC_WritePin(8,1);  HAL_Delay(1000);
    Gate4_Output_not[1] = PORTC_ReadPin(7);

    PORTC_WritePin(10,0);  HAL_Delay(1000);
    Gate5_Output_not[0] = PORTC_ReadPin(9);
    PORTC_WritePin(10,1); HAL_Delay(1000);
    Gate5_Output_not[1] = PORTC_ReadPin(9);

       PORTC_WritePin(12,0);  HAL_Delay(1000);
       Gate6_Output_not[0] = PORTC_ReadPin(11);
       PORTC_WritePin(12,1);  HAL_Delay(1000);
       Gate6_Output_not[1] = PORTC_ReadPin(11);

       final_not[0] = compareArrays(not_truth_table, Gate1_Output_not);
       final_not[1] = compareArrays(not_truth_table, Gate2_Output_not);
       final_not[2] = compareArrays(not_truth_table, Gate3_Output_not);
       final_not[3] = compareArrays(not_truth_table, Gate4_Output_not);
       final_not[4] = compareArrays(not_truth_table, Gate5_Output_not);
       final_not[5] = compareArrays(not_truth_table, Gate6_Output_not);

    for (uint8_t i = 0; i < 6; i++) {
        if (final_not[i] != 1) return 0;
    }
    return 1;
}

uint8_t compareArrays(const uint8_t* array1, const uint8_t* array2)
{
    // Check for null pointers
    if (array1 == NULL || array2 == NULL)
    {
        return 0;  // Arrays can't be identical if either is NULL
    }

    // Compare each element
    for (uint8_t i = 0; i < 4; i++)
    {
        if (array1[i] != array2[i])
        {
            return 0;  // Arrays are different
        }
    }

    // If we reach here, all elements are the same
    return 1;  // Arrays are identical
}


// Main IC testing function
void test_ic() {
    uint8_t result = 0;
    // Clear LCD and show testing message
    lcd_send_cmd(0x01);
    delay_us(2000);
    lcd_set_cursor(0, 0);
    lcd_display_string("Testing IC:  ");
    lcd_set_cursor(0, 11);
    lcd_display_string(ic_number);
    // Allow power to stabilize
    delay_us(500000); // 1 second delay

    // Test the appropriate IC based on input
    if (strcmp(ic_number, "7408") == 0) {
        lcd_set_cursor(1, 0);
        lcd_display_string(" AND ");
        result = test_7408();
    }
    else if (strcmp(ic_number, "7432") == 0) {
        lcd_set_cursor(1, 0);
        lcd_display_string(" OR ");
        result = test_7432();
    }
    else if (strcmp(ic_number, "7402") == 0) {
            lcd_set_cursor(1, 0);
            lcd_display_string(" NOR ");
            result = test_7402();
        }
    else if (strcmp(ic_number, "7486") == 0) {
        lcd_set_cursor(1, 0);
        lcd_display_string(" XOR");
        result = test_7486();
    }
    else if (strcmp(ic_number, "7400") == 0) {
        lcd_set_cursor(1, 0);
        lcd_display_string(" NAND ");
        result = test_7400();
    }
    else if (strcmp(ic_number, "7404") == 0) {
            lcd_set_cursor(1, 0);
            lcd_display_string(" HEX  INVERT ");
            result = test_7404();
        }
    else {
        // Unsupported IC
        lcd_set_cursor(1, 0);
        lcd_display_string("Unsupported  ");
        delay_us(300000);  // 3 seconds delay
        return;
    }

    // Display test result
    lcd_set_cursor(2, 0);
    if (result) {
        lcd_display_string("Status:  GOOD    ");
    } else {
        lcd_display_string("Status:  FAULTY   ");
    }

    // Message to press # for new test
    lcd_set_cursor(3, 0);
    lcd_display_string("# - new IC ");


    // Allow time to read the result
    delay_us(500000);
}
