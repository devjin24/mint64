#ifndef __MODESWITCH_H__
#define __MODESWITCH_H__

#include "Types.h"

void kReadCPUID(dword dwEAX, dword* pdwEAX, dword* pdwEBX, dword* pdwECX, dword* pdwEDX);
void kSwitchAndExecute64bitKernel(void);

#endif