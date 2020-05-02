#include <stdio.h>
#include "instructions.h"



void evalTest();
void evalInstruction();
void secondPass();

int main() {
/*
    //gamle TESTS
    char immBin[50] = {0};
    char immtest[] = "x5F";
    imm_offsetToBin(immtest,10,immBin);
    printf("%s\n",immBin);

    char hexBin[32] = {0};
    char hexTest[] = "3FFF1";
    hexToBin(hexTest,32,hexBin);
    printf("\n%s\n",hexBin);


    char LDRBin[16+5] = {0};
    char LDRtest[] = "LDRR1,R2,#-10";
    evalLDR(LDRtest,LDRBin);
    printf("\n%s\n", LDRBin);


   char binary[16+5] = {0};
   char notTest[] = "NOTR1,R1";
   char addTest[] = "ADDR1,R2,#-10";
   evalADD(addTest,binary);
   printf("\n%s\n", binary);
   EvalInstruction(notTest, binary);



    char bits[13]={0}; // output char array
    int testToDecimal = -13; //test value MAX 4095

    DecimalToBinary2(testToDecimal, 6, bits);
    DecimalToBinary(testToDecimal, 6, bits);
    printf("%s", bits);



    char UpperCase[20] = {0}; // et char array som er initialiseret til at være 0'er
    char testLowerCase[] = "m#m.D-a&R";
    StrToUpper(testLowerCase, UpperCase);
    printf(testLowerCase);
    printf("%s \n",UpperCase);
    //printf("%s",output);

    char STbin[16+5] = {0};
    char STtest[] = "STR7,#8";
    evalST(STtest,STbin);
    printf("Test af evalST: %s\n",STbin);

    char noSpace[16+5] = {0};
    char withSpaceTest[] = "ST R7 , #      8";
    removeSpaces(withSpaceTest,noSpace);
    printf("Test af removeSpaces: %s\n",noSpace);

    char instructionBin[16+5] = {0};
    char * instructionAsm = "ADD, R1, R2, #3";
    evalInstruction(instructionAsm,instructionBin);
    printf("Test af evalInstruction: %s\n",instructionBin);

*/


    char bits[50] = {0};
    DecimalToBinary2(99,20,bits);
    printf("test af decToBin2: %s\n",bits);

    char STbin[16+5] = {0};
    char STtest[] = "STR7,#8";
    evalST(STtest,STbin);
    printf("Test af evalST: %s\n",STbin);


    char instructionBin[16+5] = {0};
    char * instructionAsm;


    printf("%s\n","Type instruction:");
    scanf("%99[^\n]",instructionAsm); //Lidt specielt format af scanf her - den indlæser en hel linje i stedet for bare et ord
    evalInstruction(instructionAsm,instructionBin);
    printf("Test af evalInstruction: %s\n",instructionBin);

    return 0;
}






void evalInstruction(char * assembly, char * binary){
    //Input: assembly - a line of assembly code
    //Output: binary - the binary translation of the line of asm code
    //Ignores labels in front of instructions

    //Converts all letters to uppercase
    char instruction[30] = {0};
    StrToUpper(assembly, instruction);

    //Checks if there is a label in front of the instruction/directive + gets opcode
    int opcode;
    int labelFirst;
    labelFirst = hasLabel(instruction, &opcode); //Gives hasLabel pointer to opcode, so this can be determined in same call

    char * tempInstruction;

    if (labelFirst){ //remove the label, since it's not going to be used here (this function should be used in 2nd pass)
        strtok(instruction, " \t"); //make strtok remove the label
        tempInstruction = strtok(NULL, ""); //strtok remembers rest of the string and puts it into tempInstruction, since delim is empty
        strcpy(instruction, tempInstruction); //copy the tempInstruction part into instruction
    }

    //remove all spaces - they are now unnessecary
    char withoutSpace[30] = {0};
    removeSpaces(instruction, withoutSpace);


    switch (opcode){
        case 1:
            evalADD(withoutSpace, binary);
            break;
        case 2:

            break;
        case 3:
            evalST(withoutSpace,binary);
            break;
        case 4:

            break;
        case 5:

            break;
        case 6:
            evalLDR(withoutSpace,binary);
            break;
        case 7:

            break;
        case 8:

            break;
        case 9:
            evalNOT(withoutSpace, binary);
            break;
        case 10:

            break;
        case 11:

            break;
        case 12:

            break;
        case 13:

            break;
        case 14:

            break;
        case 15:

            break;

        //These are not real opcodes, but codes for the directives
        case 16:

            break;
        case 17:

            break;
        case 18:

            break;
        case 19:

            break;
        case 20:

            break;
    }



}


void secondPass(){
    FILE* inStream;
    char fileLocation[] = "C:\\Users\\peter\\Documents\\asm.txt";
    inStream = fopen(fileLocation, "r");
    if (!inStream) {
        //Error - file not found
        printf("%s\n","Error - File not found.");
    }

    char binLine[22] = {0};
    int bufferLength = 255;
    char asmLine[bufferLength];
    while(fgets(asmLine, bufferLength, inStream)) {
        evalInstruction(asmLine,binLine);
        printf(binLine);
        printf("\n");
    }




}



/*
 void evalInstruction(char * assembly, char * binary){
    char withoutSpace[30] = {0};
    removeSpaces(assembly, withoutSpace);
    char Instruction[30] = {0};
    StrToUpper(withoutSpace, Instruction);

    if(strstr(Instruction, "ADD") != NULL) //chekker om instruktionen indeholder ADD
    {
        evalADD(Instruction, binary);

    }else if(strstr(Instruction, "NOT") != NULL){
        evalNOT(Instruction, binary);
    }else if(strstr(Instruction, "LDR") != NULL){
        evalLDR(Instruction, binary);
    }else if(strstr(Instruction, "LD") != NULL){

    }else if(strstr(Instruction, "ST") != NULL){
        evalST(Instruction, binary);
    }else if(strstr(Instruction, "BR") != NULL){

    }else{//error
    }
}
 */











