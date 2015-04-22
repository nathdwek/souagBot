#include "globals.h"
#include "filter.h"
#include "math.h"//Remove for production

//COEFFICIENTS DES FILTRES PB NUMERIQUES
//Les filtres sont normalisés: ai0=bi0=1

//Filtre centré autour de 900
//Section 1
const float a900_11 = -1.951975278015571024781138476100750267506;
const float a900_12 =  0.997074853285093487542667389789130538702;
const float b900_11 = 0;
const float b900_12 = -1;
const float g900_1 = 0.003760448777517376439671892285332432948;

//Section 2
const float a900_21 = -1.954956755552087255267679211101494729519;
const float a900_22 =  0.997168937992165327344196157355327159166;
const float b900_21 = 0;
const float b900_22 = -1;
const float g900_2 = 0.003760448777517376439671892285332432948;

//Section  3
const float a900_31 = -1.948874945990294094144701375626027584076;
const float a900_32 =  0.993018819830499221978925561415962874889;
const float b900_31 = 0;
const float b900_32 = -1;
const float g900_3 = 0.003752830012794396152830955770696164109;

//Section 4
const float a900_41 = -1.950161054069266430843754278612323105335;
const float a900_42 =  0.993112545431724336175705047935480251908;
const float b900_41 = 0;
const float b900_42 = -1;
const float g900_4 = 0.003752830012794396152830955770696164109;

float Xx1_900[sectionOrder], y1x2_900[sectionOrder], y2x3_900[sectionOrder],
      y3x4_900[sectionOrder], y4Y_900[sectionOrder];


//Filtre centré autour de 1100
//Section 1
const float a1100_11 = -1.92920300573017611256432246591430157423;
const float a1100_12 =  0.996426421868306433360373830510070547462;
const float b1100_11 = 0;
const float b1100_12 = -1;
const float g1100_1 = 0.004594628512362023374515640483650713577;

//Section 2
const float a1100_21 = -1.933612702419810647214148957573343068361;
const float a1100_22 =  0.996540492147176215631532159022754058242;
const float b1100_21 = 0;
const float b1100_22 = -1;
const float g1100_2 = 0.004594628512362023374515640483650713577;

//Section  3
const float a1100_31 = -1.925702738601609897983735208981670439243;
const float a1100_32 =  0.991474476782913560768406568968202918768;
const float b1100_31 = 0;
const float b1100_32 = -1;
const float g1100_3 = 0.004583266011817110560655486040104733547;

//Section 4
const float a1100_41 = -1.927589029099253448151785050868056714535;
const float a1100_42 =  0.991588010100639016819457083329325541854;
const float b1100_41 = 0;
const float b1100_42 = -1;
const float g1100_4 = 0.004583266011817110560655486040104733547;

float Xx1_1100[sectionOrder], y1x2_1100[sectionOrder], y2x3_1100[sectionOrder],
      y3x4_1100[sectionOrder], y4Y_1100[sectionOrder];


void initFilter(void){
    int i;
    for (i = 0; i<sectionOrder;i++){
        Xx1_900[i] = 0;
        y1x2_900[i] = 0;
        y2x3_900[i] = 0;
        y3x4_900[i] = 0;
        y4Y_900[i] = 0;
        Xx1_1100[i] = 0;
        y1x2_1100[i] = 0;
        y2x3_1100[i] = 0;
        y3x4_1100[i] = 0;
        y4Y_1100[i] = 0;
    }
}

void shiftArrays(void){
    int i;
    for (i=0;i<2;i++){
        Xx1_900[2-i] = Xx1_900[1-i];
        y1x2_900[2-i] = y1x2_900[1-i];
        y2x3_900[2-i] = y2x3_900[1-i];
        y3x4_900[2-i] = y3x4_900[1-i];
        y4Y_900[2-i] = y4Y_900[1-i];
        Xx1_1100[2-i] = Xx1_1100[1-i];
        y1x2_1100[2-i] = y1x2_1100[1-i];
        y2x3_1100[2-i] = y2x3_1100[1-i];
        y3x4_1100[2-i] = y3x4_1100[1-i];
        y4Y_1100[2-i] = y4Y_1100[1-i];
    }
}

float recurrence(float a1, float a2, float b1, float b2, float gain,
                 float arrayX[3], float arrayY[3]){
    //Recurrence ordre 2 normalisée
    return gain*(arrayX[0]+b1*arrayX[1]+b2*arrayX[2])-a1*arrayY[1]-a2*arrayY[2];
}

void filterNewSample(float sample, float returnArray[2]){
    shiftArrays();
    Xx1_900[0] = sample;
    y1x2_900[0] = recurrence(a900_11,a900_12,b900_11,b900_12,g900_1,Xx1_900,y1x2_900);
    y2x3_900[0] = recurrence(a900_21,a900_22,b900_21,b900_22,g900_2,y1x2_900,y2x3_900);
    y3x4_900[0] = recurrence(a900_31,a900_32,b900_31,b900_32,g900_3,y1x2_900,y2x3_900);
    y4Y_900[0] = recurrence(a900_41,a900_42,b900_41,b900_42,g900_4,y3x4_900,y4Y_900);

    Xx1_1100[0] = sample;
    y1x2_1100[0] = recurrence(a1100_11,a1100_12,b1100_11,b1100_12,g1100_1,Xx1_1100,y1x2_1100);
    y2x3_1100[0] = recurrence(a1100_21,a1100_22,b1100_21,b1100_22,g1100_2,y1x2_1100,y2x3_1100);
    y3x4_1100[0] = recurrence(a1100_31,a1100_32,b900_31,b1100_32,g1100_3,y1x2_1100,y2x3_1100);
    y4Y_1100[0] = recurrence(a1100_41,a1100_42,b1100_41,b1100_42,g1100_4,y3x4_1100,y4Y_1100);

    returnArray[0] = y4Y_900[0];
    returnArray[1] = y4Y_1100[0];
}

//TEST
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

