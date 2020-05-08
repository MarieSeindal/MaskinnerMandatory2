#include <stdio.h>
#include <ctype.h>
#include "instructions.h"



void evalTest();
void evalInstruction();
void secondPass();
void firstPass();
#define maxInputLength 100 //maximal length of input from a file
#define charsPrBinLine 17

int binaryOutpuSize = maxInputLength*charsPrBinLine*sizeof(char ); //TODO really only needs to be 16, maybe 20 as default but doesnt work rn


int main() {
    //secondPass();
    firstPass();

    return 0;
}



void evalInstruction(char * assembly, char * binary){
    //Input: assembly - a line of assembly code
    //Output: binary - the binary translation of the line of asm code
    //Ignores labels in front of instructions

    //If the "instruction" is just whitespace
    int isEmpty=0; //Assume, it IS just space, tab or newline etc.
    int i =0;
    while(assembly[i]!= '\0'){
        if (isspace(assembly[i]) == 0){ //If it is something else than whitespace
            isEmpty++; // indicate than something else has been seen
        }
        i++;
    }
    if (isEmpty == 0){ //If it was all whitespace
        binary[0] = '\0'; //Set output to empty string
        return;
    }


    //Converts all letters to uppercase
    char instruction[maxInputLength] = {0};
    StrToUpper(assembly, instruction);

    //Checks if there is a label in front of the instruction/directive + gets opcode
    int opcode;
    int labelFirst;
    labelFirst = hasLabel(instruction, &opcode); //Gives hasLabel pointer to opcode, so this can be determined in same call

    char * tempInstruction = {0};

    if (labelFirst){ //remove the label, since it's not going to be used here (this function should be used in 2nd pass)
        strtok(instruction, " \t"); //make strtok remove the label
        tempInstruction = strtok(NULL, ""); //strtok remembers rest of the string and puts it into tempInstruction, since delim is empty
        strcpy(instruction, tempInstruction); //copy the tempInstruction part into instruction
    }

    //remove all spaces - they are now unnessecary
    char withoutSpace[maxInputLength] = {0};
    removeSpaces(instruction, withoutSpace);


    switch (opcode){
        case 0:
            evalBR(instruction, binary); //Specifically for BR it is important to have the spaces to evaluate
            //Therefore instruction is passed instead of withoutSpace
            break;
        case 1:
            evalADD(withoutSpace, binary);
            break;
        case 2:
            evalLD(withoutSpace, binary);
            break;
        case 3:
            evalST(withoutSpace,binary);
            break;
        case 4:

            break;
        case 5:
            evalAND(withoutSpace,binary);
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
            evalJMP(withoutSpace,binary);
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
            evalBLKW(withoutSpace,binary);
            break;
        case 19:
            evalSTRINGZ(assembly,binary); //Needs the unprocessed asm string
            break;
        case 20:

            break;
    }



}


void firstPass(){
    //TODO unfinished
    //In first pass, we read the asm file and create the symbol table.
    //Symbol table should not be global/static/something, so it can be read from everywhere
    printf("nu er jeg i firstpass");

    char inFileLocation[] = "asm.txt";

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
    char inFileLocation[] = "asm.txt";
    char outFileLocation[] = "bin.txt";

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
    char asmLine[maxInputLength];
    char *binLine = (char*) malloc(binaryOutpuSize); //binaryOutputSize is a global variable that can be changed
    if (binLine ==NULL){
        printf("%s","Memory allocation failed.");
    }
    //by other functions if needed
    binLine[0]='\0';

    // USes fgets() instead of fscanf() since it separated by \n and not whitespace
    while(fgets(asmLine, maxInputLength, inStream)) {     //While fgets() is actually getting something //TODO could also be while it's not getting .END
        evalInstruction(asmLine,binLine);               //Evaluate the instruction
        fprintf(outStream, "%s\n", binLine);    //Print/append to output file

        //Clear binLine
        binLine[0]='\0';

        //If binaryOutputSize was changed -change it back
        if (binaryOutpuSize != maxInputLength*charsPrBinLine*sizeof(char)){
            binaryOutpuSize=maxInputLength*charsPrBinLine*sizeof(char); //calculate default binaryOutputSize
            realloc(binLine,binaryOutpuSize);               //reallocate with default size
            if (binLine ==NULL){
                printf("%s","Memory allocation failed.");
            }
        }
    }

    free(binLine);
}




