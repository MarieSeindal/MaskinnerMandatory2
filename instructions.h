//
// Created by marie on 26-04-2020.
//

#ifndef MASKINNERMANDATORY2_INSTRUCTIONS_H
#define MASKINNERMANDATORY2_INSTRUCTIONS_H

#include "helpFunctions.h"
#endif //MASKINNERMANDATORY2_INSTRUCTIONS_H




void evalADD(char * Instruction, char * binary) //takes an instruction in asm and converts to binary
{
   //opcode to binary
    strcat(binary, "0001"); //appends opcode in binary to the output array
    Instruction += 3; //instruction-pointeren incrementes med 3 (svarer lidt til at slette de første 3 bogstaver ADD)

    char * DR = strtok(Instruction,","); //strtok er en tokenizer som er i stand til at dele strengen ved et komma
    char * SR1 = strtok(NULL,","); //fortsætter med at kommaseperere
    char * SR2_imm5 = strtok(NULL, ",");

    char DRBin[3] = {0};
    ConvRegToBin(DR,DRBin); //call a method to convert Register to binary
    strcat(binary, DRBin);

    char SR1Bin[3] = {0};
    ConvRegToBin(SR1,SR1Bin); //call a method to convert Register to binary
    strcat(binary, SR1Bin);


    if(SR2_imm5[0] == 'R'){
        strcat(binary,"000"); //appends 000 bc its a register

        char SR2Bin[3] = {0}; //initialize array for binaryReg
        ConvRegToBin(SR2_imm5,SR2Bin); //converts register to binary
        strcat(binary, SR2Bin); // appends to binary

    } else {
        strcat(binary, "1"); //appends 1 bc its an immediate value
        if(SR2_imm5[0] == '#'){
            SR2_imm5 ++;  //increments pointer, resulting in 'removing' #

            char immBin[5] = {0};
            int imm5int = (int)SR2_imm5-48; //casts imm5 to an int
            DecimalToBinary(imm5int,5,immBin);

            strcat(binary, immBin);

        } else if(SR2_imm5[0] == 'x'){ //if its written in hexadecimal

        }
    }


}

void evalNOT(char * Instruction, char * binary)
{


}

