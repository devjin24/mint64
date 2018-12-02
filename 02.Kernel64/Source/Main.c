#include "Types.h"
#include "Keyboard.h"

void kPrintString(int iX, int iY, const char* pcString);

void Main(void) {
  char vcTemp[2] = {0,};
  byte bFlags;
  byte bTemp;
  int i = 0;

  kPrintString(0,10, "Switch To IA-32e Mode Success~!!");
  kPrintString(0,11, "[PASS] IA-32e C Language Kernel Start.");
  kPrintString(0, 12, "[    ] Keyboard Activate.");

  if(kActivateKeyboard()== true) {
    kPrintString(1,12,"Pass");
    kChangeKeyboardLED(false, false, false);
  } else {
    kPrintString(1,12, "Fail");
    while(1);
  }

  while(1) {
    if(kIsOutputBufferFull() == true ) {
      bTemp = kGetKeyboardScanCode();

      if(kConvertScanCodeToASCIICode(bTemp, &(vcTemp[0]), &bFlags) == true) {
        if(bFlags & KEY_FLAGS_DOWN) {
          kPrintString(i++, 13, vcTemp);
        }
      }
    }
  }
}

void kPrintString(int iX, int iY, const char* pcString) {
  Character* pstScreen = (Character*) 0xB8000;
  int i;

  pstScreen += (iY * 80) + iX;

  for (i = 0; pcString[i] != 0; i++) {
    pstScreen[i].bCharactor = pcString[i];
  }
}