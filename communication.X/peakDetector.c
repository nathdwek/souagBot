/* 
 * File:   peakDetector.c
 * Author: labo
 *
 * Created on 5 mai 2015, 11:23
 */
#include "globals.h"

/*Ce bloc garde en mémoire les échantillons correspondant à une période de 900
 *ou 1100Hz et cherche parmi ceux-ci le maximum (Il correspond forcément à une
 *valeur élevée du sinus si celui-ci est présent vu qu'on garde une période
 *entière).Si ce maximum est supérieur à une certaine valeur, on considère
 *que la fréquence est présente*/

//Nombre d'échantillons à garder pour chaque fréquence: FS/f
#define maxIter900 23
#define maxIter1100 19

//Les arrays où on sauve les samples
int filterBuffer900[maxIter900];
int filterBuffer1100[maxIter1100];

/* Vont itérer sur chaque array. Différents car ils "bouclent" pour des valeurs
 * différentes*/
int iter900;
int iter1100;

//Les valeurs pour lesquelles les itérateurs "bouclent"
int max900;
int max1100;

//Valeurs plancher du max pour considérer qu'une fréquence est présente
int minValue900 = 135;
int minValue1100 = 135;

/*On éxécute deux fois la même fonction peakDetectOneFreq: une fois pour chaque
 *fréquence. La sortie est stockée dans ces variables, à partir desquelles on
 *construit le char final de sortie*/
char detected900;
char detected1100;

void initPeakDetector(){
    //Lots of zeroes everywhere
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
    //Recherche de max classique (et lente)
    int i;
    int currentMax = 0;
    for (i = 0;i<size;i++){
        if (filterBuffer[i] > currentMax){
            currentMax = filterBuffer[i];
        }
    }
    return currentMax;
}

char peakDetectOneFreq(int filterBuffer[], int * iter, int * max, int input,
                       int maxIter, int minValue){
    /*On essaie de ne jamais devoir itérer sur les samples gardé en mémoire.
     Puisqu'on recherche juste une maximum, l'ordre a pas d'importance donc
     plutôt que de décaler les tableaux à chaque fois, on se contente de
     remplacer la valeur la plus vieille (indiquée par iter<Frequency>. De plus,
     la plupart du temps on ne fait pas de recherche du maximum, on se contente
     de regarder si la nouvelle valeur qu'on introduit est supérieure au maximum
     actuel.*/

    /*Il y a cependant un cas particulier: si la valeur qu'on va retirer de l'
     array est le maximum, et que la nouvelle valeur qu'on va introduire ne lui
     est pas supérieure, on ne sait pas quel est le nouveau maximum (il est
     contenu quelque part ailleurs dans le tableau), et il faut faire une
     recherche classique du maximum. Ceci est couvert par le if suivant*/

    if ((filterBuffer[*iter] == *max) && (input < filterBuffer[*iter])){
        //La valeur à retirer est le maximum actuel, la nouvelle valeur n'est
        //pas plus grande. Il faut trouver le nouveau maximum
        filterBuffer[*iter] = input;//Remplace la vieille valeur
        *max = searchNewMax(filterBuffer, maxIter);//Recherche du nouveau max
                                                   //Dans l'entièreté de l'array
    }else{
        //Cas default
        filterBuffer[*iter] = input;//Remplace la vieille valeur
        if (input > *max){
            //Remplace le maximum si la valeur introduite lui est supérieure
            *max = input;
        }
    }
    
    *iter = (*iter)+1;
    if (*iter == maxIter){
        *iter = 0;
    }//Update l'itérateur


    return *max > minValue;//Fréquence détectée?
}

char peakDetect(int input[2]){
    detected900 = peakDetectOneFreq(filterBuffer900, &iter900, &max900,
                                    input[0], maxIter900,minValue900);
    detected1100 = peakDetectOneFreq(filterBuffer1100, &iter1100, &max1100,
                                     input[1], maxIter1100,minValue1100);
    
    return detected900 | 2*detected1100;//La valeur renvoyée est un char dont
    //le LSB vaut 1 ou 0 selon la présence de 900Hz et le LSB+1 vaut 1 ou 0
    //selon la présence de 1100Hz
}

