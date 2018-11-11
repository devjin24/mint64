#include "Types.h"
#include "Page.h"

void kPrintString( int iX, int iY, const char* pcString);
bool kInitializeKernel64Area(void);
bool kIsMemoryEnough(void);

void Main( void) {
	dword i;

	kPrintString(0, 3, "[Pass] C Language Kernel Start.");

	kPrintString(0, 4, "[    ] Minimum Memory Size Check.");
	if (kIsMemoryEnough() == false) {
		kPrintString(1,4, "Fail");
		kPrintString(0, 5, "Not enough Memory~!! MINT64 OS Requires Over 64MByte Memory~!!");
		while(1);
	} else {
		kPrintString(1,4, "Pass");
	}

	kPrintString(0,5, "[    ] IA-32e Kernel Area Initialize.");
	if(kInitializeKernel64Area() == false) {
		kPrintString(1,5, "Fail");
		kPrintString(0,6, "Kernel Area Initialization Fail~!!");
		while(1);
	}
	kPrintString(1,5,"Pass");

	kPrintString(0,6, "[    ] IA-32e Page Tables Initialize.");
	kInitializePageTables();
	kPrintString(1,6,"Pass");
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

bool kIsMemoryEnough(void) {
	dword* pdwCurrentAddress;

	pdwCurrentAddress = (dword*) 0x100000;

	while((dword) pdwCurrentAddress < 0x4000000) {
		*pdwCurrentAddress = 0x12345678;
		if(*pdwCurrentAddress != 0x12345678) {
			return false;
		}

		pdwCurrentAddress += (0x100000 / 4);
	}
	return true;
}