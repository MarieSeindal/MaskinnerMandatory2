//
// Created by marie on 26-04-2020.
//

#ifndef MASKINNERMANDATORY2_HELPFUNCTIONS_H
#define MASKINNERMANDATORY2_HELPFUNCTIONS_H

#include <string.h>
#include <math.h>
#endif //MASKINNERMANDATORY2_HELPFUNCTIONS_H
extern int ProgramCounter;


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
    withoutSpaces[j+1]='\0'; //make sure, withoutSpaces is terminated
}

void signExtendBinary(char * binIn, int noOfBits, char *binOut)
{
    //input: char * binIn - a binary number
    //       int noOfBits - how many bits the output should be sign-extended to
    //Output: char * binOut - a correctly sign-extended version of the input binary string
    //NOTE: obviously produces an error, if noOfBits is not chosen correctly, and if output char * binary is not allocated long enough
    //      Also "works" with reverse "extension" e.g. removing some bits


    //Calculate size of hex-array in unorthodox way, since sizeof() doesn't work on these arrays
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
        char extension = binIn[0]; //First bit of input determines if extension is with '1' or '0'

        //Output is extended to correct length
        int offset = noOfBits-inputLength;
        for (int i = 0; i < offset; i++) { //All bits until the offset are set to the extension
            binOut[i] = extension;
            binOut[i+1] = '\0'; //make sure, binOut has array terminator
        }
        //After the extension, input is appended to output
        strcat(binOut,binIn);
    }
}

void negateBinary(char * input, char * negation){
    //Takes as input a 2's complement binary number and returns as output it's negation
    //That is - returns the input * (-1) e.g. input=#5=101 ==> output =#-5 = 011
    //NOTE: works just fine if input and output strings are the same

    //Calculate length of input
    int inputLength =0;
    while (input[inputLength] != '\0'){
        inputLength++;
    }

    //Variable to store if first 1 has been seen yet
    int first1 = 0;

    for (int i = inputLength-1; i >= 0 ; i--) {
        if (input[i]=='0' && !first1){          //If we haven't encountered our first '1'
            negation[i] = '0';                  //Keep it a '0'

        } else if (input[i]=='1' && !first1){  //If we ARE encountering our first '1'
            negation[i] = '1';                  //Keep it a '1'
            first1 = 1;                         //Remember that first 1 has been found

            //After the first '1' we flip bits
        } else if (input[i]=='1' && first1){
            negation[i] = '0';                  //Flip
        } else if (input[i]=='0' && first1){
            negation[i] = '1';                  //Flip
        }
    }
    negation[inputLength]='\0'; //Terminate string
}

void StrToUpper(char * lowerCase, char * upperCase){
    //Works fine if lowercase (input) is the same as UPPERCASE (output)
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

void DecimalToBinary(int n , int numOfBits, char*binary){
    //Converts integer input to binary string in 2's complement
    // n= decimal input, numOfBits = number of bits in output string, binary = output
    //NOTE: Assumes that the caller has initialized binary array with at least numOfBits+1 chars (for termination)
    //NOTE: Works for both signed and unsigned integers if enough bits are allocated, and number is positive
    //      For negative numbers it obviously needs to have enough bits for 2's complement representation


    //Double check that output is terminated
    binary[numOfBits]='\0';


    int numToBeDivided = n;
    int index = numOfBits - 1; //build number from least significant bit

    //Check if n is negative
    int negative =0;
    if (n<0){
        negative=1;
        numToBeDivided =-n; //If negative, treat it as positive at first
    }


    while (numToBeDivided >= 1) {

        int quotient = numToBeDivided / 2;      //Result from division
        int remainder = numToBeDivided % 2;     //Remainder from division

        if (remainder == 0){
            binary[index]='0';
        } else{
            binary[index]='1';
        }

        index--;

        numToBeDivided = quotient;
    }

    //Add any trailing 0's in front of number (+1 is because index has been decremented once too much)
    for (int i = 0; i < index+1; i++) {
        binary[i]='0';
    }

    if (negative){ //Negate if it was negative
        negateBinary(binary,binary); //negation works fine with same input and output char
    }

}

void ConvRegToBin(char * Register, char * BinReg){
    //Deletes any leading whitespace
    while(isspace(Register[0])){
        Register++;
    }

    Register++; //Deletes the R from Register, so it's just a number
    int RegisterInt = (int) Register[0] -48;

    //DecimalToBinary is mostly for 2's complement integers. RegisterInt is unsigned, but still calculated correctly
    //Read comments in DecimalToBinary for further description
    DecimalToBinary(RegisterInt,3,BinReg); //Always 3 bits in a register
}

void hexToBin(const char * hex, int noOfBits, char *binary)
{   //input:    char * hex - a string describing a number in the hexadecimal format
    //          int noOfBits - how many bits the output should be sign-extended to
    //Output:   char * binary - a bit string in 2's complment format describing the same number as the input
    //NOTE: obviously produces an error, if noOfBits is not chosen correctly, and if output char * binary is not allocated long enough


    //Allocate array for sub-result
    char tempOutput[noOfBits+5]; //Tempoutput gets some extra space to avoid overflow
    tempOutput[0]='\0';

    //Determine if input hex number is negative
    int negative = 0;
    if (hex[0]=='-'){           //If it is negative
        hex++;                  //Delete the '-' to treat it as positive
        negative =1;            //Remember that it was negative so we can negate in the end

    }

    //No matter if number was negative or positive, we treat it as positive for now (same mechanics as LC3-tools assembler)
    strcat(tempOutput,"0"); //Add leading 0 so it is positive

    //Initialize index variable
    int i =0;

    //Go through input and append corresponding binary values to tempOutPut
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
            case '\n'://Often '\n' is passed to this function in the end, and it should be ignored
                break;
            default: //Activates only if no other case activated
                printf("Input not hexadecimal.");
        }
        i++;
    }

    //If the number was negative to start with
    if (negative){
        negateBinary(tempOutput,tempOutput); //Negate the number - works fine with same input as output
    }

    //Call signExtend function to format the number correctly into output string
    signExtendBinary(tempOutput,noOfBits,binary);
    //signExtendBinary can cut off some bits if asked to do so.
    // This only causes errors (unpredictable results), if the asm-instruction has syntax error
    // e.g. if we calculate x1F in binary in 5 bits, we might expect 11111, but really it produces a syntax error (in LC3-tools at least)
    //since x1F means +31 and +31 can't be represented as 2's comp with 5 bits.
    //Correct way to get 11111 would be x-1

}

