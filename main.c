#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void evalADD_AND();
void evalNOT();
void evalLDR();
void evalInstruction();

const char * deleteSpaces();
void remove_spaces ();
void strToUpper ();
void evalRegister ();
char *decimal_to_binary();



int main() {

    //Some tests instructions
    //char line[] = "add R1, R2, #-5";
    //char line[] = "NOT R2, R0";
    char line[] = "LDR R2, R0, #17";
    //char line[] = "add R1, R2, R3";


    //To get the output of evalInstruction(), we must pass the pointer of the output to the function
    //The function can then store it's output at the address, pOutput points to, which can still be acessed in main
    char * output;
    char ** pOutput = &output;
    evalInstruction(line,pOutput);

    printf(output);




    return 0;
}


void evalInstruction(char * input, char ** pInput){
    char * output;
    char ** pOutput = &output;


    //Delete all space characters from instruction
    int len = strlen(input) + 1;
    char inputTrimmed[len];
    remove_spaces(inputTrimmed,input);


    //Convert all letters to uppercase
    int newLen = strlen(inputTrimmed) + 1;
    char inputUpper[newLen];
    strToUpper(inputUpper,inputTrimmed);


    char * instruction = inputUpper;

    if(strstr(instruction, "ADD") != NULL || strstr(instruction, "AND") != NULL) {
        //If instruction contains "ADD" or "AND" (They are almost identical)
        printf("Det er en ADD/AND instruktion\n");
        evalADD_AND(instruction,pOutput);

    } else if (strstr(instruction, "NOT") != NULL){ //If instruction contains "NOT"
        printf("Det er en NOT instruktion\n");
        evalNOT(instruction,pOutput);
    } else if (strstr(instruction, "LDR") != NULL){ //If instruction contains "LDR"
        printf("Det er en LDR instruktion\n");
        evalLDR(instruction,pOutput);
    }

    * pInput = output;



}

void evalADD_AND(char * instruction, char ** pInput) {

    //Output is 16 bits long with one array terminator in the end, so 17
    char output[17+4]; //+4 is for testing
    //Makes sure, that output is currently empty
    output[0]='\000';

    //Determines if it is ADD or AND
    if (instruction[1]== 'N'){ //AND
        //Adds the opcode of ADD
        strcat(output, "0001");
        strcat(output, " "); //For easier reading - can delete later
    } else{ //ADD
        //Adds the opcode of AND
        strcat(output, "0101");
        strcat(output, " "); //For easier reading - can delete later
    }


    //Delete "ADD"/"AND" (already processed) from instruction, so we can separate with commas
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

    * pInput = output;
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

void strToUpper (char* strUpper, const char* strNotUpper)
{
    while (*strNotUpper != '\0')
    {
        if(*strNotUpper>=97 && *strNotUpper<=122)
        {
            *strUpper = *strNotUpper - 32;
        } else{
            *strUpper = *strNotUpper;
        }
        strUpper++;
        strNotUpper++;
    }
    *strUpper = '\0';
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
    pointer = (char*)malloc(numOfBits+1); //den laver en pointer til char array
                                                //som er af variabel længde dvs antallet
                                                //af bits + 1 (den ene er til et 0)

    if (pointer == NULL)
        exit(EXIT_FAILURE);

    for (c = numOfBits-1 ; c >= 0 ; c--)        //et loop som itererer gennem så længe at
                                                //antallet af bits er større end 0
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

/*

void registerToBin(char * Register){
    //Deletes the "R"
    Register++;

    //Converts number to int
    int RegDec = atoi(Register);

    //Allocates space for binary number of size 3 + "\0"
    char * RegBin = (char*)malloc(4);
    RegBin = decimal_to_binary(RegDec,3);

    Register = & RegBin;

}


 */


void evalNOT(char * instruction, char ** pInput) {

    //Output is 16 bits long with one array terminator in the end, so 17
    char output[17+4]; //+4 is for testing
    //Makes sure, that output is currently empty
    output[0]='\000';

    //Adds the opcode of NOT
    strcat(output, "1001");
    strcat(output, " "); //For easier reading - can delete later


    //Delete "NOT" (already processed) from instruction, so we can separate with commas
    instruction +=3;

    //Separate instruction into comma-separated tokens, e.g. R0, R1, #5
    char * DR = strtok(instruction, ",");
    char * SR = strtok(NULL, ",");

    //Converts DR (Destination Register - char array) to bitstring in DrBIN (char array)

    DR++; //Deletes the R in DR, e.g. "R5" -> "5"
    int DRdec = atoi(DR); //Casting the string-number to an int ()

    char * DrBIN = (char*)malloc(4); //Registers use 3 bits in LC3 + 1 bit for array terminator
    DrBIN = decimal_to_binary(DRdec,3);

    strcat(output, DrBIN); //DrBIN is added to output string
    strcat(output, " "); //For easier reading


    //Does the exact same for Source Register 1 (could implement method for this)
    SR++;
    int SR1dec = atoi(SR);
    char * SR1BIN = (char*)malloc(4);
    SR1BIN = decimal_to_binary(SR1dec,3);
    strcat(output, SR1BIN); //SR1BIN is added to output string
    strcat(output, " "); //For easier reading

    //Last 6 bits in NOT are 1's
    strcat(output, "111111");

    * pInput = output;
}

void evalLDR(char * instruction, char ** pInput) {

    //Output is 16 bits long with one array terminator in the end, so 17
    char output[17+4]; //+4 is for testing
    //Makes sure, that output is currently empty
    output[0]='\000';

    //Adds the opcode of NOT
    strcat(output, "0110");
    strcat(output, " "); //For easier reading - can delete later


    //Delete "LDR" (already processed) from instruction, so we can separate with commas
    instruction +=3;

    //Separate instruction into comma-separated tokens, e.g. R0, R1, #5
    char * DR = strtok(instruction, ",");
    char * BaseR = strtok(NULL, ",");
    char * Offset6 = strtok(NULL, ",");

    //Converts DR to bitstring in DrBIN

    DR++; //Deletes the R in DR, e.g. "R5" -> "5"
    int DRdec = atoi(DR); //Casting the string-number to an int ()

    char * DrBIN = (char*)malloc(4); //Registers use 3 bits in LC3 + 1 bit for array terminator
    DrBIN = decimal_to_binary(DRdec,3);

    strcat(output, DrBIN); //DrBIN is added to output string
    strcat(output, " "); //For easier reading


    //Does the exact same for Source Register 1 (could implement method for this)
    BaseR++;
    int BaseRdec = atoi(BaseR);
    char * BaseRBIN = (char*)malloc(4);
    BaseRBIN = decimal_to_binary(BaseRdec,3);
    strcat(output, BaseRBIN); //SR1BIN is added to output string
    strcat(output, " "); //For easier reading

    //Last 6 bits in NOT are Offset6
    if (Offset6[0] == 'X'){//If it is a hex offset value


    } else if (Offset6[0] == '#'){ //If it is a decimal offset value
        //Convert the char array to an integer and back to a char array bit string
        Offset6++; //Delete the #
        int Offset6dec = atoi(Offset6);
        char * Offset6bin = (char*)malloc(6); //Size i 6 for 5 bit values and 1 array teminator
        Offset6bin = decimal_to_binary(Offset6dec,6);
        strcat(output, Offset6bin);
    }



    * pInput = output;
}























