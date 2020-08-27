#include "stdint.h"
#include "string.h"

void iterateCRC(bool CRC[8], int currentByte) {
  for (int y = 0; y < 8; ++y) {
    bool currentBit = (currentByte >> (7-y)) & 0x01;
    bool invert = currentBit ^ CRC[7];

    CRC[7] = CRC[6];
    CRC[6] = CRC[5];
    CRC[5] = CRC[4];
    CRC[4] = CRC[3];
    CRC[3] = CRC[2];
    CRC[2] = CRC[1] ^ invert;
    CRC[1] = CRC[0] ^ invert;
    CRC[0] = invert;
  }
}

int MakeCRC(int* arr, int len, int replyTo)
{
  bool CRC[8];
  bool addLength = true;
  
  for (int i = 0; i < 8; ++i) CRC[i] = 0;
  iterateCRC(CRC, 22);
  iterateCRC(CRC, replyTo);
  iterateCRC(CRC, 23);
  
  if (addLength)
    iterateCRC(CRC, len);

  for (int x = 0; x < len; ++x) {
    int currentByte = arr[x];
    iterateCRC(CRC, currentByte);
  }

  int final = 0;

  for (int x = 0; x < 8; ++x)
    final += (0x01 << x) * CRC[x];

  return final;
}

#include <stdio.h>

void splitNum(int num) {
  int lower = (num & 0xff00) >> 8;
  int upper = num & 0x00ff;

  printf("%d, %d\n", lower, upper);
}

int main()
   {
   int arr[] = {76, 71, 67, 0, 49, 49};
   // int Result = MakeCRC(arr, 6, 32);
   // printf("[%d] with P=[100000111]\n", Result);
   
   splitNum(12600);
   
   return(0);
   }

