/* 
 * File:   regul.h
 * Author: nathdwek
 *
 * Created on 10 avril 2015, 19:02
 */

#ifndef REGUL_H
#define	REGUL_H

//coeffs de la régul
extern float kp;
extern float angularKp;
//Consignes. Exposées car reset par decision.c
extern float speedConsigne;
extern float angularSpeedConsigne;
extern float distanceConsigne;
extern float thetaConsigne;

void configRegul(void);

#endif	/* REGUL_H */

