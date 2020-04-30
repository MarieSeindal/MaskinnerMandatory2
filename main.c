#include <stdio.h>
#include "instructions.h"



void evalTest();
void EvalInstruction(char * assembly, char * binary);

int main() {

/*
char bits[50] = {0};
DecimalToBinary2(-2,bits);
printf("test af decToBin2: %s\n",bits);
*/
char TestBits[10] = {"11011"};
char TestNegativeBits[10] = {0};
int CharToInt = atoi(TestBits);
int negated = ~CharToInt;

    //
    printf("%s\n",TestBits);
    printf("%c\n",CharToInt);
    printf("%c",negated);

return 0;
}


void EvalInstruction(char * assembly, char * binary){
    char withoutSpace[30] = {0};
    // RemoveSpaces(assembly, withoutSpace);
    char Instruction[30] = {0};
    StrToUpper(withoutSpace, Instruction);

    if(strstr(Instruction, "ADD") != NULL) //chekker om instruktionen indeholder ADD
    {
        evalADD(Instruction, binary);

    }else if(strstr(Instruction, "NOT") != NULL){

    }else if(strstr(Instruction, "LDR") != NULL){

    }else if(strstr(Instruction, "LD") != NULL){

    }else if(strstr(Instruction, "ST") != NULL){

    }else if(strstr(Instruction, "BR") != NULL){

    }else{//error
    }

}















