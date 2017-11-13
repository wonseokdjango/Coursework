#include <cstdio>
#include <time.h>

#include "LZW.hpp"

int main(int argc, char* argv[])
{
  clock_t s, e;
  double elapsedComp;
  double elapsedDecomp;

  s = clock();
  LZWCompression(argv[1], argv[2]);
  e = clock();
  elapsedComp = ((double)(e - s) / CLOCKS_PER_SEC);
  
  s = clock();
  LZWDecompression(argv[2], argv[3]);
  e = clock();
  elapsedDecomp = ((double)(e - s) / CLOCKS_PER_SEC);

  printf("Elapsed time for encoding : %.7lf (usec)\n", elapsedComp);
  printf("Elapsed time for decoding : %.7lf (usec)\n", elapsedDecomp);
  
  return 0;
}
