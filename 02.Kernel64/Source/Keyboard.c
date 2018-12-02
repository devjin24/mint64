#include "Types.h"
#include "AssemblyUtility.h"
#include "Keyboard.h"

bool kIsOutputBufferFull(void) {
  if(kInPortByte(0x64) & 0x01) {
    return true;
  }
  return false;
}

bool kIsInputBufferFull(void) {
  if(kInPortByte(0x64) & 0x02) {
    return true;
  }
  return false;
}

bool kActivateKeyboard(void) {
  int i;
  int j;

  kOutPortByte(0x64, 0xAE);

  for(i = 0; i < 0xFFFF; i ++) {
    if(kIsInputBufferFull() == false) {
      break;
    }
  }

  kOutPortByte(0x60, 0xF4);

  for(j=0; j<100; j++) {
    for(i=0; i<0xFFFF; i++) {
      if(kIsOutputBufferFull() == true) {
        break;
      }
    }
    if(kInPortByte(0x60) == 0xFA) {
      return true;
    }
  }
  return false;
}

byte kGetKeyboardScanCode(void) {
  while(kIsOutputBufferFull() == false) {
    ;
  }

  return kInPortByte(0x60);
}

bool kChangeKeyboardLED(bool bCapsLockOn, bool bNumLockOn, bool bScrollLockOn) {
  int i,j;

  for(i=0; i<0xFFFF; i++) {
    if(kIsInputBufferFull()==false) {
      break;
    }
  }

  kOutPortByte(0x60, 0xED);

  for(i=0; i<0xFFFF; i++) {
    if(kIsInputBufferFull() == false) {
      break;
    }
  }

  for(j=0; j<100; j++) {
    for(i=0; i< 0xFFFF;i++) {
      if(kIsInputBufferFull() == true) {
        break;
      }
    }

    if(kInPortByte(0x60) == 0xFA) {
      break;
    }
  }

  if(j>= 100) {
    return false;
  }
  kOutPortByte(0x60, (bCapsLockOn << 2) | (bNumLockOn<<1) | bScrollLockOn);
  for(i=0; i<0xFFFF;i++) {
    if(kIsInputBufferFull() == false) {
      break;
    }
  }

  for(j=0; j<100; j++) {
    for(i=0;i < 0xFFFF; i++) {
      if(kIsOutputBufferFull() == true) {
        break;
      }
    }
    if(kInPortByte(0x60) == 0xFA) {
      break;
    }
  }
  if (j >= 100 ) {
    return false;
  }
  return true;
}

void kEnableA20Gate(void) {
  byte bOutputPortData;
  int i;

  kOutPortByte(0x64, 0xD0);

  for(i=0;i<0xFFFF;i++) {
    if(kIsOutputBufferFull() == true) {
      break;
    }
  }

  bOutputPortData = kInPortByte(0x60);
  bOutputPortData |= 0x01;

  for(i=0; i<0xFFFF; i++) {
    if(kIsInputBufferFull() == false) {
      break;
    }
  }

  kOutPortByte(0x64, 0xD1);
  kOutPortByte(0x60, bOutputPortData);
}

void kReboot(void) {
  int i;

  for(i=0; i<0xFFFF; i++) {
    if(kIsInputBufferFull() == false) {
      break;
    }
  }

  kOutPortByte(0x64, 0xD1);
  kOutPortByte(0x64, 0x00);

  while(1) {;}
}

static KEYBOARDMANAGER gs_stKeyboardManager = { 0, };

