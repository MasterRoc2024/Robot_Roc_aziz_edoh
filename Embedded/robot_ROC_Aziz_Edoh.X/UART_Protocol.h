/* 
 * File:   UART_Protocol.h
 * Author: TP-EO-5
 *
 * Created on 2 mai 2024, 15:05
 */

#ifndef UART_PROTOCOL_H
#define	UART_PROTOCOL_H
#define SET_ROBOT_STATE 0x0051
#define SET_ROBOT_MANUAL_CONTROL 0x0052
#define WAITING 0
#define FUNCTION_MSB 1
#define FUNCTION_LSB 2
#define PAYLOADLENGTH_MSB 3
#define PAYLOADLENGTH_LSB 4
#define PAYLOAD 5
#define CHECKSUM 6


void UartEncodeAndSendMessage(int msgFunction,int msgPayloadLength, unsigned char* msgPayload);
unsigned char UartCalculateChecksum(int msgFunction,int msgPayloadLength, unsigned char* msgPayload);
void UartDecodeMessage(unsigned char c);
void UartProcessDecodedMessage(int function,int payloadLength, unsigned char* payload);
#endif	/* UART_PROTOCOL_H */

