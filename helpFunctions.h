//
// Created by marie on 26-04-2020.
//

#ifndef MASKINNERMANDATORY2_HELPFUNCTIONS_H
#define MASKINNERMANDATORY2_HELPFUNCTIONS_H

#include <string.h>
//#include "instructions.h"
#endif //MASKINNERMANDATORY2_HELPFUNCTIONS_H





void removeSpaces(const char* withSpaces, char * withoutSpaces){
    int j=0;
    int i=0;
    while(withSpaces[i] != '\0'){ //While we haven't reached the end of withSpaces
        if (withSpaces[i] != ' ' && withSpaces[i] != '\t'){ //If it's not space or tab
            withoutSpaces[j]=withSpaces[i]; //add to withoutSpace
            j++; //increment withoutSpace index
        }
        i++; //increment withSpace index
    }
    withoutSpaces[j+1]='\0'; //make sure, withoutSpaces ends correctly


}


void signExtendBinary(char * binIn, int noOfBits, char *binOut)
//input: char * binIn - a binary number
//       int noOfBits - how many bits the output should be sign-extended to
//Output: char * binOut - a correctly sign-exteded version of the input binary string
//NOTE: obviously produces an error, if noOfBits is not chosen correctly, and if output char * binary is not allocated long enough
//      Also "works" with reverse "extension" e.g. removing some bits

{
    //Calculate size of hex-array in unorthodox way, since sizeof() doesn't work on dynamically allocated array
    int inputLength =0;
    while (binIn[inputLength] != '\0'){
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
         if(lowerCase[i] < 123 && lowerCase[i] > 96) {    //If it is a lowercase letter
            upperCase[i] = lowerCase[i] - 32;
        } else{                                           //If it is not a lowercase letter
            upperCase[i] = lowerCase[i];
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

    for (; forCounter >= 0; forCounter-- ){

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

void hexToBin(const char * hex, int noOfBits, char *binary)
//input: char * hex - a string describing a number in the hexadecimal format
//       int noOfBits - how many bits the output should be sign-extended to
//Output: char * binary - a bit string in 2's complment format describing the same number as the input
//NOTE: obviously produces an error, if noOfBits is not chosen correctly, and if output char * binary is not allocated long enough
{

    //Calculates length of input (in wierd way, since sizeOf() doesn't work for dynamically allocated arrays)
    int inputHexLength =0;
    while (hex[inputHexLength] != '\0'){
        inputHexLength++;
    }

    //Allocate space for sub-result (correct number but not correct length)
    char tempOutput[inputHexLength*4+1];
    tempOutput[0]='\0';

    //Go through input and append corresponding binary values to tempOutPut
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






int getOpcode(char * firstToken){
    //Input: firstToken - a string containing the first space-separated token of an instruction line
    //         If it is an instruction mnemonic, returns opcode
    //         If it is a directive, returns a special number identityfying that directive
    //         If it is neither - it must be a label and -1 is returned

    //Check if it matches any of the instructions or directives
    if (strcmp(firstToken,"ADD") == 0){
        return 1;
    } else if (strcmp(firstToken,"AND") == 0){
        return 5;
    } else if (//branch can be written in a lot different ways TODO do this in a smarter way if possible
            strcmp(firstToken,"BR") == 0|| strcmp(firstToken,"BRN")  == 0|| strcmp(firstToken,"BRP")  == 0|| strcmp(firstToken,"BRZ")  == 0
            || strcmp(firstToken,"BRNZ")  == 0|| strcmp(firstToken,"BRNP")  == 0|| strcmp(firstToken,"BRPZ")  == 0|| strcmp(firstToken,"BRPN") == 0
            || strcmp(firstToken,"BRZN")  == 0|| strcmp(firstToken,"BRZP")  == 0
            || strcmp(firstToken,"BRNPZ")  == 0|| strcmp(firstToken,"BRNZP") == 0
            || strcmp(firstToken,"BRPNZ")  == 0|| strcmp(firstToken,"BRPZN") == 0
            || strcmp(firstToken,"BRPZNP")  == 0|| strcmp(firstToken,"BRZPN") == 0
            ){
        return 0;
    } else if (strcmp(firstToken,"JMP") == 0 ||strcmp(firstToken,"RET") == 0){
        return 4;
    } else if (strcmp(firstToken,"JSR") ==0 || strcmp(firstToken,"JSRR") == 0){
        return 5;
    } else if (strcmp(firstToken,"LD") == 0){
        return 2;
    } else if (strcmp(firstToken,"LDI") == 0){
        return 10;
    } else if (strcmp(firstToken,"LDR") == 0){
        return 6;
    } else if (strcmp(firstToken,"LEA") == 0){
        return 14;
    } else if (strcmp(firstToken,"NOT") == 0){
        return 9;
    } else if (strcmp(firstToken,"RTI") == 0){
        return 8;
    } else if (strcmp(firstToken,"ST") == 0){
        return 3;
    } else if (strcmp(firstToken,"STI") == 0){
        return 11;
    } else if (strcmp(firstToken,"STR") == 0){
        return 7;
    } else if (strcmp(firstToken,"TRAP") == 0){
        return 15;
    }
    //The following are the directives. They don't have an opcode, but here we assign them a number
    else if (strcmp(firstToken,".ORIG") == 0){
        return 16;
    } else if (strcmp(firstToken,".FILL") == 0){
        return 17;
    } else if (strcmp(firstToken,".BLKW") == 0){
        return 18;
    } else if (strcmp(firstToken,".SRINGZ") == 0){
        return 19;
    } else if (strcmp(firstToken,".END") == 0){
        return 20;

    } else { //If it was neither - return -1 to indicate that token was not an opcode
        return -1;
    }
}

int hasLabel(char * asmLine, int * pOpcode){
    //Input:            asmLine - and unprocessed line of assembly code
    //Simulated Input:  return - a pointer to an int, that stores the opcode of the instruction or a number telling which directive it is
    //Output:           hasLabel - 1 if the first token of the line is a label, 0 otherwise
    //NOTE: Why does this function also return the opcode? Because opcode and whether it has a label is determined at the same time

    //create copy of asmLine so it doesn't get changed
    char asmCopy[35];
    strcpy(asmCopy,asmLine);

    char * firstToken = strtok(asmCopy," \t"); //the delimitter is both tab and space - will separate if it sees any
    //This first token should EITHER be a label OR a known instruction/directive.

    //Call method to determine the opcode
    int opcode = getOpcode(firstToken);

    if (opcode != -1){      //If it's a real opcode and not just a label
        *pOpcode = opcode;
        return 0;           //Return that it has no label

    } else {                //If it was just a label
        //get next token and try again
        char * secondToken = strtok(NULL," \t"); //gets next token
        opcode = getOpcode(secondToken);
        * pOpcode = opcode;
        return 1; //Return that is has a label
    }
}










