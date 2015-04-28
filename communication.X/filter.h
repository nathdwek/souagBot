/* 
 * File:   filter.h
 * Author: nathdwek
 *
 * Created on 22 April 2015, 14:44
 */

#ifndef FILTER_H
#define	FILTER_H
void initFilter();
void filterNewSample(unsigned int sample, float returnArray[2]);

//TEST
void generateSineInput(int length, float frequency, int returnArray[]);
float rms(float array[],int arrayLength);

#endif	/* FILTER_H */
