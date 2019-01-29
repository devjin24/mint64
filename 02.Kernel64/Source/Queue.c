#include "Queue.h"

void kInitializeQueue(QUEUE* pstQueue, void* pvQueueBuffer, int iMaxDataCount, int iDataSize){
  pstQueue->iMaxDataCount = iMaxDataCount;
  pstQueue->iDataSize = iDataSize;
  pstQueue->pvQueueArray = pvQueueBuffer;

  pstQueue->iPutIndex = 0;
  pstQueue->iGetIndex = 0;
  pstQueue->bLastOperationPut = false;
}
bool kIsQueueFull(const QUEUE* pstQueue) {
  if((pstQueue->iGetIndex == pstQueue->iPutIndex) && 
  (pstQueue->bLastOperationPut==true)) {
    return true;
  }
  return false;
}
bool kIsQueueEmpty(const QUEUE* pstQueue) {
  if((pstQueue->iGetIndex == pstQueue->iPutIndex) &&
  (pstQueue->bLastOperationPut == false)) {
    return true;
  }
  return false;
}
bool kPutQueue(QUEUE* pstQueue, const void* pvData) {
  if(kIsQueueFull(pstQueue) == true) {
    return false;
  }

  kMemCpy((char*) pstQueue->pvQueueArray + (pstQueue->iDataSize * pstQueue->iPutIndex), pvData, pstQueue->iDataSize);

  pstQueue->iPutIndex = (pstQueue->iPutIndex +1) % pstQueue->iMaxDataCount;
  pstQueue->bLastOperationPut = true;
  return true;
}
bool kGetQueue(QUEUE* pstQueue, void* pvData) {
  if(kIsQueueEmpty(pstQueue) == true) {
    return false;
  }

  kMemCpy(pvData, (char*) pstQueue->pvQueueArray + (pstQueue->iDataSize * pstQueue->iGetIndex), pstQueue->iDataSize);

  pstQueue->iGetIndex = (pstQueue->iGetIndex +1) % pstQueue->iMaxDataCount;
  pstQueue->bLastOperationPut = false;
  return true;
}
