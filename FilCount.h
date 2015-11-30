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
#ifndef FILCOUNT_H
#define FILCOUNT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>

class FilCount{
private:
    std::string _filePath;
    FILE *GCode;
    double totalSize;
public:
    explicit FilCount(std::string filePath) throw (std::string);
    ~FilCount();
    /*=================== getTotalSize() ==========================
        Return used filament in milimeters.
      =============================================================*/
    double getTotalSize();

    /*=================== getFilePath() ===========================
        Return the file path associated with the class.
      =============================================================*/
    std::string getFilePath();

    /*=================== getTimeInSeconds(double speed) ==========
        Given speed (in mm/s), returns the aproximated time
        of the print job.
      =============================================================*/
    long getTimeInSeconds(double speed);
};


#endif // FILCOUNT_H
