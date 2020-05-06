#include <stdio.h>

int main() {
    char inFileLocation[] = "C:\\lc3\\asm.txt"; //TODO har ikke kunne få det til at virke, hvor filerne ligger i projektroden

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

    char currentString[17];


    fgets(currentString, 17, inStream);
    printf("string is: %s\n", currentString);


    fgets(currentString, 17, inStream);
    printf("string is: %s\n", currentString);


    return 0;
}
