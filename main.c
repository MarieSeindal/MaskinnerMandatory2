#include <stdio.h>
#include "helpFunctions.h"
#include "instructions.h"



void evalTest();

int main() {
   char binary[16+5] = {0};
   char TestAssembly[] = "ADDR1,R2,R2";
   evalADD(TestAssembly,binary);
   printf("Hehehhehe + %s", binary);
   EvalInstruction(TestAssembly, binary);






    char UpperCase[20] = {0}; // et char array som er initialiseret til at være 0'er
    char testLowerCase[] = "mmDaRiaedhaEjd";


    StrToUpper(testLowerCase, UpperCase);

    printf("%s \n",UpperCase);
    //printf("%s",output);

    char bits[13]={0}; // output char array
    int testToDecimal = -13; //test value MAX 4095

    decimalToBinary2(testToDecimal, 6, bits);
    DecimalToBinary(testToDecimal, 6, bits);


    printf("%s", bits);


    return 0;
}


void evalTest(char * input, char * output){
    for (int i =0; i<11;i++){
        output[i] = input[i] - 32;
    }
    //output[11]='\0';
}














