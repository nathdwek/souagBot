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
const int a900_11 = -19027;
const int a900_12 = 9813;
const int b900_11 = 0;
const int b900_12 = -10000;
const int g900_1 = 93;

//Filtre centré autour de 1100
//Section 1
const int a1100_11 = -18642;
const int a1100_12 = 9813;
const int b1100_11 = 0;
const int b1100_12 = -10000;
const int g1100_1 = 93;

//X:entrée "générale"
//Y:sortie "générale"
//xi:entrée de la section i
//yi:sortie de la section i
//chaque vecteur est deux choses à la fois.
int x[sectionOrder];

long y_900[sectionOrder], y_1100[sectionOrder];

void initFilter(void){
    //Filtre causal
    int i;
    for (i = 0; i<sectionOrder;i++){
        x[i] = 0;
        y_1100[i] = 0;
        y_900[i] = 0;
    }
}

void shiftArrays(void){//Explicite
    int i;
    for (i=0;i<2;i++){
        x[2-i] = x[1-i];
        
        y_900[2-i] = y_900[1-i];
        y_1100[2-i] = y_1100[1-i];
    }
}

long recurrence(long a1, long a2, long gain,
                 int arrayX[3], long arrayY[3]){
    //Recurrence ordre 2 normalisée
    //Opti: b1 et b2 sont toujours (0,1)
    return (gain*(arrayX[0]-arrayX[2])-a1*arrayY[1]-a2*arrayY[2])/10000;
    //Division par 10000 pour revenir sur du int8
}

void filterNewSample(unsigned int sample, int returnArray[2]){
    shiftArrays();
    x[0] = sample;
    
    y_900[0] = recurrence(a900_11,a900_12,g900_1,x,y_900);
    y_1100[0] = recurrence(a1100_11,a1100_12,g1100_1,x,y_1100);
    
    returnArray[0] = y_900[0];
    returnArray[1] = y_1100[0];
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
