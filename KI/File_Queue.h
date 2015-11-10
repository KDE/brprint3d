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

#ifndef __KI_C____File_Queue__
#define __KI_C____File_Queue__

#include <cstdlib>
#include <iostream>

class FQueue
{
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
