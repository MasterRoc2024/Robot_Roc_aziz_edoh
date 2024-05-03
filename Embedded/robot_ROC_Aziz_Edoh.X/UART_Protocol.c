#include <xc.h>
#include "UART_Protocol.h"
#include"UART.h"

unsigned char UartCalculateChecksum(int msgFunction,
int msgPayloadLength, unsigned char* msgPayload)
{
//Fonction prenant entree la trame et sa longueur pour calculer le checksum
unsigned char checksum = 0;
checksum ^= 0xFE;
checksum ^= (unsigned char)(msgFunction >> 8);
checksum ^= (unsigned char)(msgFunction >> 0);
checksum ^= (unsigned char)(msgPayloadLength >> 8);
checksum ^= (unsigned char)(msgPayloadLength >> 0);
for (int i = 0; i < msgPayloadLength; i++)
{
    checksum ^= msgPayload[i];
}
return checksum;
}

void UartEncodeAndSendMessage(int msgFunction,int msgPayloadLength, unsigned char* msgPayload)
{
//Fonction d?encodage et d?envoi d?un message
    unsigned char checksum = UartCalculateChecksum(msgFunction, msgPayloadLength, msgPayload);
    unsigned char messageComplet[msgPayloadLength + 6];
    int pos = 0;
    messageComplet[pos++] = 0xFE;
    messageComplet[pos++] = (unsigned char)(msgFunction >> 8);
    messageComplet[pos++] = (unsigned char)(msgFunction >> 0);
    messageComplet[pos++] = (unsigned char)(msgPayloadLength >> 8);
    messageComplet[pos++] = (unsigned char)(msgPayloadLength >> 0);
    for (int i = 0;i < msgPayloadLength;i++)
    {
        messageComplet[pos++] = msgPayload[i];
    }
    messageComplet[pos++] = checksum;
    SendMessageDirect(messageComplet, msgPayloadLength+6);
}


unsigned char StateReception;
unsigned char msgDecodedFunction = 0;
int msgDecodedPayloadLength = 0;
int msgDecodedPayloadIndex = 0;
unsigned char receivedChecksum = 0;
unsigned char msgDecodedPayload[msgDecodedPayloadLength];
void UartDecodeMessage(unsigned char c)
{
    //Fonction prenant en entree un octet et servant a reconstituer les trames
    switch (StateReception)
    {
        case WAITING:
            if (c == 0xFE){
                StateReception = FUNCTION_MSB;
               
            }
            break;
        case FUNCTION_MSB:
           
           msgDecodedFunction = (c << 8);
            StateReception = FUNCTION_LSB;
        break;
        case FUNCTION_LSB:
           msgDecodedFunction |= c ;
           StateReception = PAYLOADLENGTH_MSB;
        break;
        case PAYLOADLENGTH_MSB:
            msgDecodedPayloadLength = (c << 8);
            StateReception = PAYLOADLENGTH_LSB;
        break;
        case PAYLOADLENGTH_LSB:
            msgDecodedPayloadLength |= c ;
            if (msgDecodedPayloadLength == 0)
            {
                StateReception = CHECKSUM;
            }
            else
            {
                
               StateReception = PAYLOAD;
            }
        break;
        case PAYLOAD:
            msgDecodedPayload[msgDecodedPayloadIndex] = c;
            msgDecodedPayloadIndex++;
            if(msgDecodedPayloadIndex >= msgDecodedPayloadLength){
            StateReception = CHECKSUM;
            }
                
            break;
        case CHECKSUM:
            receivedChecksum = c;
            unsigned char calculatedChecksum = UartCalculateChecksum(msgDecodedFunction, msgDecodedPayloadLength, msgDecodedPayload) ;
            if (calculatedChecksum == receivedChecksum)
            {
                //Success, on a un message valide
                
            }

            else
            {
                

            }
             StateReception = WAITING;
        break;
        default:
           StateReception = WAITING;
            break;
    }
}

//
//void UartProcessDecodedMessage(unsigned char function,
//unsigned char payloadLength, unsigned char payload[])
//{
////Fonction éappele èaprs le édcodage pour éexcuter l?action
////correspondant au message çreu
//switch (msgFunction)
//{
//case SET_ROBOT_STATE:
//    SetRobotState(msgPayload[0]);
//break;
//case SET_ROBOT_MANUAL_CONTROL:
//SetRobotAutoControlState(msgPayload[0]);
//break;
//default:
//break;
//}
//}
////*************************************************************************/
////Fonctions correspondant aux messages
////*************************************************************************/
//
