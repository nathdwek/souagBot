#include "globals.h"
#include "filter.h"
#ifdef FILTER_DBG
#include "math.h"//Remove for production
#endif

#define sectionOrder 3 //n n-1 n-2

//COEFFICIENTS DES FILTRES PB NUMERIQUES
//Les filtres sont normalisés: ai0=bi0=1
//Coefficients int16 = 10000*coeff de matlab

//Filtre centré autour de 900
//Section 1
const int a900_11 = -19039;
const int a900_12 = 9865;
const int g900_1 = 94;

//Section 2
const int a900_21 = -19119;
const int a900_22 = 9871;
const int g900_2 = 94;

//Filtre centré autour de 1100
//Section 1
const int a1100_11 = -18646;
const int a1100_12 = 9865;
const int g1100_1 = 94;

//Section 2
const int a1100_21 = -18740;
const int a1100_22 = 9870;
const int g1100_2 = 94;

//X:entrée "générale"
//Y:sortie "générale"
//xi:entrée de la section i
//yi:sortie de la section i
//chaque vecteur est deux choses à la fois.
long Xx1[sectionOrder];

long y1x2_900[sectionOrder], y1x2_1100[sectionOrder], y2Y_900[sectionOrder], y2Y_1100[sectionOrder];

void initFilter(void){
    //Filtre causal
    int i;
    for (i = 0; i<sectionOrder;i++){
        Xx1[i] = 0;

        y1x2_1100[i] = 0;
        y1x2_900[i] = 0;

        y2Y_1100[i] = 0;
        y2Y_900[i] = 0;
    }
}

void shiftArrays(void){//Explicite
    int i;
    for (i=0;i<2;i++){
        Xx1[2-i] = Xx1[1-i];

        y1x2_900[2-i] = y1x2_900[1-i];
        y1x2_1100[2-i] = y1x2_1100[1-i];

        y2Y_900[2-i] = y2Y_900[1-i];
        y2Y_1100[2-i] = y2Y_1100[1-i];
    }
}

long recurrence(long a1, long a2, long gain,
                 long arrayX[3], long arrayY[3]){
    //Recurrence ordre 2 normalisée
    //Opti: b0 et b2 sont toujours (0,1)
    return (gain*(arrayX[0]-arrayX[2])-a1*arrayY[1]-a2*arrayY[2])/9825;
    //Division par 10000 pour revenir sur du int16
}

void filterNewSample(unsigned int sample, int returnArray[2]){
    shiftArrays();
    Xx1[0] = sample;

    y1x2_900[0] = recurrence(a900_11,a900_12,g900_1,Xx1,y1x2_900);
    y1x2_1100[0] = recurrence(a1100_11,a1100_12,g1100_1,Xx1,y1x2_1100);

    y2Y_900[0] = recurrence(a900_21,a900_22,g900_2,y1x2_900,y2Y_900);
    y2Y_1100[0] = recurrence(a1100_21,a1100_22,g1100_2,y1x2_1100,y2Y_1100);
    
    returnArray[0] = y2Y_900[0];
    returnArray[1] = y2Y_1100[0];
}

#ifdef FILTER_DBG
//NEEDS math.h
float rms(float array[],int arrayLength){
    int i;
    float rms = 0;
    for (i=1;i<arrayLength;i++){
        rms = rms + array[i]*array[i];
    }
    rms = rms/arrayLength;
    return sqrtf(rms);
}

void generateSineInput(int length,float frequency, int returnArray[]){
    int i;
    float sample;
    for (i=0;i<length;i++){
        sample = sin(2.0*PI*frequency*i/FS);
        returnArray[i] = 1000*sample;
    }
}
#endif
