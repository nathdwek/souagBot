/* 
 * File:   filter.h
 * Author: nathdwek
 *
 * Created on 22 April 2015, 14:44
 */

#ifndef FILTER_H
#define	FILTER_H
//#define FILTER_DBG

void initFilter();
void filterNewSample(unsigned int sample, int returnArray[2]);

#ifdef FILTER_DBG
void generateSineInput(int length, float frequency, int returnArray[]);
float rms(float array[],int arrayLength);
#endif

#endif	/* FILTER_H */
