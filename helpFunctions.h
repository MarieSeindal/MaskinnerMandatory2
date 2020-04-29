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
    Register++; //Deletes the R from Register, so it's just a number
    int RegisterInt = (int) Register[0] -48;

    DecimalToBinary(RegisterInt,3,BinReg); //Always 3 bits in a register


}

void hexToBin(char * hex, int noOfBits, char *binary)
//input: char * hex - a string describing a number in the hexadecimal format
//       int noOfBits - how many bits the output should be sign-extended to
//Output: char * binary - a bit string in 2's complment format describing the same number as the input
//NOTE: obviously produces an error, if noOfBits is not chosen correctly, and if output char * binary is not allocated long enough
{
    //Calculate how many "extension bits" are needed
    int inputHexLength = sizeof(hex)/ sizeof(hex[0]); //number of elements = size of array / size of element
    int minOutputLength = inputHexLength *4;
    int extensionBits = noOfBits - minOutputLength;


    if (hex[0] < 8){ //If it is a positive number (e.g. if first hex-char is 0101)
        for (int i =0; i<extensionBits;i++){
            binary[i]='0';
        }
    } else{ //If it is a negative  number
        for (int i =0; i<extensionBits;i++){
            binary[i]='1';
        }
    }


    for (int i =extensionBits; i<noOfBits;i++){

        switch(hex[i])
        {
            case '0':
                strcat(binary, "0000");
                break;
            case '1':
                strcat(binary, "0001");
                break;
            case '2':
                strcat(binary, "0010");
                break;
            case '3':
                strcat(binary, "0011");
                break;
            case '4':
                strcat(binary, "0100");
                break;
            case '5':
                strcat(binary, "0101");
                break;
            case '6':
                strcat(binary, "0110");
                break;
            case '7':
                strcat(binary, "0111");
                break;
            case '8':
                strcat(binary, "1000");
                break;
            case '9':
                strcat(binary, "1001");
                break;
            case 'A':
                strcat(binary, "1010");
                break;
            case 'B':
                strcat(binary, "1011");
                break;
            case 'C':
                strcat(binary, "1100");
                break;
            case 'D':
                strcat(binary, "1101");
                break;
            case 'E':
                strcat(binary, "1110");
                break;
            case 'F':
                strcat(binary, "1111");
                break;
            default: //Activates only if no other case activated
                printf("Input not hexadecimal.");
        }
    }





}










