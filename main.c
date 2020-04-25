#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

const char *evalADD();
void evalInstruction();
const char * deleteSpaces();
void remove_spaces ();
void evalRegister ();
char *decimal_to_binary();
const char * evalAND(char * instruction);


int main() {
    char line[] = "AND R1, R2, #-2";


    evalInstruction(line);


    return 0;
}


void evalInstruction(char * input){
    //Delete all space characters from instruction
    int len = strlen(input) + 1;
    char inputTrimmed[len];
    remove_spaces(inputTrimmed,input);


    //Convert all letters to uppercase

    char * instruction = inputTrimmed;

    if(strstr(instruction, "ADD") != NULL) { //If instruction contains "ADD"
        printf("Det er en ADD instruktion\n");
        evalADD(instruction);

    } else if (strstr(instruction, "AND") != NULL){ //If instruction contains "AND"
        printf("Det er en AND instruktion\n");
        evalAND(instruction);
    }



}

const char * evalADD(char * instruction) {
    //Output is 16 bits long with one array terminator in the end, so 17
    char output[17+4]; //+4 is for testing
    //Makes sure, that output is currently empty
    output[0]='\000';

    //Adds the known opcode
    strcat(output, "0001");
    strcat(output, " "); //For easier reading - can delete later


    //Delete "ADD" (already known) from instruction, so we can separate with commas
    instruction +=3;

    //Separate instruction into comma-separated tokens, e.g. R0, R1, #5
    char * DR = strtok(instruction, ",");
    char * SR1 = strtok(NULL, ",");
    char * SR2_imm5 = strtok(NULL, ",");


    //Converts DR (Destination Register - char array) to bitstring in DrBIN (char array)

    DR++; //Deletes the R in DR, e.g. "R5" -> "5"
    int DRdec = atoi(DR); //Casting the string-number to an int ()

    char * DrBIN = (char*)malloc(4); //Registers use 3 bits in LC3 + 1 bit for array terminator
    DrBIN = decimal_to_binary(DRdec,3);

    strcat(output, DrBIN); //DrBIN is added to output string
    strcat(output, " "); //For easier reading


    //Does the excact same for Source Register 1 (could implement method for this)
    SR1++;
    int SR1dec = atoi(SR1);
    char * SR1BIN = (char*)malloc(4);
    SR1BIN = decimal_to_binary(SR1dec,3);
    strcat(output, SR1BIN); //SR1BIN is added to output string
    strcat(output, " "); //For easier reading


    //Last token may be a register or an immediate value. This is determined

    if (SR2_imm5[0] == 'R'){ //If first char is an R, it must be a register
        //In this version of ADD, bits 5-3 are 0's.
        strcat(output, "000");
        strcat(output, " "); //For easier reading

        //Same procedure as for other registers
        SR2_imm5++;
        int SR2dec = atoi(SR2_imm5);
        char * SR2BIN = (char*)malloc(4);
        SR2BIN = decimal_to_binary(SR2dec,3);
        strcat(output, SR2BIN);
    } else { //Else it is an immediate value
        //This version of ADD has bit 5 = 1
        strcat(output, "1");
        strcat(output, " "); //For easier reading


        if (SR2_imm5[0] == 'X'){//If it is a hex immediate value


        } else if (SR2_imm5[0] == '#'){ //If it is a decimal immediate value
            //Convert the char array to an integer and back to a char array bit string
            SR2_imm5++; //Delete the #
            int imm5dec = atoi(SR2_imm5);
            char * imm5bin = (char*)malloc(6); //Size i 6 for 5 bit values and 1 array teminator
            imm5bin = decimal_to_binary(imm5dec,5);
            strcat(output, imm5bin);
        }

    }


    printf("\n");
    printf("%s", output);
    return output;
}








