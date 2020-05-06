#include <stdio.h>

int main() {

    FILE* outStream;
    outStream = fopen("asm2.txt","w");
    if(!outStream){
        printf("%s", "Something is not working with writing to ouput file");
    }

    fprintf(outStream,"ADD SR1,SR2,SR3;\nADD SR2,SR1,SR1;");

    fclose(outStream);



   char inFileLocation[] = "asm2.txt";

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
    int fileSize = ftell(inStream);         // get current file pointer -- wrong! it gets amount of characters in file
    printf("stoerrelsen paa filen %d\n",fileSize);
    fseek(inStream, 0, SEEK_SET);   // seek back to beginning of file

    char currentString[50];


    fgets(currentString, 50, inStream);
    printf("string is: %s", currentString);

    fgets(currentString, 50, inStream);
    printf("string is: %s", currentString);


    return 0;
}
