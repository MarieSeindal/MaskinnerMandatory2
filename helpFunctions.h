//
// Created by marie on 26-04-2020.
//

#ifndef MASKINNERMANDATORY2_HELPFUNCTIONS_H
#define MASKINNERMANDATORY2_HELPFUNCTIONS_H

#include <string.h>
#endif //MASKINNERMANDATORY2_HELPFUNCTIONS_H






void StrToUpper(char * lowerCase, char * upperCase){
    int j = strlen(lowerCase);

    for (int i =0; i<j;i++){
        if(lowerCase[i] < 91 && lowerCase[i] > 64){ //hvis de allerede er uppercase
            upperCase[i] = lowerCase[i];
        }else {
            upperCase[i] = lowerCase[i] - 32;
        }
    }
 }








