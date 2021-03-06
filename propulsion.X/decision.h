/* 
 * File:   decision.h
 * Author: nathdwek
 *
 * Created on 10 avril 2015, 19:08
 */

#ifndef DECISION_H
#define	DECISION_H

extern float acceleration;
extern float angularAcceleration;
extern char goalDistance;
extern char decelerationDistance;
extern float goalTheta;
extern float decelerationTheta;
extern char goingStraight;
extern char rotating;

void resetStateVariables();
void stop();

void rotate(char angleInDegrees, char way);
void straight(char distance);

void interpretCommand(unsigned char command, unsigned char param);

#endif	/* DECISION_H */

