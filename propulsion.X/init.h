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
extern int REGUL_FCY;
extern int leftSpins;
extern int rightSpins;
extern float kp;
extern float angularKp;
extern float zoneMorteLeft;
extern float zoneMorteRight;
extern float cmPerTick;
extern float distanceConsigne;
extern float thetaConsigne;
extern int accelerating;
extern int acceleratingAngular;
extern float acceleration;
extern float angularAcceleration;
extern float speed;
extern float angularSpeed;
extern float maxSpeed;
extern float maxAngularSpeed;

#endif	/* INIT_H */