void remove_spaces (char* str_trimmed, const char* str_untrimmed)
{
    while (*str_untrimmed != '\0')
    {
        if(!isspace(*str_untrimmed))
        {
            *str_trimmed = *str_untrimmed;
            str_trimmed++;
        }
        str_untrimmed++;
    }
    *str_trimmed = '\0';
}

void evalRegister (const char* regASM, const char* regBIN)
{
    if (regASM[0]=='R'){ //First char should be R
        regASM++;
        //Casting the string-number to an int
        int number = atoi(regASM);


        char * numberBIN = decimal_to_binary(number,3);
        //Converting the int to a string of decimal values

        regBIN= numberBIN;
    }
}

char *decimal_to_binary(int n, int numOfBits)
{
    int c, d, count;
    char *pointer;

    count = 0;
    pointer = (char*)malloc(numOfBits+1);

    if (pointer == NULL)
        exit(EXIT_FAILURE);

    for (c = numOfBits-1 ; c >= 0 ; c--)
    {
        d = n >> c;

        if (d & 1)
            *(pointer+count) = 1 + '0';
        else
            *(pointer+count) = 0 + '0';

        count++;
    }
    *(pointer+count) = '\0';

    return  pointer;
}
















const char * evalAND(char * instruction) {
    //Output is 16 bits long with one array terminator in the end, so 17
    char output[17+4]; //+4 is for testing
    //Makes sure, that output is currently empty
    output[0]='\000';

    //Adds the known opcode
    strcat(output, "0101");
    strcat(output, " "); //For easier reading - can delete later


    //Delete "ADD" (already known) from instruction, so we can separate with commas
    instruction +=3;

    //Separate instruction into comma-separated tokens, e.g. R0, R1, #5
    char * DR = strtok(instruction, ",");
    char * SR1 = strtok(NULL, ",");
    char * SR2_imm5 = strtok(NULL, ",");


    //Converts DR (Destination Register - char array) to bitstring in DrBIN (char array)

    DR++; //Deletes the R in DR, e.g. "R5" -> "5"
    int DRdec = atoi(DR); //Casting the string-number to an int ()

    char * DrBIN = (char*)malloc(4); //Registers use 3 bits in LC3 + 1 bit for array terminator
    DrBIN = decimal_to_binary(DRdec,3);

    strcat(output, DrBIN); //DrBIN is added to output string
    strcat(output, " "); //For easier reading


    //Does the excact same for Source Register 1 (could implement method for this)
    SR1++;
    int SR1dec = atoi(SR1);
    char * SR1BIN = (char*)malloc(4);
    SR1BIN = decimal_to_binary(SR1dec,3);
    strcat(output, SR1BIN); //SR1BIN is added to output string
    strcat(output, " "); //For easier reading


    //Last token may be a register or an immediate value. This is determined

    if (SR2_imm5[0] == 'R'){ //If first char is an R, it must be a register
        //In this version of AND, bits 5-3 are 0's.
        strcat(output, "000");
        strcat(output, " "); //For easier reading

        //Same procedure as for other registers
        SR2_imm5++;
        int SR2dec = atoi(SR2_imm5);
        char * SR2BIN = (char*)malloc(4);
        SR2BIN = decimal_to_binary(SR2dec,3);
        strcat(output, SR2BIN);
    } else { //Else it is an immediate value
        //This version of AND has bit 5 = 1
        strcat(output, "1");
        strcat(output, " "); //For easier reading


        if (SR2_imm5[0] == 'X'){//If it is a hex immediate value


        } else if (SR2_imm5[0] == '#'){ //If it is a decimal immediate value
            //Convert the char array to an integer and back to a char array bit string
            SR2_imm5++; //Delete the #
            int imm5dec = atoi(SR2_imm5);
            char * imm5bin = (char*)malloc(6); //Size i 6 for 5 bit values and 1 array teminator
            imm5bin = decimal_to_binary(imm5dec,5);
            strcat(output, imm5bin);
        }

    }

    printf("\n");
    printf("%s", output);
    return output;
}






