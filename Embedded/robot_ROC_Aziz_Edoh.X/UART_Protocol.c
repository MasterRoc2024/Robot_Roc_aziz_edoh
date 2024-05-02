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
 //   SendMessageDirect(messageComplet, 0, msgPayloadLength+6);
}


//
// enum StateReception
//{
//    Waiting,
//    FunctionMSB,
//    FunctionLSB,
//    PayloadLengthMSB,
//    PayloadLengthLSB,
//    Payload,
//    CheckSum
//}
//StateReception rcvState = StateReception.Waiting;
//int msgDecodedFunction = 0;
//int msgDecodedPayloadLength = 0;
//unsigned char msgDecodedPayload[] ;
//int msgDecodedPayloadIndex = 0;
//
//void UartDecodeMessage(unsigned char c)
//{
//    //Fonction prenant en entree un octet et servant a reconstituer les trames
//    switch (rcvState)
//    {
//        case StateReception.Waiting:
//            if (c== 0XFE){
//                rcvState = StateReception.FunctionMSB;
//               
//            }
//            break;
//        case StateReception.FunctionMSB:
//            msgDecodedFunction = (c << 8);
//            rcvState = StateReception.FunctionLSB;
//        break;
//        case StateReception.FunctionLSB:
//           msgDecodedFunction |= c ;
//            rcvState = StateReception.PayloadLengthMSB;
//        break;
//        case StateReception.PayloadLengthMSB:
//            msgDecodedPayloadLength = (c << 8);
//            rcvState = StateReception.PayloadLengthLSB;
//        break;
//        case StateReception.PayloadLengthLSB:
//            msgDecodedPayloadLength |= c ;
//            if (msgDecodedPayloadLength == 0)
//            {
//                rcvState = StateReception.CheckSum;
//            }
//            else
//            {
//                unsigned char msgDecodedPayload[msgDecodedPayloadLength];
//                msgDecodedPayloadIndex = 0;
//                rcvState = StateReception.Payload;
//            }
//        break;
//        case StateReception.Payload:
//            msgDecodedPayload[msgDecodedPayloadIndex] = c;
//            msgDecodedPayloadIndex++;
//            if(msgDecodedPayloadIndex >= msgDecodedPayloadLength)
//                rcvState = StateReception.CheckSum;
//            break;
//        case StateReception.CheckSum:
//             receivedChecksum = c;
//            unsigned char calculatedChecksum = UartCalculateChecksum(msgDecodedFunction, msgDecodedPayloadLength, msgDecodedPayload) ;
//            if (calculatedChecksum == receivedChecksum)
//            {
//                //Success, on a un message valide
//                printf("message reçu");
//            }
//
//            else
//            {
//                printf("Erreur dans la trame!!!");
//
//            }
//            rcvState = StateReception.Waiting;
//        break;
//        default:
//            rcvState = StateReception.Waiting;
//            break;
//    }
//}
//
//
//void UartProcessDecodedMessage(int function,int payloadLength, unsigned char* payload)
//{
////Fonction appelee apres le decodage pour executer l?action
////correspondant au message recu
//...
//}
////*************************************************************************/
////Fonctions correspondant aux messages
////*************************************************************************/
//
