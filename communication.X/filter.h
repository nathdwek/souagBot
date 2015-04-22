/* 
 * File:   filter.h
 * Author: nathdwek
 *
 * Created on 22 April 2015, 14:44
 */

#ifndef FILTER_H
#define	FILTER_H

#define sectionOrder 3//n, n-1, n-2

//Filtre 900
//Section 1
extern const float a900_11;
extern const float a900_12;
extern const float b900_11;
extern const float b900_12;
extern const float g900_1;

//Section 2
extern const float a900_21;
extern const float a900_22;
extern const float b900_21;
extern const float b900_22;
extern const float g900_2;

//Section  3
extern const float a900_31;
extern const float a900_32;
extern const float b900_31;
extern const float b900_32;
extern const float g900_3;

//Section 4
extern const float a900_41;
extern const float a900_42;
extern const float b900_41;
extern const float b900_42;
extern const float g900_4;

extern float Xx1_900[sectionOrder], y1x2_900[sectionOrder],
             y2x3_900[sectionOrder], y3x4_900[sectionOrder],
             y4Y_900[sectionOrder];

//Filtre 1100
//Section 1
extern const float a1100_11;
extern const float a1100_12;
extern const float b1100_11;
extern const float b1100_12;
extern const float g1100_1;

//Section 2
extern const float a1100_21;
extern const float a1100_22;
extern const float b1100_21;
extern const float b1100_22;
extern const float g1100_2;

//Section  3
extern const float a1100_31;
extern const float a1100_32;
extern const float b1100_31;
extern const float b1100_32;
extern const float g1100_3;

//Section 4
extern const float a1100_41;
extern const float a1100_42;
extern const float b1100_41;
extern const float b1100_42;
extern const float g1100_4;

extern float Xx1_1100[sectionOrder], y1x2_1100[sectionOrder],
             y2x3_1100[sectionOrder], y3x4_1100[sectionOrder],
             y4Y_1100[sectionOrder];

void initFilter();
void filterNewSample(float sample, float returnArray[2]);

//TEST
void generateSineInput(int length, float frequency, int returnArray[]);
float rms(float array[],int arrayLength);

#endif	/* FILTER_H */
