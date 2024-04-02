/* 
 * File:   CB_TX1.h
 * Author: TP-EO-5
 *
 * Created on 2 avril 2024, 09:05
 */

#ifndef CB_TX1_H
#define	CB_TX1_H
void SendMessage(unsigned char* message, int length);
void CB_TX1_Add(unsigned char value);
void __attribute__((interrupt, no_auto_psv)) _U1TXInterrupt(void);
unsigned char CB_TX1_IsTranmitting(void);
int CB_TX1_GetDataSize(void);
int CB_TX1_GetRemainingSize(void);
void SendOne();

#endif	/* CB_TX1_H */

