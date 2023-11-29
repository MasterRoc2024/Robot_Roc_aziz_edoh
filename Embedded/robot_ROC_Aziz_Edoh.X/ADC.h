/* 
 * File:   ADC.h
 * Author: TP-EO-5
 *
 * Created on 29 novembre 2023, 10:17
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif
    
void InitADC1(void);
void ADC1StartConversionSequence();
unsigned int * ADCGetResult(void);
unsigned char ADCIsConversionFinished(void);
void ADCClearConversionFinishedFlag(void);



#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

