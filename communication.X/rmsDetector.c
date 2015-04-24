#include <p33FJ128GP802.h>
#include "globals.h"
#include "rmsDetector.h"


int sampleNo;
float rmsValue_900;
float rmsValue_1100;
char bitEnded;
const int samplesPerBit = FS/FSYMBOL;

void initRmsDetector(){
    sampleNo = 0;
    rmsValue_900 = 0;
    rmsValue_1100 = 0;
}

char rmsDetect(float filteredSample[2],char detected[2]){
    sampleNo++;
    rmsValue_900 += filteredSample[0]*filteredSample[0];
    rmsValue_1100 += filteredSample[1]*filteredSample[1];
    if (sampleNo < samplesPerBit){
        bitEnded = 0;
    }else{
        rmsValue_900 /= samplesPerBit;
        rmsValue_1100 /= samplesPerBit;
        bitEnded = 1;
        detected[0] = rmsValue_900 > MIN_RMS_VALUE;
        detected[1] = rmsValue_1100 > MIN_RMS_VALUE;
    }
    return bitEnded;
}
