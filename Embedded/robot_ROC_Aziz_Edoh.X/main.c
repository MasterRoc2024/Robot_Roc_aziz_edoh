#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <libpic30.h>
#include "ChipConfig.h"
#include "IO.h"
#include "PWM.h"
#include "timer.h"
#include "ADC.h"
#include "Robot.h"
#include "UART.h"
#include "CB_TX1.h"
#include "CB_RX1.h"
#include"UART_Protocol.h"
int ADCResult0;
int ADCResult1;
int ADCResult2;

int main(void) {
    /***************************************************************************************************/
    //Initialisation de l?oscillateur
    /****************************************************************************************************/
    InitOscillator();
    /****************************************************************************************************/
    // Configuration des entrées sorties
    /****************************************************************************************************/
    InitIO();

    InitTimer23();
    InitTimer1();
    InitADC1();
    InitPWM();

    InitUART();
    // PWMSetSpeed(-20, MOTEUR_DROIT);
    // PWMSetSpeed(-20, MOTEUR_GAUCHE);

    PWMUpdateSpeed();
    LED_BLANCHE = 1;
    LED_BLEUE = 1;
    LED_ORANGE = 1;

    /****************************************************************************************************/
    // Boucle Principale
    /****************************************************************************************************/
    while (1) {
        if (ADCIsConversionFinished() == 1) {

            ADCClearConversionFinishedFlag();
            unsigned int * result = ADCGetResult();
            float volts = ((float) result [2])* 3.3 / 4096 * 3.2;
            robotState.distanceTelemetreDroit = 34 / volts - 5;
            volts = ((float) result [1])* 3.3 / 4096 * 3.2;
            robotState.distanceTelemetreCentre = 34 / volts - 5;
            volts = ((float) result [0])* 3.3 / 4096 * 3.2;
            robotState.distanceTelemetreGauche = 34 / volts - 5;
            unsigned char payloadtelemetre[] = {robotState.distanceTelemetreGauche, robotState.distanceTelemetreCentre, robotState.distanceTelemetreDroit};
            UartEncodeAndSendMessage(0x0030, 3, payloadtelemetre);
            __delay32(40000000);

        }
        //SendMessageDirect((unsigned char*) "bonjour", 7);
        //__delay32(40000000);
        /*SendMessage((unsigned char*) "bonjour", 7);
        */
//        int i;
//        for (i = 0; i < CB_RX1_GetDataSize(); i++) {
//            unsigned char c = CB_RX1_Get();
//            SendMessage(&c, 1);
//        }
//        __delay32(1000);
//        unsigned char payload[] = {'B', 'o', 'n', 'j', 'o', 'u', 'r'};
//        UartEncodeAndSendMessage(0x0080, 7, payload);
//        __delay32(40000000);
    } // fin main
}