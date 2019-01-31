#include "Types.h"
#include "Keyboard.h"
#include "Descriptor.h"
#include "PIC.h"
#include "Console.h"
#include "ConsoleShell.h"

void kPrintString(int iX, int iY, const char* pcString);

void Main(void) {
  int iCursorX, iCursorY;

  kInitializeConsole(0, 10);
  kPrintf("Switch To IA-32e Mode Success~!!\n");
  kPrintf("[Pass] IA-32e C Language Kernel Start.\n");
  kPrintf("[Pass] Initialize Console.\n");

  kGetCursor(&iCursorX, &iCursorY);
  kPrintf("[    ] GDTI Initialize And Switch For IA-32e Mode.");
  kInitializeGDTTableAndTSS();
  kLoadGDTR(GDTR_STARTADDRESS);
  kSetCursor(1, iCursorY++);
  kPrintf("Pass\n");

  kPrintf("[    ] TSS Segment Load.");
  kLoadTR(GDT_TSSSEGMENT);
  kSetCursor(1, iCursorY++);
  kPrintf("Pass\n");

  kPrintf("[    ] IDT Initialize.");
  kInitializeIDTTables();
  kLoadIDTR(IDTR_STARTADDRESS);
  kSetCursor(1, iCursorY++);
  kPrintf("Pass\n");

  kPrintf("[    ] Keyboard Activate And Queue Initialize.");
  if(kInitializeKeyboard()== true) {
    kSetCursor(1, iCursorY++);
    kPrintf("Pass\n");
    kChangeKeyboardLED(false, false, false);
  } else {
    kSetCursor(1, iCursorY++);
    kPrintf("Fail\n");
    while(1);
  }

  kPrintf("[    ] PIC Controller And Interrupt Initialize.");
  kInitializePIC();
  kMaskPICInterrupt(0);
  kEnableInterrupt();
  kSetCursor(1, iCursorY++);
  kPrintf("Pass\n");

  kStartConsoleShell();
}
void kPrintString(int iX, int iY, const char* pcString) {
  Character* pstScreen = (Character*) 0xB8000;
  int i;

  pstScreen += (iY * 80) + iX;

  for (i = 0; pcString[i] != 0; i++) {
    pstScreen[i].bCharactor = pcString[i];
  }
}