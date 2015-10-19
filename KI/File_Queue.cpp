//
//  File_Queue.cpp
//  KI-C++
//
//  Created by Ayrton Cavalieri de Almeida on 4/07/2015.
//  Copyright (c) 2015 Simple. All rights reserved.
//

#include "File_Queue.h"

FQueue::FQueue(unsigned long initialSize, unsigned long resize) throw (std::string){
    this->size = initialSize;
    this->resize = resize;
    this->np = this->last = 0;
    this->vector = (void**)malloc(this->size * sizeof(void*));
    if(this->vector == NULL){
        std::string exc = "FQueue: Could not allocate memory.";
        throw exc;
    }
    for(int i = 0; i < this->size; i++){
        this->vector[i] = NULL;
    }
}

FQueue::~FQueue(){
    this->emptyFQueue();
    free(this->vector);
}

void FQueue::emptyFQueue(){
    for(int i = 0; i < this->size && vector[i] != NULL; i++){
        free(vector[i]);
        vector[i] = NULL;
    }
    this->last = 0;
    this->np = 0;
    this->size = 0;
    this->resize = 0;
}

bool FQueue::optimizeFQueue() throw (std::string){
    void **temp;
    if(this->last < this->size){
        temp = (void**)malloc(this->last * sizeof(void*));
        if(temp == NULL){
            std::string exc = "FQueue: Could not optmize.";
            throw exc;
        }
        for(unsigned int i = 0; i < this->last; i++){
            temp[i] = this->vector[i];
        }
        free(this->vector);
        this->vector = temp;
        this->size = this->last;
        return true;
    }
    return false;
}

unsigned long FQueue::getFQueueSize(){
    return this->size;
}

void FQueue::insertInfo(void *info) throw (std::string){
    void **temp;
    if(this->last < this->size){
        this->vector[this->last] = info;
        this->last++;
    }else{
        temp = (void**)malloc((size + resize) * sizeof(void*));
        if(temp == NULL){
            std::string exc = "FQueue: Could not reallocate space.";
            throw exc;
        }
        this->size+=this->resize;
        for(unsigned int i = 0; i < this->size; i++){
            if(i < last){
                temp[i] = this->vector[i];
            }else{
                temp[i] = NULL;
            }
        }
        free(this->vector);
        this->vector = temp;
        this->vector[this->last] = info;
        this->last++;
    }
}

void* FQueue::returnInfo(){
    void *temp;
    temp = this->vector[this->np];
    this->np++;
    return temp;
}

void FQueue::resetFQueue(){
    this->np = 0;
}

bool FQueue::hasFQueueEnded(){
    return this->np == this->last ? true : false;
}
