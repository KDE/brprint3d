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

#include "StringRepetierOps.h"

void prepareStringToSend(char *str, const int size)
{
    int i;
    for (i = 0; i < size; i++) {
        if (str[i] == '\0') {
            str[i] = '\n';
            str[i + 1] = '\0';
            break;
        }
    }
}

void restoreSentString(char *str, const int size)
{
    int i;
    for (i = 0; i < size; i++) {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
    }
}

void prepareStringToReceive(char *str, const int size)
{
    int i;
    for (i = 0; i < size; i++) {
        if (str[i] == '\r') {
            str[i] = '\0';
            break;
        }
    }
}

void pointDecimalMarkToComma(char *str, const int size)
{
    int i;
    for (i = 0; str[i] != '\0' && i < size; i++) {
        if (str[i] == '.') {
            str[i] = ',';
        }
    }
}

void commaDecimalMarkToPoint(char *str, const int size)
{
    int i;
    for (i = 0; str[i] != '\0' && i < size; i++) {
        if (str[i] == ',') {
            str[i] = '.';
        }
    }
}
