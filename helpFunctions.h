//
// Created by marie on 26-04-2020.
//

#ifndef MASKINNERMANDATORY2_HELPFUNCTIONS_H
#define MASKINNERMANDATORY2_HELPFUNCTIONS_H

#include <string.h>
//#include "instructions.h"
#endif //MASKINNERMANDATORY2_HELPFUNCTIONS_H


//void RemoveSpaces(char* withSpaces, char * withoutSpaces){}


void signExtendBinary(char * binIn, int noOfBits, char *binOut)
//input: char * binIn - a binary number
//int noOfBits - how many bits the output should be sign-extended to
//Output: char * binOut - a correctly sign-exteded version of the input binary string
//NOTE: obviously produces an error, if noOfBits is not chosen correctly, and if output char * binary is not allocated long enough
//Also "works" with reverse "extension" e.g. removing some bits

{
    //Calculate size of hex-array in unorthodox way, since sizeof() doesn't work on dynamically allocated array
    int inputLength =0;
    while (binIn[inputLength] != NULL){
        inputLength++;
    }

    if (noOfBits<inputLength){ //If it needs to be shortened
        //Copy only the last "noOfBits" bits to binOut
        int offset = inputLength-noOfBits;
        for (int i = 0; i <noOfBits ; ++i) {
            binOut[i] = binIn[i+offset];
        }

    } else if (noOfBits==inputLength){ //If size is already correct
        //copy input into output
        for (int i = 0; i <noOfBits ; ++i) {
            binOut[i] = binIn[i];
        }

    } else { //If it needs to be extended
        char extension = binIn[0]; //First bit of input determines if extension is with 1 or 0

        //Output is extended to correct length
        int offset = noOfBits-inputLength;
        for (int i = 0; i < offset; i++) { //All bits untill the offset are set to the extension
            binOut[i] = extension;
            binOut[i+1] = '\0'; //make sure, binOut has array terminator
        }
        //After the extension, input is appended to output
        strcat(binOut,binIn);
    }


}


void StrToUpper(char * lowerCase, char * upperCase){
    int j = strlen(lowerCase);

    // int i = uppercase index

    for (int i =0; i<j;i++){
        if(lowerCase[i] < 91 && lowerCase[i] > 64){             //hvis de allerede er uppercase
            upperCase[i] = lowerCase[i];
        } else if(lowerCase[i] < 123 && lowerCase[i] > 96) {    // hvis de er lowercase
            upperCase[i] = lowerCase[i] - 32;
        } else{                                                 // hvis de ikke er et kendt tegn, så skipper den over tegnet og tager det næste input i stedet for.
            upperCase[i] = lowerCase[i];
        }
    }
 }


void DecimalToBinary2(int n, char*bits){ // n= decimal

    int numToBeDivided = n;
    int WasItNegative = 0;

    if(n<0){
        numToBeDivided *= -1;
        WasItNegative = 1;
    }
    char bit[13]={0};
    int count = 0;

    //takes care of the situation if only input is a 0
    if (n == 0){
        bits[0]=48;
    }

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

    int forCounter = count;
    int count2=0;

    // 13 .... antl bit =4

    for (forCounter; forCounter >= 0; forCounter-- ){

        bits[forCounter-1]=bit[count2];

        count2++;
    }



    if(WasItNegative){
        //flip all the bits and add one
        for(forCounter; forCounter>=0; forCounter--){
            bits[forCounter] = ~bits[forCounter];
        }

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

    //Calculates length of input (in wierd way, since sizeOf() doesn't work for dynamically allocated arrays)
    int inputHexLength =0;
    while (hex[inputHexLength] != NULL){
        inputHexLength++;
    }

    //Allocate space for sub-result (correct number but not correct length)
    char tempOutput[inputHexLength*4];
    tempOutput[0]='\0';

    //Go thorugh input and append corresponding binary values to tempOutPut
    int i =0;
    while (hex[i]!= '\0'){

        switch(hex[i])
        {
            case '0':
                strcat(tempOutput, "0000");
                break;
            case '1':
                strcat(tempOutput, "0001");
                break;
            case '2':
                strcat(tempOutput, "0010");
                break;
            case '3':
                strcat(tempOutput, "0011");
                break;
            case '4':
                strcat(tempOutput, "0100");
                break;
            case '5':
                strcat(tempOutput, "0101");
                break;
            case '6':
                strcat(tempOutput, "0110");
                break;
            case '7':
                strcat(tempOutput, "0111");
                break;
            case '8':
                strcat(tempOutput, "1000");
                break;
            case '9':
                strcat(tempOutput, "1001");
                break;
            case 'A':
                strcat(tempOutput, "1010");
                break;
            case 'B':
                strcat(tempOutput, "1011");
                break;
            case 'C':
                strcat(tempOutput, "1100");
                break;
            case 'D':
                strcat(tempOutput, "1101");
                break;
            case 'E':
                strcat(tempOutput, "1110");
                break;
            case 'F':
                strcat(tempOutput, "1111");
                break;
            default: //Activates only if no other case activated
                printf("Input not hexadecimal.");
        }
        i++;
    }

    //Call signExtend function to format the number correctly
    signExtendBinary(tempOutput,noOfBits,binary);



}


void imm_offsetToBin(char * imm_offset, int numOfBits, char * binOut){
    if(imm_offset[0] == '#'){
        imm_offset ++;  //increments pointer, resulting in 'removing' #

        int imm_offsetInt = atoi(imm_offset); //casts or offset to an int
        DecimalToBinary(imm_offsetInt, numOfBits, binOut); //converts to binary


    } else if(imm_offset[0] == 'x'){ //if its written in hexadecimal
        imm_offset ++;  //increments pointer, resulting in 'removing' x

        hexToBin(imm_offset, numOfBits, binOut); //converts to binary

    }
}











