/* 
 * File:   peakDetector.c
 * Author: labo
 *
 * Created on 5 mai 2015, 11:23
 */
#include "globals.h"

long filterBuffer900[];
long filterBuffer1100[];

int iter900;
int iter1100;

int maxIter900;
int maxIter1100;

long max900;
long max1100;

char detected900;
char detected1100;

void initPeakDetector(){
    max900 = 0;
    max1100 = 0;
    maxIter900 = FS/900;
    maxIter1100 = FS/1100;
}

char peakDetect(long input[2]){
    detected900 = peakDetectOneFreq(filterBuffer900, &iter900, &max900, input, maxIter900);
    detected1100 = peakDetectOneFreq(filterBuffer1100, &iter1100, &max1100, input, maxIter1100);
}

long searchNewMax(long filterBuffer[], int size){
    int i = 0;
    long currentMax = 0;
    for (i;i<size;i++){
        if (filterBuffer[i] > currentMax){
            currentMax = filterBuffer[i];
        }
    }
    return currentMax;
}

char peakDetectOneFreq(long filterBuffer, int * iter, long * max, long input, int maxIter, long minValue){
    if ((filterBuffer[*iter] == *max) && (input < filterBuffer[*iter])){
        filterBuffer[*iter] = input;
        *max = searchNewMax(filterBuffer, maxIter);
    }else{
        filterBuffer[*iter] = input;
        if (input > *max){
            *max = input;
        }
    }
    *iter++;
    if (*iter == maxIter){
        *iter = 0;
    }
    return *max > minValue;
}
