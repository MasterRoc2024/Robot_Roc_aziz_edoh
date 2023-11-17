/* 
 * File:   PWM.h
 * Author: TP-EO-5
 *
 * Created on 23 octobre 2023, 12:10
 */

#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif
void PWMSetSpeed(float vitesseEnPourcents);
void InitPWM(void);



#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

