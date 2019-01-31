#ifndef __UTILITY_H__
#define __UTILITY_H__

#include "Types.h"
#include <stdarg.h>

void kMemSet(void* pvDestination, byte bData, int iSize);
int kMemCpy(void* pvDestination, const void* pvSource, int iSize);
int kMemCmp(const void* pvDestination, const void* pvSource, int iSize);
bool kSetInterruptFlag(bool bEnableInterrupt);
int kStrLen(const char* pcBuffer);
void kCheckTotalRAMSize(void);
qword kGetTotalRAMSize(void);
void kReverseString(char* pcBuffer);
long kAToI(const char* pcBuffer, int iRadix);
qword kHexStringToQword(const char* pcBuffer);
long kDecimalStringToLong(const char* pcBuffer);
int kIToA(long lValue, char* pcBuffer, int iRadix);
int kHexToString(qword qwValue, char* pcBuffer);
int kDecimalToString(long lValue, char*pcBuffer);
int kSPrintf(char* pcBuffer, const char* pcFormatString, ...);
int kVSPrintf(char* pcBuffer, const char* pcFormatString, va_list ap);

#endif