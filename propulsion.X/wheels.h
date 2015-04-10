/* 
 * File:   wheels.h
 * Author: nathdwek
 *
 * Created on 10 avril 2015, 19:08
 */

#ifndef WHEELS_H
#define	WHEELS_H

extern int leftSpins;
extern int rightSpins;
extern float oldRightDistance;
extern float oldLeftDistance;
extern float theta;

void configPWM();
void configQEI();

void resetMotors();
void resetPositionVariables();

float readDistances();
#endif	/* WHEELS_H */

