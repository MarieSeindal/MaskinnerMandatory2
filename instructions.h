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
    char DRBin[4] = {0};
    ConvRegToBin(DR,DRBin); //call a method to convert Register to binary
    strcat(binary, DRBin);
    strcat(binary, " "); //For easier reading

    char * SR1 = strtok(NULL,","); //fortsætter med at kommaseperere
    char SR1Bin[4] = {0};
    ConvRegToBin(SR1,SR1Bin); //call a method to convert Register to binary
    strcat(binary, SR1Bin);
    strcat(binary, " "); //For easier reading

    char * SR2_imm5 = strtok(NULL, ",");
    if(SR2_imm5[0] == 'R'){
        strcat(binary,"000"); //appends 000 bc its a register
        strcat(binary, " "); //For easier reading

        char SR2Bin[4] = {0}; //initialize array for binaryReg
        ConvRegToBin(SR2_imm5,SR2Bin); //converts register to binary
        strcat(binary, SR2Bin); // appends to binary

    } else {
        strcat(binary, "1"); //appends 1 bc its an immediate value
        strcat(binary, " "); //For easier reading

        //Offset6
        char immBin[6] = {0};
        imm_offsetToBin(SR2_imm5,6,immBin); //call method to convert offset to binary
        strcat(binary, immBin);
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

        char DRBin[4] = {0};
        ConvRegToBin(DR,DRBin); //call a method to convert Register to binary
        strcat(binary, DRBin);
        strcat(binary, " "); //For easier reading

        char SR1Bin[4] = {0};
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


    //First register
    char * DR = strtok(Instruction,",");
    char DRBin[4] = {0};
    ConvRegToBin(DR,DRBin); //call a method to convert Register to binary
    strcat(binary, DRBin);
    strcat(binary, " "); //For easier reading

    //Second register
    char * SR1 = strtok(NULL,",");
    char SR1Bin[4] = {0};
    ConvRegToBin(SR1,SR1Bin); //call a method to convert Register to binary
    strcat(binary, SR1Bin);
    strcat(binary, " "); //For easier reading

    //Offset6
    char * offset6 = strtok(NULL, ",");
    char offsetBin[6] = {0};
    imm_offsetToBin(offset6,6,offsetBin); //call method to convert offset to binary
    strcat(binary, offsetBin);

}

void evalST(char * Instruction, char * binary){
    //opcode to binary
    strcat(binary,"0011");
    strcat(binary," "); //formatting
    Instruction += 2; //incrementer pointeren

    char * SR = strtok(Instruction,","); //strtok er en tokenizer som er i stand til at dele strengen ved et komma
    char * PCoffset9 = strtok(NULL,","); //fortsætter med at kommaseperere

    //TODO add logic here to take into account, if second argument is a label

    char SRBin[4] = {0};
    ConvRegToBin(SR,SRBin);
    strcat(binary,SRBin); //appends binary register to result
    strcat(binary," "); //formatting


    char offsetBin[9] = {0};
    imm_offsetToBin(PCoffset9,9,offsetBin); //converting offset to binary
    strcat(binary,offsetBin); //append to result


}

void evalAND(char * Instruction, char * binary) //takes an instruction in asm and converts to binary
{
    //opcode to binary
    strcat(binary, "0101"); //appends opcode in binary to the output array
    strcat(binary, " "); //For easier reading
    Instruction += 3; //deletes "AND"

    //First token DR
    char * DR = strtok(Instruction,",");
    char DRBin[4] = {0};
    ConvRegToBin(DR,DRBin);
    strcat(binary, DRBin);
    strcat(binary, " "); //For easier reading

    //Second token SR1
    char * SR1 = strtok(NULL,",");
    char SR1Bin[4] = {0};
    ConvRegToBin(SR1,SR1Bin);
    strcat(binary, SR1Bin);
    strcat(binary, " "); //For easier reading

    //Third token either SR2 or imm5
    char * SR2_imm5 = strtok(NULL, ",");
    if(SR2_imm5[0] == 'R'){
        strcat(binary,"000"); //appends 000 bc its a register
        strcat(binary, " "); //For easier reading

        char SR2Bin[4] = {0}; //initialize array for binaryReg
        ConvRegToBin(SR2_imm5,SR2Bin); //converts register to binary
        strcat(binary, SR2Bin); // appends to binary

    } else {
        strcat(binary, "1"); //appends 1 bc its an immediate value
        strcat(binary, " "); //For easier reading

        //Offset6
        char immBin[6] = {0};
        imm_offsetToBin(SR2_imm5,6,immBin); //call method to convert offset to binary
        strcat(binary, immBin);

    }


}

void evalBR(char * Instruction, char * binary)
{
    //opcode to binary
    strcat(binary, "0000"); //appends opcode in binary to the output array
    strcat(binary, " "); //For easier reading
    //Get first SPACE-separated token to determine which type of BR-instuction it is

    char * mnemonic = strtok(Instruction," \t");

    int N = strstr(mnemonic,"N");
    int Z = strstr(mnemonic,"Z");
    int P = strstr(mnemonic,"P");

    if (N){
        strcat(binary,"1");
    } else{
        strcat(binary,"0");
    }
    if (Z){
        strcat(binary,"1");
    } else{
        strcat(binary,"0");
    }
    if (P){
        strcat(binary,"1");
    } else{
        strcat(binary,"0");
    }

    strcat(binary,"0");//For readability

    char * imm = strtok(NULL,""); //Get the rest of the instruction string
    char immBin[10] = {0}; //imm9 + one bit for termination
    imm_offsetToBin(imm,9,immBin); //call method to convert offset to binary
    strcat(binary, immBin);



}