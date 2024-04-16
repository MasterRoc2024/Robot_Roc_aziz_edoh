/* 
 * File:   UART.h
 * Author: TP-EO-5
 *
 * Created on 26 mars 2024, 10:25
 */

#ifndef UART_H
#define	UART_H

void InitUART(void);
void SendMessageDirect(unsigned char* message, int length);
void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void);

#endif	/* UART_H */

