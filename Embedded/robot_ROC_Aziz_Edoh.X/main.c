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
        if (ADCIsConversionFinished() == 1){
           
            ADCClearConversionFinishedFlag();
            unsigned int * result = ADCGetResult();
            float volts = ((float) result [2])* 3.3 / 4096 * 3.2;
            robotState.distanceTelemetreDroit = 34 / volts - 5;
            volts = ((float) result [1])* 3.3 / 4096 * 3.2;
            robotState.distanceTelemetreCentre = 34 / volts - 5;
            volts = ((float) result [0])* 3.3 / 4096 * 3.2;
            robotState.distanceTelemetreGauche = 34 / volts - 5;
           
            
        }
     //SendMessageDirect((unsigned char*) "bonjour", 7);
     //__delay32(40000000);

    } // fin main
}