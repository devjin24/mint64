#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "Types.h"

#pragma pack(push,1)

typedef struct kQueueManagerStruct {
  int iDataSize;
  int iMaxDataCount;

  void* pvQueueArray;
  int iPutIndex;
  int iGetIndex;

  bool bLastOperationPut;
} QUEUE;

#pragma pack(pop)

void kInitializeQueue(QUEUE* pstQueue, void* pvQueueBuffer, int iMaxDataCount, int iDataSize);
bool kIsQueueFull(const QUEUE* pstQueue);
bool kIsQueueEmpty(const QUEUE* pstQueue);
bool kPutQueue(QUEUE* pstQueue, const void* pvData);
bool kGetQueue(QUEUE* pstQueue, void* pvData);

#endif