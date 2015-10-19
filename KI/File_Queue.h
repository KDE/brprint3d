//
//  File_Queue.h
//  KI-C++
//
//  Created by Ayrton Cavalieri de Almeida on 4/07/2015.
//  Copyright (c) 2015 Simple. All rights reserved.
//

#ifndef __KI_C____File_Queue__
#define __KI_C____File_Queue__

#include <cstdlib>
#include <iostream>

class FQueue{
private:
    unsigned long size, np, last, resize;
    void **vector;
public:
    FQueue(unsigned long initialSize, unsigned long resize) throw (std::string);
    ~FQueue();
    void emptyFQueue();
    bool optimizeFQueue() throw (std::string);
    unsigned long getFQueueSize();
    void insertInfo(void *info) throw (std::string);
    void* returnInfo();
    void resetFQueue();
    bool hasFQueueEnded();
};

#endif /* defined(__KI_C____File_Queue__) */
