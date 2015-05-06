/* 
 * File:   peakDetector.c
 * Author: labo
 *
 * Created on 5 mai 2015, 11:23
 */
#include "globals.h"

#define maxIter900 30
#define maxIter1100 25


int filterBuffer900[maxIter900];
int filterBuffer1100[maxIter1100];

int iter900;
int iter1100;

int max900;
int max1100;

int minValue900 = 250;
int minValue1100 = 250;

char detected900;
char detected1100;

void initPeakDetector(){
    max900 = 0;
    max1100 = 0;

    iter900 = 0;
    iter1100 = 0;

    int i;
    for (i = 0; i< maxIter900; i++){
        filterBuffer900[i] = 0;
    }
    for (i = 0; i< maxIter1100; i++){
        filterBuffer1100[i] = 0;
    }
}

int searchNewMax(int filterBuffer[], int size){
    int i;
    int currentMax = 0;
    for (i = 0;i<size;i++){
        if (filterBuffer[i] > currentMax){
            currentMax = filterBuffer[i];
        }
    }
    return currentMax;
}

char peakDetectOneFreq(int * filterBuffer, int * iter, int * max, int input,
                       int maxIter, int minValue){
    if ((filterBuffer[*iter] == *max) && (input < filterBuffer[*iter])){
        filterBuffer[*iter] = input;
        *max = searchNewMax(filterBuffer, maxIter);
    }else{
        filterBuffer[*iter] = input;
        if (input > *max){
            *max = input;
        }
    }
    *iter = (*iter)+1;
    if (*iter == maxIter){
        *iter = 0;
    }
    return *max > minValue;
}

char peakDetect(int input[2]){
    detected900 = peakDetectOneFreq(filterBuffer900, &iter900, &max900,
                                    input[0], maxIter900,minValue900);
    detected1100 = peakDetectOneFreq(filterBuffer1100, &iter1100, &max1100,
                                     input[1], maxIter1100,minValue1100);
    return detected900 | 2*detected1100;
}

