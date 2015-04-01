/* 
 * File:   init.h
 * Author: nathdwek
 *
 * Created on 04 March 2015, 21:59
 */

#ifndef INIT_H
#define	INIT_H

void configPWM();

void configQEI();

void configRegul();

extern int leftSpins;
extern int rightSpins;
extern float oldRightDistance;
extern float oldLeftDistance;
extern float theta;

extern float distanceConsigne;
extern float thetaConsigne;
extern float accelerating;
extern float acceleratingAngular;
extern float speedConsigne;
extern float angularSpeedConsigne;
extern float goalDistance;
extern float goalTheta;

#endif	/* INIT_H */
