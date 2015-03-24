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
extern float kpLeft;
extern float kpRight;
extern float zoneMorteLeft;
extern float zoneMorteRight;
extern float cmPerTick;
extern float leftConsigne;
extern float rightConsigne;
extern int acceleratingLeft;
extern int acceleratingRight;
extern float a;
extern float leftDistance;
extern float rightDistance;
extern float leftSpeed;
extern float rightSpeed;
extern float maxSpeed;

#endif	/* INIT_H */
