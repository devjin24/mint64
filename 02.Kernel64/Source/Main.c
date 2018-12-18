#include "Types.h"
#include "Keyboard.h"
#include "Descriptor.h"
#include "PIC.h"

void kPrintString(int iX, int iY, const char* pcString);

void Main(void) {
  char vcTemp[2] = {0,};
  byte bFlags;
  byte bTemp;
  int i = 0;

  kPrintString(0,10, "Switch To IA-32e Mode Success~!!");
  kPrintString(0,11, "[PASS] IA-32e C Language Kernel Start.");

  kPrintString(0, 12, "[    ] GDTI Initialize And Switch For IA-32e Mode.");
  kInitializeGDTTableAndTSS();
  kLoadGDTR(GDTR_STARTADDRESS);
  kPrintString(1, 12, "Pass");

  kPrintString(0, 13, "[    ] TSS Segment Load.");
  kLoadTR(GDT_TSSSEGMENT);
  kPrintString(1,13, "Pass");

  kPrintString(0, 14, "[    ] IDT Initialize.");
  kInitializeIDTTables();
  kLoadIDTR(IDTR_STARTADDRESS);
  kPrintString(1, 14,"Pass");
  kPrintString(0, 15, "[    ] Keyboard Activate.");

  if(kActivateKeyboard()== true) {
    kPrintString(1,15,"Pass");
    kChangeKeyboardLED(false, false, false);
  } else {
    kPrintString(1,15, "Fail");
    while(1);
  }

  kPrintString(0, 16, "[    ] PIC Controller And Interrupt Initialize.");
  kInitializePIC();
  kMaskPICInterrupt(0);
  kEnableInterrupt();
  kPrintString(1,16, "Pass");

  while(1) {
    if(kIsOutputBufferFull() == true ) {
      bTemp = kGetKeyboardScanCode();

      if(kConvertScanCodeToASCIICode(bTemp, &(vcTemp[0]), &bFlags) == true) {
        if(bFlags & KEY_FLAGS_DOWN) {
          kPrintString(i++, 17, vcTemp);
          if(vcTemp[0] == '0') {
            bTemp = bTemp / 0;
          }
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