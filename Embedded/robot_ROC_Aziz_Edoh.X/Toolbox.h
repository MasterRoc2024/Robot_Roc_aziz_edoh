/* 
 * File:   Toolbox.h
 * Author: TP-EO-5
 *
 * Created on 23 octobre 2023, 12:08
 */

#ifndef TOOLBOX_H
#define	TOOLBOX_H
#define PI 3.141592653589793
#ifdef	__cplusplus
extern "C" {
    
#endif
float Abs(float value);
float Max(float value, float value2);
float Min(float value, float value2);
float LimitToInterval(float value, float lowLimit, float highLimit);
float RadianToDegree(float value);
float DegreeToRadian(float value);



#ifdef	__cplusplus
}
#endif

#endif	/* TOOLBOX_H */

