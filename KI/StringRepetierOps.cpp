//
//  StringRepetierOps.cpp
//  KI-C++
//
//  Created by Ayrton Cavalieri de Almeida on 3/09/2015.
//  Copyright (c) 2015 Simple. All rights reserved.
//

#include "StringRepetierOps.h"

void prepareStringToSend(char *str, const int size){
    int i;
    for(i = 0; i < size; i++){
        if(str[i] == '\0'){
            str[i] = '\n';
            str[i+1] = '\r';
            str[i+2] = '\0';
            break;
        }
    }
}

void restoreSentString(char *str, const int size){
    int i;
    for(i = 0; i < size; i++){
        if(str[i] == '\n'){
            str[i] = '\0';
            break;
        }
    }
}

void prepareStringToReceive(char *str, const int size){
    int i;
    for(i = 0; i < size; i++){
        if(str[i] == '\r'){
            str[i] = '\0';
            break;
        }
    }
}

void pointDecimalMarkToComma(char *str, const int size){
    int i;
    for(i = 0;str[i] != '\0' && i < size; i++){
        if(str[i] == '.'){
            str[i] = ',';
        }
    }
}

void commaDecimalMarkToPoint(char *str, const int size){
    int i;
    for(i = 0;str[i] != '\0' && i < size; i++){
        if(str[i] == ','){
            str[i] = '.';
        }
    }
}
