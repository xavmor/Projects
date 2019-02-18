


#ifndef uart_print_h
#define uart_print_h

#include "stdint.h"

/**
 * @details   Initialize EUSCI_A0 for UART operation
 * @details   115,200 baud rate (assuming 12 MHz SMCLK clock),
 * @details   8 bit word length, no parity bits, one stop bit
 * @param  none
 * @return none
 * @note   assumes 48 MHz bus and 12 MHz SMCLK
 * @brief  Initialize EUSCI A0
 */
void UART0_Init(void);

/**
 * @details   Transmit a character to EUSCI_A0 UART
 * @details   Busy-wait synchronization,
 * @details   blocking, wait for UART to be ready
 * @param  letter is the ASCII code for key to send
 * @return none
 * @note   UART0_Init must be called once prior
 * @brief  Transmit byte out of MSP432
 */
void UART0_OutChar(char letter);

/**
 * @details   Transmit a string to EUSCI_A0 UART
 * @param  pt is pointer to null-terminated ASCII string to be transferred
 * @return none
 * @note   UART0_Init must be called once prior
 * @brief  Transmit string out of MSP432
 */
void UART0_OutString(char *pt);


/**
 * @details   Transmit a number as ASCII characters in unsigned decimal format
 * @details   Variable format 1-10 digits with no space before or after
 * @param  n is a unsigned 32-bit number to be transferred
 * @return none
 * @note   UART0_Init must be called once prior
 * @brief  Transmit an unsigned number out of MSP432
 */
void UART0_OutUDec(uint32_t n);


#endif
