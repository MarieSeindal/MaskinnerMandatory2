//
// Created by marie on 26-04-2020.
//

#ifndef MASKINNERMANDATORY2_INSTRUCTIONS_H
#define MASKINNERMANDATORY2_INSTRUCTIONS_H

#include <stdlib.h>
#include "helpFunctions.h"
#endif //MASKINNERMANDATORY2_INSTRUCTIONS_H




void evalADD(char * Instruction, char * binary) //takes an instruction in asm and converts to binary
{
   //opcode to binary
    strcat(binary, "0001"); //appends opcode in binary to the output array
    strcat(binary, " "); //For easier reading
    Instruction += 3; //instruction-pointeren incrementes med 3 (svarer lidt til at slette de første 3 bogstaver ADD)

    char * DR = strtok(Instruction,","); //strtok er en tokenizer som er i stand til at dele strengen ved et komma
    char * SR1 = strtok(NULL,","); //fortsætter med at kommaseperere
    char * SR2_imm5 = strtok(NULL, ",");

    char DRBin[3] = {0};
    ConvRegToBin(DR,DRBin); //call a method to convert Register to binary
    strcat(binary, DRBin);
    strcat(binary, " "); //For easier reading

    char SR1Bin[3] = {0};
    ConvRegToBin(SR1,SR1Bin); //call a method to convert Register to binary
    strcat(binary, SR1Bin);
    strcat(binary, " "); //For easier reading


    if(SR2_imm5[0] == 'R'){
        strcat(binary,"000"); //appends 000 bc its a register
        strcat(binary, " "); //For easier reading

        char SR2Bin[3] = {0}; //initialize array for binaryReg
        ConvRegToBin(SR2_imm5,SR2Bin); //converts register to binary
        strcat(binary, SR2Bin); // appends to binary

    } else {
        strcat(binary, "1"); //appends 1 bc its an immediate value
        strcat(binary, " "); //For easier reading
        if(SR2_imm5[0] == '#'){
            SR2_imm5 ++;  //increments pointer, resulting in 'removing' #

            char immBin[5] = {0};
            int imm5int = atoi(SR2_imm5); //casts imm5 to an int
            //int imm5int = (int)SR2_imm5[0]-48; //casts imm5 to an int
            DecimalToBinary(imm5int,5,immBin);

            strcat(binary, immBin);

        } else if(SR2_imm5[0] == 'x'){ //if its written in hexadecimal

        }
    }


}

void evalNOT(char * Instruction, char * binary)
{
        //opcode to binary
        strcat(binary, "1001"); //appends opcode in binary to the output array
        strcat(binary, " "); //For easier reading
        Instruction += 3; //instruction-pointeren incrementes med 3 (svarer lidt til at slette de første 3 bogstaver ADD)

        char * DR = strtok(Instruction,","); //strtok er en tokenizer som er i stand til at dele strengen ved et komma
        char * SR1 = strtok(NULL,","); //fortsætter med at kommaseperere

        char DRBin[3] = {0};
        ConvRegToBin(DR,DRBin); //call a method to convert Register to binary
        strcat(binary, DRBin);
        strcat(binary, " "); //For easier reading

        char SR1Bin[3] = {0};
        ConvRegToBin(SR1,SR1Bin); //call a method to convert Register to binary
        strcat(binary, SR1Bin);
        strcat(binary, " "); //For easier reading

        strcat(binary, "111111");



}

void evalLDR(char * Instruction, char * binary) //takes an instruction in asm and converts to binary
{
    //opcode to binary
    strcat(binary, "0110"); //appends opcode in binary to the output array
    strcat(binary, " "); //For easier reading
    Instruction += 3; //instruction-pointeren incrementes med 3 (svarer lidt til at slette de første 3 bogstaver ADD)

    char * DR = strtok(Instruction,",");
    char * SR1 = strtok(NULL,",");
    char * offset6 = strtok(NULL, ",");

    char DRBin[3] = {0};
    ConvRegToBin(DR,DRBin); //call a method to convert Register to binary
    strcat(binary, DRBin);
    strcat(binary, " "); //For easier reading

    char SR1Bin[3] = {0};
    ConvRegToBin(SR1,SR1Bin); //call a method to convert Register to binary
    strcat(binary, SR1Bin);
    strcat(binary, " "); //For easier reading


    if(offset6[0] == '#'){
        offset6 ++;  //increments pointer, resulting in 'removing' #

        char offset[6] = {0};
        int offsetInt = atoi(offset6); //casts imm5 to an int
        DecimalToBinary(offsetInt, 6, offset);

        strcat(binary, offset);

    } else if(offset6[0] == 'x'){ //if its written in hexadecimal
        offset6 ++;  //increments pointer, resulting in 'removing' #

        char offset[6] = {0};
        int offsetInt = atoi(offset6); //casts imm5 to an int
        DecimalToBinary(offsetInt, 6, offset);

        strcat(binary, offset);
    }


}

