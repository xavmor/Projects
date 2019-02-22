#include "timer_a.h"
#include "timer32.h"
#include "cs.h"


#ifndef __delay_h__
#define __delay_h__

// If the DCO is set at 12 MHz then the SMCLK will be set to 12 MHz
// then we will divide by 12 will give us a timer of 1 micros econds
Timer_A_ContinuousModeConfig delay =
{
     TIMER_A_CLOCKSOURCE_SMCLK,             //uint_fast16_t clockSource
     TIMER_A_CLOCKSOURCE_DIVIDER_12,         //uint_fast16_t clockSourceDivider
     TIMER_A_TAIE_INTERRUPT_DISABLE,
     TIMER_A_SKIP_CLEAR
};

// IDK how precise this is
void microDelay(uint16_t microSec)
{
    // Make sure the value entered was not invalid
    if (microSec > 60000)
        ;
    //delay->clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
    delay.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_12;
    //delay->timerInterruptEnable_TAIE =TIMER_A_TAIE_INTERRUPT_DISABLE;
    //delay->timerClear = TIMER_A_SKIP_CLEAR;
    //delay->clockSource ;
    Timer_A_clearTimer(TIMER_A1_BASE);
    //Timer_A_ContinuousModeConfig * test = &delay;

    Timer_A_configureContinuousMode(TIMER_A1_BASE, &delay);
    //Timer_A_initCompare();
    Timer_A_startCounter(TIMER_A1_BASE, TIMER_A_CONTINUOUS_MODE);

    while(microSec > Timer_A_getCounterValue(TIMER_A1_BASE));

    // turn timer off we are done with it
    Timer_A_stopTimer(TIMER_A1_BASE);
}


// I don't think this is very accurate
void milliDelay(uint16_t milliSec)
{
    uint32_t microSec;

    // this delay is clocking at 1 microsecond every tick
    microSec = milliSec * 1000;

    while(microSec)
    {
        Timer_A_clearTimer(TIMER_A1_BASE);
        Timer_A_configureContinuousMode(TIMER_A1_BASE, &delay);
        Timer_A_startCounter(TIMER_A1_BASE, TIMER_A_CONTINUOUS_MODE);

        if (microSec < 65000)
        {
            while(microSec > Timer_A_getCounterValue(TIMER_A1_BASE));
            microSec = 0;
        }
        else
        {
            while (65000 > Timer_A_getCounterValue(TIMER_A1_BASE));
            microSec -= 65000;
        }
    }


    //delay->clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
    //delay->clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_12;
    //delay->timerInterruptEnable_TAIE =TIMER_A_TAIE_INTERRUPT_DISABLE;
    //delay->timerClear = TIMER_A_SKIP_CLEAR;
    //delay->clockSource ;

    // turn timer off we are done with it
    Timer_A_stopTimer(TIMER_A1_BASE);
}



void getTimeStamp(unsigned long  * timeStamp)
{
    *timeStamp = Timer32_getValue(TIMER32_0_BASE);

     //0;
}


#endif  // delay_h



///**
// * @details   Initialize EUSCI_A0 for UART operation
// * @details   115,200 baud rate (assuming 12 MHz SMCLK clock),
// * @details   8 bit word length, no parity bits, one stop bit
// * @param  none
// * @return none
// * @note   assumes 48 MHz bus and 12 MHz SMCLK
// * @brief  Initialize EUSCI A0
// */
//void UART0_Init(void);
//
///**
// * @details   Transmit a character to EUSCI_A0 UART
// * @details   Busy-wait synchronization,
// * @details   blocking, wait for UART to be ready
// * @param  letter is the ASCII code for key to send
// * @return none
// * @note   UART0_Init must be called once prior
// * @brief  Transmit byte out of MSP432
// */
//void UART0_OutChar(char letter);
//
///**
// * @details   Transmit a string to EUSCI_A0 UART
// * @param  pt is pointer to null-terminated ASCII string to be transferred
// * @return none
// * @note   UART0_Init must be called once prior
// * @brief  Transmit string out of MSP432
// */
//void UART0_OutString(char *pt);
//
//
//
//
//
//// Other Stuff
////------------UART0_OutChar------------
//// Output 8-bit to serial port
//// Input: letter is an 8-bit ASCII character to be transferred
//// Output: none
//void UART0_OutChar(char letter){
//  while((EUSCI_A0->IFG&0x02) == 0);
//  EUSCI_A0->TXBUF = letter;
//}
//
////------------UART0_OutString------------
//// Output String (NULL termination)
//// Input: pointer to a NULL-terminated string to be transferred
//// Output: none
//void UART0_OutString(char *pt){
//  while(*pt){
//    UART0_OutChar(*pt);
//    pt++;
//  }
//}
//
///**
// * @details   Transmit a number as ASCII characters in unsigned decimal format
// * @details   Variable format 1-10 digits with no space before or after
// * @param  n is a unsigned 32-bit number to be transferred
// * @return none
// * @note   UART0_Init must be called once prior
// * @brief  Transmit an unsigned number out of MSP432
// */
//void UART0_OutUDec(uint32_t n);
//
//
//
//
////------------UART0_Init------------
//// Initialize the UART for 115,200 baud rate (assuming 12 MHz SMCLK clock),
//// 8 bit word length, no parity bits, one stop bit
//// Input: none
//// Output: none
//void UART0_Init(void){
//  EUSCI_A0->CTLW0 = 0x0001;                   // hold the USCI module in reset mode
//  // bit15=0,      no parity bits
//  // bit14=x,      not used when parity is disabled
//  // bit13=0,      LSB first
//  // bit12=0,      8-bit data length
//  // bit11=0,      1 stop bit
//  // bits10-8=000, asynchronous UART mode
//  // bits7-6=11,   clock source to SMCLK
//  // bit5=0,       reject erroneous characters and do not set flag
//  // bit4=0,       do not set flag for break characters
//  // bit3=0,       not dormant
//  // bit2=0,       transmit data, not address (not used here)
//  // bit1=0,       do not transmit break (not used here)
//  // bit0=1,       hold logic in reset state while configuring
//  EUSCI_A0->CTLW0 = 0x00C1;
//                                 // set the baud rate
//                                 // N = clock/baud rate = 12,000,000/115,200 = 104.1667
//  EUSCI_A0->BRW = 104;           // UCBR = baud rate = int(N) = 104
//  EUSCI_A0->MCTLW &= ~0xFFF1;    // clear first and second modulation stage bit fields
//  P1->SEL0 |= 0x0C;
//  P1->SEL1 &= ~0x0C;             // configure P1.3 and P1.2 as primary module function
//  EUSCI_A0->CTLW0 &= ~0x0001;    // enable the USCI module
//  EUSCI_A0->IE &= ~0x000F;       // disable interrupts (transmit ready, start received, transmit empty, receive full)
//}
//
//
////-----------------------UART0_OutUDec-----------------------
//// Output a 32-bit number in unsigned decimal format
//// Input: 32-bit number to be transferred
//// Output: none
//// Variable format 1-10 digits with no space before or after
//void UART0_OutUDec(uint32_t n){
//// This function uses recursion to convert decimal number
////   of unspecified length as an ASCII string
//  if(n >= 10){
//    UART0_OutUDec(n/10);
//    n = n%10;
//  }
//  UART0_OutChar(n+'0'); /* n is between 0 and 9 */
//}

