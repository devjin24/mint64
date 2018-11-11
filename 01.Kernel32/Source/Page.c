#include "Page.h"

void kInitializePageTables(void) {
	PML4TEntry* pstPML4TEntry;
	PDPTEntry* pstPDPTEntry;
	PDEntry* pstPDEntry;
	dword dwMappingAddress;
	int i;

	pstPML4TEntry = (PML4TEntry*)0x100000;
	kSetPageEntryData( &(pstPML4TEntry[0]), 0x00, 0x101000, PAGE_FLAGS_DEFAULT, 0);
	for(i = 1; i < PAGE_MAXENTRYCOUNT; i++) {
		kSetPageEntryData(&(pstPML4TEntry[i]),0,0,0,0);
	}

	pstPDPTEntry = (PDPTEntry*) 0x101000;
	for(i=0 ;i < 64; i ++) {
		kSetPageEntryData(&(pstPDPTEntry[i]), 0,0x102000 + (i * PAGE_TABLESIZE), PAGE_FLAGS_DEFAULT,0 );
	}
	for(i = 64; i< PAGE_MAXENTRYCOUNT; i++) {
		kSetPageEntryData(&(pstPDPTEntry[i]),0,0,0,0);
	}

	pstPDEntry = (PDEntry*) 0x102000;
	dwMappingAddress = 0;
	for(i=0; i<PAGE_MAXENTRYCOUNT * 64; i++) {
		kSetPageEntryData(&(pstPDEntry[i]), (i * (PAGE_DEFAULTSIZE >> 20)) >> 12, dwMappingAddress, PAGE_FLAGS_DEFAULT | PAGE_FLAGS_PS, 0);
		dwMappingAddress += PAGE_DEFAULTSIZE;
	}
}

void kSetPageEntryData(PTEntry* pstEntry, dword dwUpperBaseAddress, dword dwLowerBaseAddress, dword dwLowerFlags, dword dwUpperFlags) {
	pstEntry-> dwAttributeAndLowerBaseAddress = dwLowerBaseAddress | dwLowerFlags;
	pstEntry ->dwUpperBaseAddressAndEXB = (dwUpperBaseAddress & 0xFF) | dwUpperFlags;
}