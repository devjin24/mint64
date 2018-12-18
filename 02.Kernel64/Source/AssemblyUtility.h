#ifndef __ASSEMBLYUTILITY_H__
#define __ASSEMBLYUTILITY_H__

#include "Types.h"

byte kInPortByte(word wPort);
void kOutPortByte(word wPort, byte bData);

void kLoadGDTR(qword qwGDTRAddress);
void kLoadTR(word wTSSSegmentOffset);
void kLoadIDTR(qword qwIDTRAddress);

void kEnableInterrupt(void);
void kDisableInterrupt(void);
qword kReadRFLAGS(void);

#endif