static KEYMAPPINGENTRY gs_vstKeyMappingTable[ KEY_MAPPINGTABLEMAXCOUNT ] =
{
    /*  0   */  {   KEY_NONE        ,   KEY_NONE        },
    /*  1   */  {   KEY_ESC         ,   KEY_ESC         },
    /*  2   */  {   '1'             ,   '!'             },
    /*  3   */  {   '2'             ,   '@'             },
    /*  4   */  {   '3'             ,   '#'             },
    /*  5   */  {   '4'             ,   '$'             },
    /*  6   */  {   '5'             ,   '%'             },
    /*  7   */  {   '6'             ,   '^'             },
    /*  8   */  {   '7'             ,   '&'             },
    /*  9   */  {   '8'             ,   '*'             },
    /*  10  */  {   '9'             ,   '('             },
    /*  11  */  {   '0'             ,   ')'             },
    /*  12  */  {   '-'             ,   '_'             },
    /*  13  */  {   '='             ,   '+'             },
    /*  14  */  {   KEY_BACKSPACE   ,   KEY_BACKSPACE   },
    /*  15  */  {   KEY_TAB         ,   KEY_TAB         },
    /*  16  */  {   'q'             ,   'Q'             },
    /*  17  */  {   'w'             ,   'W'             },
    /*  18  */  {   'e'             ,   'E'             },
    /*  19  */  {   'r'             ,   'R'             },
    /*  20  */  {   't'             ,   'T'             },
    /*  21  */  {   'y'             ,   'Y'             },
    /*  22  */  {   'u'             ,   'U'             },
    /*  23  */  {   'i'             ,   'I'             },
    /*  24  */  {   'o'             ,   'O'             },
    /*  25  */  {   'p'             ,   'P'             },
    /*  26  */  {   '['             ,   '{'             },
    /*  27  */  {   ']'             ,   '}'             },
    /*  28  */  {   '\n'            ,   '\n'            },
    /*  29  */  {   KEY_CTRL        ,   KEY_CTRL        },
    /*  30  */  {   'a'             ,   'A'             },
    /*  31  */  {   's'             ,   'S'             },
    /*  32  */  {   'd'             ,   'D'             },
    /*  33  */  {   'f'             ,   'F'             },
    /*  34  */  {   'g'             ,   'G'             },
    /*  35  */  {   'h'             ,   'H'             },
    /*  36  */  {   'j'             ,   'J'             },
    /*  37  */  {   'k'             ,   'K'             },
    /*  38  */  {   'l'             ,   'L'             },
    /*  39  */  {   ';'             ,   ':'             },
    /*  40  */  {   '\''            ,   '\"'            },
    /*  41  */  {   '`'             ,   '~'             },
    /*  42  */  {   KEY_LSHIFT      ,   KEY_LSHIFT      },
    /*  43  */  {   '\\'            ,   '|'             },
    /*  44  */  {   'z'             ,   'Z'             },
    /*  45  */  {   'x'             ,   'X'             },
    /*  46  */  {   'c'             ,   'C'             },
    /*  47  */  {   'v'             ,   'V'             },
    /*  48  */  {   'b'             ,   'B'             },
    /*  49  */  {   'n'             ,   'N'             },
    /*  50  */  {   'm'             ,   'M'             },
    /*  51  */  {   ','             ,   '<'             },
    /*  52  */  {   '.'             ,   '>'             },
    /*  53  */  {   '/'             ,   '?'             },
    /*  54  */  {   KEY_RSHIFT      ,   KEY_RSHIFT      },
    /*  55  */  {   '*'             ,   '*'             },
    /*  56  */  {   KEY_LALT        ,   KEY_LALT        },
    /*  57  */  {   ' '             ,   ' '             },
    /*  58  */  {   KEY_CAPSLOCK    ,   KEY_CAPSLOCK    },
    /*  59  */  {   KEY_F1          ,   KEY_F1          },
    /*  60  */  {   KEY_F2          ,   KEY_F2          },
    /*  61  */  {   KEY_F3          ,   KEY_F3          },
    /*  62  */  {   KEY_F4          ,   KEY_F4          },
    /*  63  */  {   KEY_F5          ,   KEY_F5          },
    /*  64  */  {   KEY_F6          ,   KEY_F6          },
    /*  65  */  {   KEY_F7          ,   KEY_F7          },
    /*  66  */  {   KEY_F8          ,   KEY_F8          },
    /*  67  */  {   KEY_F9          ,   KEY_F9          },
    /*  68  */  {   KEY_F10         ,   KEY_F10         },
    /*  69  */  {   KEY_NUMLOCK     ,   KEY_NUMLOCK     },
    /*  70  */  {   KEY_SCROLLLOCK  ,   KEY_SCROLLLOCK  },

    /*  71  */  {   KEY_HOME        ,   '7'             },
    /*  72  */  {   KEY_UP          ,   '8'             },
    /*  73  */  {   KEY_PAGEUP      ,   '9'             },
    /*  74  */  {   '-'             ,   '-'             },
    /*  75  */  {   KEY_LEFT        ,   '4'             },
    /*  76  */  {   KEY_CENTER      ,   '5'             },
    /*  77  */  {   KEY_RIGHT       ,   '6'             },
    /*  78  */  {   '+'             ,   '+'             },
    /*  79  */  {   KEY_END         ,   '1'             },
    /*  80  */  {   KEY_DOWN        ,   '2'             },
    /*  81  */  {   KEY_PAGEDOWN    ,   '3'             },
    /*  82  */  {   KEY_INS         ,   '0'             },
    /*  83  */  {   KEY_DEL         ,   '.'             },
    /*  84  */  {   KEY_NONE        ,   KEY_NONE        },
    /*  85  */  {   KEY_NONE        ,   KEY_NONE        },
    /*  86  */  {   KEY_NONE        ,   KEY_NONE        },
    /*  87  */  {   KEY_F11         ,   KEY_F11         },
    /*  88  */  {   KEY_F12         ,   KEY_F12         }
};

