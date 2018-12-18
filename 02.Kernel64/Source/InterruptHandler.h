#ifndef __INTERRUNTHANDLER_H__
#define __INTERRUNTHANDLER_H__

#include "Types.h"

void kCommonExceptionHandler(int iVectorNumber, qword qwErrorCode);
void kCommonInterruptHandler(int iVectorNumber);
void kKeyboardHandler(int iVectorNumber);

#endif