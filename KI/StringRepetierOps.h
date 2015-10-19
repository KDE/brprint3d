//
//  StringRepetierOps.h
//  KI-C++
//
//  Created by Ayrton Cavalieri de Almeida on 3/09/2015.
//  Copyright (c) 2015 Simple. All rights reserved.
//

#ifndef __KI_C____StringRepetierOps__
#define __KI_C____StringRepetierOps__

void prepareStringToSend(char *str, const int size);
void restoreSentString(char *str, const int size);
void prepareStringToReceive(char *str, const int size);
void pointDecimalMarkToComma(char *str, const int size);
void commaDecimalMarkToPoint(char *str, const int size);

#endif /* defined(__KI_C____StringRepetierOps__) */
