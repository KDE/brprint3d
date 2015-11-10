/*=====================================================================

 BRPrint3D, Open Source 3D Printing Host

 (c) 2015 BRPrint3D Authors 

 This file is part of the BRPrint3D project

 BRPrint3D is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 BRPrint3D is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with BRPrint3D. If not, see <http://www.gnu.org/licenses/>.

 ======================================================================*/

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
