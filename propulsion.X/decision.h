/* 
 * File:   decision.h
 * Author: nathdwek
 *
 * Created on 10 avril 2015, 19:08
 */

#ifndef DECISION_H
#define	DECISION_H

extern float accelerating;
extern float acceleratingAngular;
extern float goalDistance;
extern float goalTheta;
extern int goingStraight;
extern int rotating;

void resetStateVariables();

void stop();

void rotate(float angle);
void straight(float distance);
void interpretCommand(unsigned char command, unsigned char param);

#endif	/* DECISION_H */

