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

#include "FilCount.h"

FilCount::FilCount(const char *filePath) throw (std::string)
{
    char instring[100001], *X, *Y, *Z;
    bool first = true;
    double vX[2], vY[2], vZ[2] /*0 - Inicial, 1 - Final*/, temp;
    this->GCode = fopen(filePath, "rt");
    if(this->GCode == NULL){
        std::string exc = "Could not open the file: ";
        exc+=filePath;
        exc+=".";
        throw exc;
    }
    this->filePath = (char*)malloc((strlen(filePath) + 1) * sizeof(char));
    strcpy(this->filePath, filePath);
    this->totalSize = 0.0;
    while(fscanf(this->GCode, "%[^\n]\n", instring) != EOF){
        if(!first){
            if(instring[0] == 'G'){
                X = strstr(instring, "X");
                if(X != NULL){
                    sscanf(X, "X%lf", &vX[1]);
                }else{
                    vX[1] = vX[0];
                }
                Y = strstr(instring, "Y");
                if(Y != NULL){
                    sscanf(Y, "Y%lf", &vY[1]);
                }else{
                    vY[1] = vY[0];
                }
                temp = sqrt(pow((vX[1] - vX[0]),2) + pow((vY[1] - vY[0]), 2));
                vX[0] = vX[1];
                vY[0] = vY[1];
                Z = strstr(instring, "Z");
                if(Z != NULL){
                    sscanf(Z, "Z%lf", &vZ[1]);
                    this->totalSize += sqrt(pow(temp, 2) + pow((vZ[1] - vZ[0]), 2));
                    vZ[0] = vZ[1];
                }else{
                    this->totalSize += temp;
                }
            }
        }else{
            if(instring[0] == 'G'){
                X = strstr(instring, "X");
                if(X == NULL){
                    vX[0] = vX[1] = 0;
                }else{
                    sscanf(X, "X%lf", &vX[0]);
                }
                Y = strstr(instring, "Y");
                if(Y == NULL){
                    vY[0] = vY[1] = 0;
                }else{
                    sscanf(Y, "Y%lf", &vY[0]);
                }
                Z = strstr(instring, "Z");
                if(Z == NULL){
                    vZ[0] = vZ[1] = 0;
                }else{
                    sscanf(Z, "Z%lf", &vZ[0]);
                }
                first = false;
            }
        }
    }
}

FilCount::~FilCount()
{
    free(this->filePath);
    this->filePath = NULL;
    this->totalSize = 0.0;
    fclose(this->GCode);
    this->GCode = NULL;
}

double FilCount::getTotalSize()
{
    return this->totalSize;
}

std::string FilCount::getFilePath()
{
    std::string ret = this->filePath;
    return ret;
}

long FilCount::getTimeInSeconds(double speed)
{
    return (long)(this->totalSize/speed);
}
