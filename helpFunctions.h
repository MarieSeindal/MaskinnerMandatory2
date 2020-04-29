//
// Created by marie on 26-04-2020.
//

#ifndef MASKINNERMANDATORY2_HELPFUNCTIONS_H
#define MASKINNERMANDATORY2_HELPFUNCTIONS_H

#include <string.h>
//#include "instructions.h"
#endif //MASKINNERMANDATORY2_HELPFUNCTIONS_H





//void RemoveSpaces(char* withSpaces, char * withoutSpaces){}





void StrToUpper(char * lowerCase, char * upperCase){
    int j = strlen(lowerCase);

    for (int i =0; i<j;i++){
        if(lowerCase[i] < 91 && lowerCase[i] > 64){ //hvis de allerede er uppercase
            upperCase[i] = lowerCase[i];
        }else {
            upperCase[i] = lowerCase[i] - 32;
        }
    }
 }

void DecimalToBinary2(int n , int noOfBits, char*bits){ // n= decimal

    int numToBeDivided = n;
    char bit[13]={0};
    int count = 0;


    while (numToBeDivided >= 1) {

        int quotient = numToBeDivided / 2; // resultatet af divisionen
        int remainder = numToBeDivided % 2; //bit-værdien

        if (remainder == 0){
            bit[count]=48;
        } else{
            bit[count]=49;
        }

        count++;

        numToBeDivided = quotient;
    }

    //char flip[count+1];

    int forCounter = count;
    int count2=0;

    // 13 .... antl bit =4

    for (forCounter; forCounter >= 0; forCounter-- ){

        bits[forCounter-1]=bit[count2];

        count2++;
    }

    if (n == 0){
        bits[0]=48;
    }

}



void DecimalToBinary(int n, int noOfBits, char *bits)
{
    int c, d, count;                            //init tre ints

    count = 0;

    for (c = noOfBits-1 ; c >= 0 ; c--)        //et loop som itererer gennem så længe at
                                //antallet af bits er større end 0
        //og starter fra
    {
        d = n >> c;                             //bitwise right shift operator
        //is equal to n/(2^c)
        if (d & 1)                              //mask operation, bitwise and operator
            //it becomes true when the last bit is 1
            *(bits+count) = 1 + '0';
        else
            *(bits+count) = 0 + '0';

        count++;                                //counter
    }
    *(bits+count) = '\0';                       //

}

void ConvRegToBin(char * Register, char * BinReg){
    //remove R
    //DecimalToBinary()


}










