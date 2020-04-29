#include <stdio.h>
#include "helpFunctions.h"
#include "instructions.h"



void evalTest();

int main() {
    //printf("Hello, World!\n");

    //char output[100] = {0};
    //char eksempel[] = "hejmaltehej";
    //evalTest(eksempel, output);
    char UpperCase[20] = {0}; // et char array som er initialiseret til at være 0'er
    char testLowerCase[] = "mmDaRiaedhaEjd";

    StrToUpper(testLowerCase, UpperCase);

    printf("%s \n",UpperCase);
    //printf("%s",output);

    char bits[13]={0}; // output char array
    int testToDecimal = 13; //test value

    DecimalToBinary(testToDecimal, 13, bits);

    printf("%s", bits);


    return 0;
}


void evalTest(char * input, char * output){
    for (int i =0; i<11;i++){
        output[i] = input[i] - 32;
    }
    //output[11]='\0';
}














