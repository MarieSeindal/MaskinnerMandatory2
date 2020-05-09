#include <stdio.h>
#include <ctype.h>
#include "instructions.h"



void evalInstruction();
void secondPass();
void firstPass();
#define maxInputLength 200 //Can maximally read 200 characters pr line. This can be changed
//Also upper bound for how many lines .BLKW can reserve
#define charsPrBinLine 18
int LocationCounter = 0;
int ProgramCounter =0;
int binaryOutpuSize = maxInputLength*charsPrBinLine*sizeof(char );


int main() {
    firstPass(); //Read asm.txt and create symbol table
    secondPass(); //Evaulate all lines in asm.txt and append translations to bin.txt

    return 0;
}



void evalInstruction(char * assembly, char * binary){
    //Input: assembly - a line of assembly code
    //Output: binary - the binary translation of the line of asm code
    //Ignores labels in front of instructions

    //If the "instruction" is just whitespace
    int notEmpty=0; //Assume, it IS just space, tab or newline etc.
    int i =0;
    while(assembly[i]!= '\0'){
        if (isspace(assembly[i]) == 0){ //If it is something else than whitespace
            notEmpty=1; // indicate than something else has been seen
            break; //Break the while loop
        }
        i++;
    }
    if (notEmpty == 0){ //If it was all whitespace
        binary[0] = '\0'; //Set output to empty string
        return;
    } else{ //If it is something meaningful
        ProgramCounter++; //Increments program counter
    }


    //Converts all letters to uppercase
    char instruction[maxInputLength] = {0};
    StrToUpper(assembly, instruction);

    //Checks if there is a label in front of the instruction/directive + gets opcode
    int opcode;
    int labelFirst;
    labelFirst = hasLabel(instruction, &opcode); //Gives hasLabel pointer to opcode, so this can be determined in same call


    if (labelFirst){ //remove the label, since it's not going to be used here (this function should be used in 2nd pass)
        char * tempInstruction = {0};
        strtok(instruction, " \t"); //make strtok remove the label
        tempInstruction = strtok(NULL, ""); //strtok remembers rest of the string and puts it into tempInstruction, since delim is empty
        strcpy(instruction, tempInstruction); //copy the tempInstruction part into instruction
    }

    //remove all spaces - they are now unnessecary
    char withoutSpace[maxInputLength] = {0};
    removeSpaces(instruction, withoutSpace);


    switch (opcode){
        case 0:
            evalBR(assembly, binary); //Specifically for BR it is important to have the spaces to evaluate correctly
            //Therefore instruction is passed instead of withoutSpace
            break;
        case 1:
            evalADD(withoutSpace, binary);
            break;
        case 2:
            evalLD(assembly, binary); //Needs unprocessed string for correct label
            break;
        case 3:
            evalST(assembly,binary); //Needs unprocessed string for correct label
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
            ProgramCounter = evalORIG(withoutSpace,binary)+1; //Sets ProgramCounter with call
            //PC must point to next instruction, not current - hence the +1
            break;
        case 17:

            break;
        case 18:
            ProgramCounter += evalBLKW(withoutSpace,binary)-1;
            //Increments PC by number of EXTRA lines, that BLKW reserves (already counted that it reserved 1)
            break;
        case 19:
            ProgramCounter += evalSTRINGZ(assembly,binary)-1; //Needs the unprocessed asm string, so the string is untouched
            //Updates PC with number of EXTRA lines, that STRINGZ reserves (already counted that it reserved 1)
            break;
        case 20:

            break;
    }
}


void firstPass(){
    //In first pass, we read the asm file and create the symbol table.

    char inFileLocation[] = "asm.txt";

    ////////////////////////////Initialize input stream/////////////////////////
    FILE* inStream;
    inStream = fopen(inFileLocation, "r"); //Open file at file location in reading mode
    if (!inStream) {                                //If it is not found
        printf("%s\n","Error - Input file not found.");
    }


    ////////////////////////OuputStream////////////////////////////////////////
    FILE* outStream;
    outStream = fopen("label.txt","w"); //this line makes sure that the file is empty before appending anything
    fopen("label.txt","a"); //shifts to mode: appends
    if(!outStream){
        printf("%s", "Something is not working with writing to ouput file");
    }

    ///////////////////////SYMBOLTABLE////////////////////////////////
    char currentString[50];
    char currentStringCopy[50];
    int opcode;
    char label[30] = {0};
    char * string;

    while (fgets(currentString, maxInputLength, inStream)){ //While not End Of File
       // printf("%s", currentString);

        //If the "instruction" is just whitespace
        int notEmpty=0; //Assume, it IS just space, tab or newline etc.
        int i =0;
        while(currentString[i]!= '\0'){
            if (isspace(currentString[i]) == 0){ //If it is something else than whitespace
                notEmpty=1; // indicate than something else has been seen
                break; //Break the while loop
            }
            i++;
        }
        if (notEmpty != 0){ //If it's not just whitespace - proceed

            //Make an uppercase copy of currentString for determining opcode
            strcpy(currentStringCopy,currentString);
            StrToUpper(currentStringCopy,currentStringCopy);//Works fine with same input as output

            int containsLabel = hasLabel(currentStringCopy,&opcode); //See if line has label and get opcode

            if (opcode != -1){ //If the line was recongnized (it could have been just whitespace)
                LocationCounter++; //Increment location counter because line was read
            }


            if (opcode == 16){//If it is .ORIG

                char binary[20]={0}; //Binary string is useless here, but parameter must be passed
                LocationCounter = evalORIG(currentString,binary); //Sets location counter
                binary[0]='\0';

            } else if (opcode ==20){ //If it is .END
                break;                 //Break the while loop
            }

            if(containsLabel){ //If line has a label
                strcpy(label,currentString); //make a copy of currentString so we don't cut it
                strtok(label, " \t"); //Separate by space or tab to get label
                fprintf(outStream,"%s",label);
                fprintf(outStream,",%d\n",LocationCounter);
            }

            if(opcode == 18){ //If it is .BLKW
                // fprintf(outStream,"jeg fandt en blkw\n");
                strtok(currentString,".");
                string = strtok(NULL,"");
                strtok(string," \t");
                string = strtok(NULL," \t\n");
                int number = atoi(string);
                LocationCounter += number-1;

            } else if(opcode == 19){ //If it is .STRINGZ
                strtok(currentString,"\"");
                string = strtok(NULL,"\"");
                int stringlength = strlen(string);
                LocationCounter += stringlength;  //Increment by excact length (+1 for termination, -1 because already incremented)
            }
        }
    }


//////////////////////////closing ouputstream////////////////////////////
    fclose(outStream);

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
    outStream = fopen(outFileLocation,"w"); //this line makes sure that the file is empty before appending anything
    fopen(outFileLocation, "a"); //append mode
    //If outfile is not found, it will create it.


    //Arrays to hold each asm line and corresponding bin line
    char asmLine[maxInputLength];
    char binLine[binaryOutpuSize];
    binLine[0]='\0';

    // USes fgets() instead of fscanf() since it separated by \n and not whitespace
    while(fgets(asmLine, maxInputLength, inStream)) {     //While fgets() is actually getting something //TODO could also be while it's not getting .END

        evalInstruction(asmLine,binLine);               //Evaluate the instruction
        fprintf(outStream, "%s\n", binLine);    //Print/append to output file

        //Clear binLine
        binLine[0]='\0';
    }
}




