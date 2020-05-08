//
// Created by marie on 26-04-2020.
//

#ifndef MASKINNERMANDATORY2_INSTRUCTIONS_H
#define MASKINNERMANDATORY2_INSTRUCTIONS_H

#include <stdlib.h>
#include "helpFunctions.h"
#endif //MASKINNERMANDATORY2_INSTRUCTIONS_H
#define maxInputLength 100 //maximal length of input from a file
#define charsPrBinLine 17
extern int binaryOutpuSize;


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
        imm_offsetToBin(SR2_imm5,5,immBin); //call method to convert offset to binary
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
    char offsetBin[7] = {0};
    imm_offsetToBin(offset6,6,offsetBin); //call method to convert offset to binary
    strcat(binary, offsetBin);

}

void evalST(char * Instruction, char * binary)  //TODO add logic for handling labels
{
    //opcode to binary
    strcat(binary,"0011");
    strcat(binary," "); //formatting
    Instruction += 2; //incrementer pointeren

    char * SR = strtok(Instruction,","); //strtok er en tokenizer som er i stand til at dele strengen ved et komma
    char * PCoffset9 = strtok(NULL,","); //fortsætter med at kommaseperere


    char SRBin[4] = {0};
    ConvRegToBin(SR,SRBin);
    strcat(binary,SRBin); //appends binary register to result
    strcat(binary," "); //formatting


    char offsetBin[10] = {0};
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
        imm_offsetToBin(SR2_imm5,5,immBin); //call method to convert offset to binary
        strcat(binary, immBin);

    }


}

void evalBR(char * Instruction, char * binary) //TODO add logic for handling labels
{
    //opcode to binary
    strcat(binary, "0000"); //appends opcode in binary to the output array
    strcat(binary, " "); //For easier reading

    //Get first SPACE-separated token to determine which type of BR-instuction it is
    char * mnemonic = strtok(Instruction," \t");

    //Determine if it contains N, Z and P
    char * N = strstr(mnemonic,"N");
    char * Z = strstr(mnemonic,"Z");
    char * P = strstr(mnemonic,"P");


    //add corresponding bits (condition codes)
    if (N){ //If (N != NULL) - meaning if "N" was in the mnemonic
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

    strcat(binary," ");//For readability

    char * imm = strtok(NULL," \t"); //Get the rest of the instruction string
    char immBin[10] = {0}; //imm9 + one bit for termination
    imm_offsetToBin(imm,9,immBin); //call method to convert offset to binary
    strcat(binary, immBin);
}

void evalJMP(char * Instruction, char * binary) //TODO add logic for handling labels
{
    //opcode to binary
    strcat(binary, "1100"); //appends opcode in binary to the output array
    strcat(binary, " "); //For easier reading

    //This function may be called both if it is JMP or RET - they have same opcode
    //Both have 3 0's here
    strcat(binary, "000"); //appends opcode in binary to the output array
    strcat(binary, " "); //For easier reading

    //Determine which it is
    if (Instruction[0]=='J'){//If first char is J it must be JMP
        //Delete JMP from Instruction
        Instruction+=3;

        //Rest of the Instruction must be the base register
        char BaseRBin[4] = {0}; //initialize array for binaryReg
        ConvRegToBin(Instruction,BaseRBin); //converts register to binary
        strcat(binary, BaseRBin); // appends to binary
    } else{ //If it is RET, just append "111"
        strcat(binary, "111"); //appends opcode in binary to the output array
    }

    strcat(binary, " "); //For easier reading

    //Last 6 bits are 0
    strcat(binary, "000000");


}

void evalLD(char * Instruction, char * binary) //TODO add logic for handling labels
{
    //opcode to binary
    strcat(binary, "0010"); //appends opcode in binary to the output array
    strcat(binary, " "); //For easier reading

    //Delete "LD"
    Instruction+=2;

    //Destination Register
    char * DR = strtok(Instruction,",");
    char DRBin[4] = {0};
    ConvRegToBin(DR,DRBin); //call a method to convert Register to binary
    strcat(binary, DRBin);

    strcat(binary," ");//For readability

    char * PCoffset9 = strtok(NULL,","); //Rest of the instruction is the offset
    char offsetBin[10] = {0};
    imm_offsetToBin(PCoffset9,9,offsetBin); //converting offset to binary
    strcat(binary,offsetBin); //append to result
}


void evalSTRINGZ(char * Instruction, char * binary)
{
    //Calculate size of array in unorthodox way, since sizeof() doesn't work
    int inputLength =0;
    while (Instruction[inputLength] != '\0'){
        inputLength++;
    }

    //Reallocate space for binary, since it might need more space for .STRINGZ
    binaryOutpuSize = inputLength*charsPrBinLine; //reassign global variable binaryOutputSize
    realloc(binary,binaryOutpuSize); //TODO vær opmærksom på denne linje - den har tidligere givet en fejl
    if (binary ==NULL){
        printf("%s","Memory allocation failed.");
    }
    binary[0]='\0';

    //Get the actual message - quotation-marks are not allowed in labels, so always works
    strtok(Instruction,"\"");
    char * stringz = strtok(NULL,"\"");

    //Converts the stringz-array to binary ascii values
    int i =0;
    int decimalASCII;
    char binChar[charsPrBinLine]={0};

    while (stringz[i] != '\0'){ //Untill end of array
        decimalASCII = (int) stringz[i];                    //get ascii value
        DecimalToBinary(decimalASCII,16,binChar);   //convert value to binary
        strcat(binary,binChar);                             //append to output
        strcat(binary,"\n");                        //append \n to output
        binChar[0]='\0';                                    //clear binChar array
        i++;
    }

    //append binary array terminator
    strcat(binary,"0000000000000000\n");
}

void evalBLKW(char * Instruction, char * binary)
{
    //Deletes the ".BLKW"
    Instruction+=5;

    //Gets the number in the .BLKW directive
    int size = atoi(Instruction); //Get warning here, but if syntax is kept it's no problem

    //Reallocate space for binary, since it might need more space for .STRINGZ
    binaryOutpuSize = size*charsPrBinLine+1; //reassign global variable binaryOutputSize
    realloc(binary,binaryOutpuSize); //TODO vær opmærksom på denne linje - den har tidligere givet en fejl
    if (binary ==NULL){
        printf("%s","Memory allocation failed.");
    }
    binary[0]='\0';

    //Appends empty space
    for (int i=0;i<size;i++){
        strcat(binary,"0000000000000000\n");
    }
}

int evalORIG(char * Instruction, char * binary)
//Input: char array instruction containing a .ORIG asm-line
//Output: char array binary containing binary representation of the address in the line (binary translation)
//          also returns int holding decimal value of address

{
    //Deletes the ".ORIG"
    Instruction+=5;

    //Delete any extra whitespace (function might be called in firstPass() where whitespace hasn't been deleted)
    int i =0;
    while (isspace(Instruction[0])){
        Instruction++;
    }

    //Make binary output
    imm_offsetToBin(Instruction,16,binary);

    //We want to return an int corresponding to the decimal value of the address - used in firstPass()
    if(Instruction[0]=='#'){//If it is already decimal
        //Remove the #
        Instruction++;
        //Return decimal value
        return atoi(Instruction);
    }else{ //If it is hexadecimal
        //Remove the 'X'
        Instruction++;
        //Convert to decimal
        return hexToInt(Instruction);
    }

}