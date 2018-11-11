#ifndef __TYPE_H__
#define __TYPE_H__

#define byte unsigned char
#define word unsigned short
#define dword unsigned int
#define qword unsigned long
#define bool unsigned char

#define true 1
#define false 0
#define null 0

#pragma pack(push ,1)

typedef struct kCharactorStruct {
  byte bCharactor;
  byte bAttribute;
} Character;

#pragma pack (pop)
#endif