bool kIsAlphabetScanCode(byte bScanCode) {
  if(('a' <= gs_vstKeyMappingTable[bScanCode].bNormalCode) && 
  (gs_vstKeyMappingTable[bScanCode].bNormalCode <= 'z')) {
    return true;
  }
  return false;
}

bool kIsNumberOrSymbolScanCode(byte bScanCode) {
  if((2 <= bScanCode) && (bScanCode <= 53) &&
  (kIsAlphabetScanCode(bScanCode) == false) ) {
    return true;
  }
  return false;
}

bool kIsNumberPadScanCode(byte bScanCode) {
  if((71 <= bScanCode) && (bScanCode<=83)) {
    return true;
  }
  return false;
}

bool kIsUseCombinedCode(byte bScanCode) {
  byte bDownScanCode;
  bool bUseCombinedKey = false;

  bDownScanCode = bScanCode & 0x7F;
  if(kIsAlphabetScanCode(bDownScanCode) == true) {
    if(gs_stKeyboardManager.bShiftDown ^ gs_stKeyboardManager.bCapsLockDown) {
      bUseCombinedKey = true;
    } else {
      bUseCombinedKey = false;
    }
  } else if (kIsNumberOrSymbolScanCode(bDownScanCode) == true) { 
    if(gs_stKeyboardManager.bShiftDown == true) {
      bUseCombinedKey = true;
    } else {
      bUseCombinedKey = false;
    }
  } else if ((kIsNumberPadScanCode(bDownScanCode) == true) && 
  (gs_stKeyboardManager.bExtendedCodeIn == false)) {
    if(gs_stKeyboardManager.bNumLockDown == true) {
      bUseCombinedKey = true;
    } else {
      bUseCombinedKey = false;
    }
  }

  return bUseCombinedKey;
}

void UpdateCombiationKeyStatusAndLED(byte bScanCode) {
  bool bDown;
  byte bDownScanCode;
  bool bLEDStatusChanged = false;

  if (bScanCode & 0x80) {
    bDown = false;
    bDownScanCode = bScanCode & 0x7F;
  } else {
    bDown = true;
    bDownScanCode = bScanCode;
  }

  if((bDownScanCode == 42) || (bDownScanCode == 54)) {
    gs_stKeyboardManager.bShiftDown = bDown;
  } else if ((bDownScanCode == 58) && (bDown == true)) {
    gs_stKeyboardManager.bCapsLockDown ^= true;
    bLEDStatusChanged = true;
  } else if ((bDownScanCode == 69) && (bDown == true)) {
    gs_stKeyboardManager.bNumLockDown ^= true;
    bLEDStatusChanged = true;
  } else if ((bDownScanCode == 70) && (bDown == true)) {
    gs_stKeyboardManager.bScrollLockDown ^= true;
    bLEDStatusChanged = true;
  }

  if(bLEDStatusChanged == true) {
    kChangeKeyboardLED(gs_stKeyboardManager.bCapsLockDown, 
      gs_stKeyboardManager.bNumLockDown, gs_stKeyboardManager.bScrollLockDown);
  }
}

bool kConvertScanCodeToASCIICode(byte bScanCode, byte* pbASCIICode, bool* pbFlags){
  bool bUseCombinedKey;

  if(gs_stKeyboardManager.iSkipCountForPause >0) {
    gs_stKeyboardManager.iSkipCountForPause--;
    return false;
  }

  if(bScanCode== 0xE1) {
    *pbASCIICode = KEY_PAUSE;
    *pbFlags = KEY_FLAGS_DOWN;
    gs_stKeyboardManager.iSkipCountForPause = KEY_SKIPCOUNTFORPAUSE;
    return true;
  } else if (bScanCode == 0xE0) {
    gs_stKeyboardManager.bExtendedCodeIn = true;
    return false;
  }

  bUseCombinedKey = kIsUseCombinedCode(bScanCode);
  
  if(bUseCombinedKey == true) {
    *pbASCIICode = gs_vstKeyMappingTable[bScanCode & 0x7F].bCombinedCode;
  } else {
    *pbASCIICode = gs_vstKeyMappingTable[bScanCode & 0x7F].bNormalCode;
  }

  if(gs_stKeyboardManager.bExtendedCodeIn == true) {
    *pbFlags = KEY_FLAGS_EXTENDEDKEY;
    gs_stKeyboardManager.bExtendedCodeIn = false;
  } else {
    *pbFlags = 0;
  }

  if((bScanCode & 0x80) == 0) {
    *pbFlags |= KEY_FLAGS_DOWN;
  }

  UpdateCombiationKeyStatusAndLED(bScanCode);
  return true;
}