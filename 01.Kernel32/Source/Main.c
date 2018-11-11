#include "Types.h"

void kPrintString( int iX, int iY, const char* pcString);
bool kInitializeKernel64Area(void);

void Main( void) {
  kPrintString(0, 3, "C Language Kernel Started~!!!");

  kInitializeKernel64Area();
  kPrintString(0,4, "IA-32e Kernel Area Initialization Complete");
  while(1);
}

void kPrintString( int iX, int iY, const char* pcString) {
  Character* pstScreen = (Character*) 0xB8000;
  int i;

  pstScreen += (iY * 80) + iX;
  for(i = 0; pcString[i] != 0;i ++) {
    pstScreen[i].bCharactor = pcString[i];
  }
}

bool kInitializeKernel64Area(void) {
  dword* pdwCurrentAddress;
  pdwCurrentAddress = (dword*) 0x100000;

  while((dword)pdwCurrentAddress < 0x600000) {
    *pdwCurrentAddress = 0x00;

    if(*pdwCurrentAddress != 0) {
      return false;
    }
    pdwCurrentAddress++;
  }

  return true;
}