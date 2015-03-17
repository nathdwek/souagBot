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
extern float kp;
extern float ticksPerMeter;
extern float accelConsigne[80];
extern float leftConsigne;
extern float rightConsigne;
extern int consigneIndex;
extern int accelerating;
extern int leftDistance;
extern int rightDistance;

#endif	/* INIT_H */
