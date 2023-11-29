/* 
 * File:   PWM.h
 * Author: TP-EO-5
 *
 * Created on 23 octobre 2023, 12:10
 */

#ifndef PWM_H
#define	PWM_H
#define MOTEUR_DROIT 1
#define MOTEUR_GAUCHE 0

//void PWMSetSpeed(float , int);
void InitPWM(void);
void PWMUpdateSpeed() ;
void PWMSetSpeedConsigne(float vitesseEnPourcents, char moteur) ;

#endif	/* PWM_H */

