/* 
 * File:   peakDetector.h
 * Author: labo
 *
 * Created on 5 mai 2015, 11:29
 */

#ifndef PEAKDETECTOR_H
#define	PEAKDETECTOR_H

void initPeakDetector();
char peakDetect(int input[2]);//Renvoie un char dont le LSB vaut 1 ou 0 selon la
                              //présence de 900Hz et le LSB+1 vaut 1 ou 0 selon
                              //la présence de 1100Hz

#endif	/* PEAKDETECTOR_H */

