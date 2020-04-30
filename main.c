#include <stdio.h>
#include "instructions.h"



void evalTest();
void EvalInstruction(char * assembly, char * binary);

int main() {

    char hexBin[32] = {0};
    char hexTest[] = "3FFF1";
    hexToBin(hexTest,32,hexBin);
    printf("%s\n",hexBin);



   char binary[16+5] = {0};
   char notTest[] = "NOTR1,R1,R2";
   char addTest[] = "NOTR1,R1,#-10";
   evalNOT(notTest,binary);
   printf("\n%s\n", binary);
   EvalInstruction(notTest, binary);






    char UpperCase[20] = {0}; // et char array som er initialiseret til at være 0'er
    char testLowerCase[] = "mmDaRiaedhaEjd";


    StrToUpper(testLowerCase, UpperCase);

    printf("%s \n",UpperCase);
    //printf("%s",output);

    char bits[13]={0}; // output char array
    int testToDecimal = -13; //test value MAX 4095

    DecimalToBinary2(testToDecimal, 6, bits);
    DecimalToBinary(testToDecimal, 6, bits);


    printf("%s", bits);


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















