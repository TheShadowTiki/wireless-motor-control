#include <msp430.h>
#include <stdio.h>
#include <math.h>
#include "A4_I2C.h"

int Value = 0, prev = 0;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                   // Stop watchdog timer

    // Configure UART
    UCA0CTLW0 |= UCSWRST;                       // Put eUSCI in reset
    UCA0CTLW0 |= UCSSEL__SMCLK;                 // Select SMCLK as the clock source

    // Baud Rate calculation
    UCA0BR0 = 8;                                // 1000000/115200 = 8.68
    UCA0MCTLW = 0xD600;                         // 1000000/115200 - INT(1000000/115200)=0.68
                                                // UCBRSx value = 0xD6 (See UG)

    // Configure UART pins
    P1SEL1 &= ~BIT6;                            // Set P1.6 for UART TX
    P1SEL0 |= BIT6;

    P6DIR |= BIT1;                              // Set P6.1 as PWM output to Motor
    P6SEL0 |= BIT1;

    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port settings

    UCA0CTLW0 &= ~UCSWRST;                      // Initialize eUSC
    UCA0IE |= UCRXIE;                           // Enable USCI_A0 RX interrupt

    I2C_Init(0x27);                             // Initialize I2C with address 0x27
    LCD_Setup();
    LCD_SetCursor(0, 0);                        // Set the cursor to the first row, first column
    LCD_Write("Motor Percentage");              // Prints "Motor Percentage" to LCD Screen

    // Setup Timer3_B CCR
    TB3CCR0 = 100;                              // Sets period of the PWM
    TB3CCTL2 = OUTMOD_7;                        // Set output mode to reset/set
    TB3CCR2 = 0;                                // Initialize PWM duty cycle to 0

    // Setup Timer3_B
    TB3CTL = TBSSEL_1 | MC_1 | TBCLR;           // Select ACLK, up mode, clear timer


    while(1)
    {
        if (prev != Value)                      // Check for change in value
        {
            prev = Value;                       // Sets prev to "current" value
            LCD_SetCursor(0, 1);                // Moves cursor to second row, first column
            LCD_Write("                ");      // Clears previous motor percentage
            LCD_SetCursor(3, 1);                // Move cursor to second row, fourth column
            LCD_WriteNum(Value);                // Displays motor percentage value
            LCD_Write("% Power ");              // Displays "% Power " after motor percentage is shown
            TB3CCR2 = Value;                    // Update PWM duty cycle to new motor percentage
        }
    }

    return 0;
}

// UART ISR
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
    Value = UCA0RXBUF;                          // Save recieved value from UART into Value
}
