#include "uart_print.h"
#include "driverlib/eusci.h"


// Other Stuff
//------------UART0_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
void UART0_OutChar(char letter)
{
  while((EUSCI_A0->IFG&0x02) == 0);
  EUSCI_A0->TXBUF = letter;
}

//------------UART0_OutString------------
// Output String (NULL termination)
// Input: pointer to a NULL-terminated string to be transferred
// Output: none
void UART0_OutString(char *pt)
{
  while(*pt){
    UART0_OutChar(*pt);
    pt++;
  }
}



//------------UART0_Init------------
// Initialize the UART for 115,200 baud rate (assuming 12 MHz SMCLK clock),
// 8 bit word length, no parity bits, one stop bit
// Input: none
// Output: none
void UART0_Init(void){
  EUSCI_A0->CTLW0 = 0x0001;                   // hold the USCI module in reset mode
  // bit15=0,      no parity bits
  // bit14=x,      not used when parity is disabled
  // bit13=0,      LSB first
  // bit12=0,      8-bit data length
  // bit11=0,      1 stop bit
  // bits10-8=000, asynchronous UART mode
  // bits7-6=11,   clock source to SMCLK
  // bit5=0,       reject erroneous characters and do not set flag
  // bit4=0,       do not set flag for break characters
  // bit3=0,       not dormant
  // bit2=0,       transmit data, not address (not used here)
  // bit1=0,       do not transmit break (not used here)
  // bit0=1,       hold logic in reset state while configuring
  EUSCI_A0->CTLW0 = 0x00C1;
                                 // set the baud rate
                                 // N = clock/baud rate = 12,000,000/115,200 = 104.1667
  EUSCI_A0->BRW = 104;           // UCBR = baud rate = int(N) = 104
  EUSCI_A0->MCTLW &= ~0xFFF1;    // clear first and second modulation stage bit fields
  P1->SEL0 |= 0x0C;
  P1->SEL1 &= ~0x0C;             // configure P1.3 and P1.2 as primary module function
  EUSCI_A0->CTLW0 &= ~0x0001;    // enable the USCI module
  EUSCI_A0->IE &= ~0x000F;       // disable interrupts (transmit ready, start received, transmit empty, receive full)
}


//-----------------------UART0_OutUDec-----------------------
// Output a 32-bit number in unsigned decimal format
// Input: 32-bit number to be transferred
// Output: none
// Variable format 1-10 digits with no space before or after
void UART0_OutUDec(uint32_t n){
// This function uses recursion to convert decimal number
//   of unspecified length as an ASCII string
  if(n >= 10){
    UART0_OutUDec(n/10);
    n = n%10;
  }
  UART0_OutChar(n+'0'); /* n is between 0 and 9 */
}

