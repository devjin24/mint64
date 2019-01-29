#include "Utility.h"
#include "AssemblyUtility.h"

void kMemSet(void* pvDestination, byte bData, int iSize) {
  int i;
  for(i=0; i < iSize; i++) {
    ((char*) pvDestination)[i] = bData;
  }
}
int kMemCpy(void* pvDestination, const void* pvSource, int iSize) {
  int i;
  for(i=0; i< iSize; i++) {
    ((char*)pvDestination)[i] = ((char*)pvSource)[i];
  }
  return iSize;
}

int kMemCmp(const void* pvDestination, const void* pvSource, int iSize) {
  int i;
  char cTemp;

  for(i = 0; i < iSize; i++) {
    cTemp = ((char*) pvDestination)[i] - ((char*)pvSource)[i];
    if(cTemp != 0) {
      return (int) cTemp;
    }
  }
  return 0;
}

bool kSetInterruptFlag(bool bEnableInterrupt) {
  qword qwRFLAGS;

  qwRFLAGS = kReadRFLAGS();
  if(bEnableInterrupt == true) {
    kEnableInterrupt();
  } else {
    kDisableInterrupt();
  }
  if(qwRFLAGS & 0x0200) {
    return true;
  }
  return false;
}