void imm_offsetToBin(char * imm_offset, int numOfBits, char * binOut){
    if(imm_offset[0] == '#'){
        imm_offset ++;  //increments pointer, resulting in 'removing' #

        int imm_offsetInt = atoi(imm_offset); //converts imm or offset to an int
        DecimalToBinary(imm_offsetInt, numOfBits, binOut); //converts to binary


    } else if(imm_offset[0] == 'X'){ //if its written in hexadecimal
        imm_offset ++;  //increments pointer, resulting in 'removing' X

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
    } else if (//branch can be written in a lot different ways
            strcmp(firstToken,"BR") == 0|| strcmp(firstToken,"BRN")  == 0|| strcmp(firstToken,"BRP")  == 0|| strcmp(firstToken,"BRZ")  == 0
            || strcmp(firstToken,"BRNZ")  == 0|| strcmp(firstToken,"BRNP")  == 0|| strcmp(firstToken,"BRPZ")  == 0|| strcmp(firstToken,"BRPN") == 0
            || strcmp(firstToken,"BRZN")  == 0|| strcmp(firstToken,"BRZP")  == 0
            || strcmp(firstToken,"BRNPZ")  == 0|| strcmp(firstToken,"BRNZP") == 0
            || strcmp(firstToken,"BRPNZ")  == 0|| strcmp(firstToken,"BRPZN") == 0
            || strcmp(firstToken,"BRPZNP")  == 0|| strcmp(firstToken,"BRZPN") == 0
            ){
        return 0;
    } else if (strcmp(firstToken,"JMP") == 0 || strcmp(firstToken,"RET") == 0){
        return 12;
    } else if (strcmp(firstToken,"JSR") ==0 || strcmp(firstToken,"JSRR") == 0){
        return 4;
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
    } else if (strcmp(firstToken,".STRINGZ") == 0){
        return 19;
    } else if (strcmp(firstToken,".END") == 0 ||strcmp(firstToken,".END\n") == 0){
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

int hexToInt(char * hexInput){
    //Takes as input a char array containing a hex-number (without X) e.g. 1FA or -10
    //Returns integer holding the decimal value of the input

    strtok(hexInput,"\n"); //Terminate hexInput at newLine if there is one, so it doesn't mess up size

    //Find out if hexInput is negative (can only be indicated by minus-sign)
    int negative =0;
    if (hexInput[0]=='-'){
        //remember that it is negative
        negative=1;
        //remove the minus-sign
        hexInput++;
    }

    // Find the length of total number of hex digit -1 for correct exponent power
    int len = strlen(hexInput)-1;

    //Initialize variables
    int decimal =0; //The total decimal number
    int val=0;      //Value of each character (0-15)

    //Iterate over each hex digit
    for(int i=0; hexInput[i]!='\0'; i++)
    {
        //Find the decimal representation of hex[i]
        //If it is from 0 to 9
        if(hexInput[i]>='0' && hexInput[i]<='9')
        {
            //Subtract 48 which is ASCII value of 0
            val = hexInput[i] - 48;
        }
        //If it is from A to F
        else if(hexInput[i]>='A' && hexInput[i]<='F')
        {
            //Subtract 65 which is ASCII value of A and add 10 so A->10, F->15 and so on
            val = hexInput[i] - 65 + 10;
        }

        //Add to decimal number the value of the character times 16 to the power of index number (from right to left)
        decimal += val * pow(16, len);
        //Decrement index number
        len--;
    }
    //return decimal value
    return decimal;
}

int getLabelAddress(const char * label){
    //Searches label.txt file for specific label and returns address of label

    char inFileLocation[] = "SymbolTable.txt";

    FILE* inStream;
    inStream = fopen(inFileLocation, "r"); //Open file at file location in reading mode
    if (!inStream) {                                //If it is not found
        printf("%s\n","Error - Input file not found.");
    }


    char line[31]={0};
    while (fgets(line, 30, inStream)){//While not EOF
        strtok(line,",");
        if (strcmp(label,line)==0){ //If label that we search for is equal to found label
            char *addressString;
            addressString = strtok(NULL,"\n"); //Get rest of string
            int address = atoi(addressString); //Convert number to int
            fclose(inStream); //close file
            return address;
        }
    }

    fclose(inStream);
    return -1; //If not found - return -1

}

void calcBinaryOffset(char* label, int numOfBits, char * binaryOffset){
    //Calculates the offset from PC to label and returns it in binary format in specified number of bits
    int labelAddress = getLabelAddress(label);
    int offset = labelAddress - ProgramCounter ;
    DecimalToBinary(offset,numOfBits,binaryOffset);
}







