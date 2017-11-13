/**
  *@File    main.cpp
  *@Author  Wonseok Lee
  *@Brief   Main for for LZW compression/decompression
  */

#include <cstdio>
#include <time.h>

#include "LZW.hpp"

int main(int argc, char* argv[])
{
  clock_t s, e;
  double elapsedComp;
  double elapsedDecomp;

  s = clock();
  LZW::LZWEnc(argv[1], argv[2]);
  e = clock();
  elapsedComp = ((double)(e - s) / CLOCKS_PER_SEC);
  
  s = clock();
  LZW::LZWDec(argv[2], argv[3]);
  e = clock();
  elapsedDecomp = ((double)(e - s) / CLOCKS_PER_SEC);

  printf("Elapsed time for encoding : %.8lf (sec)\n", elapsedComp);
  printf("Elapsed time for decoding : %.8lf (sec)\n", elapsedDecomp);
  
  return 0;
}
