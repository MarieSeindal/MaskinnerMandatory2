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

*/

    secondPass();


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


void firstPass(){
    //TODO unfinished
    //In first pass, we read the asm file and create the symbol table.
    //Symbol table should not be global/static/something, so it can be read from everywhere



    char inFileLocation[] = "C:\\Users\\peter\\Documents\\asm.txt"; //TODO har ikke kunne få det til at virke, hvor filerne ligger i projektroden

    //Initialize input stream
    FILE* inStream;
    inStream = fopen(inFileLocation, "r"); //Open file at file location in reading mode
    if (!inStream) {                                //If it is not found
        printf("%s\n","Error - Input file not found.");
    }

    struct label{
        char name[10]; //Assume that labelnames are of max length 10
        int address; //TODO måske bør det ikke være en int, men en bitstreng
    };

    //Get size of file
    fseek(inStream, 0, SEEK_END);   // seek to end of file
    int fileSize = ftell(inStream);         // get current file pointer
    fseek(inStream, 0, SEEK_SET);   // seek back to beginning of file

    //NOTE: Symbol table could be made using dynamic data structure like linked list - that would be best TODO - make a linked list
    //Much easier to use an array. Smallest possible avg. size of an asm-line is 5 chars=5 bytes e.g "BR x\n"
    //So symboltable cannot be any longer that filesize/5 - even if all lines have labels
    int maxSymbolTableSize = sizeof(struct label)*fileSize/5;

    //TODO make a static symbol table, that can be used in 2nd pass also


}


void secondPass(){
    //TODO gør fil-lokationerne smartere
    char inFileLocation[] = "C:\\Users\\peter\\Documents\\asm.txt"; //Note - har ikke kunne få det til at virke, hvor filerne ligger i projektroden
    char outFileLocation[] = "C:\\Users\\peter\\Documents\\bin.txt";

    //Initialize input stream
    FILE* inStream;
    inStream = fopen(inFileLocation, "r"); //Open file at file location in reading mode
    if (!inStream) { //If it is not found
        //Error - file not found
        printf("%s\n","Error - Input file not found.");
    }



    //Initialize output stream
    FILE* outStream;
    outStream = fopen(outFileLocation, "a"); //append mode
    //If outfile is not found, it will create it.


    //Arrays to hold each asm line and corresponding bin line
    int bufferLength = 255; //won't be able to read any line longer than 255 chars
    char asmLine[bufferLength];
    char binLine[22] = {0};


    //TODO det ville nok være bedre at bruge fscanf(), men kan ikke få den til at virke - Peter
    while(fgets(asmLine, bufferLength, inStream)) {     //While fgets() is actually getting something //TODO could also be while it's not getting .END
        evalInstruction(asmLine,binLine);               //Evaluate the instruction
        fprintf(outStream, "%s\n", binLine);    //Print/append to output file

        //Clear binLine
        binLine[0]='\0';
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











