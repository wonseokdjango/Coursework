/**
  *@File    LZW.cpp
  *@Author  Wonseok Lee
  *@Brief   Source for LZW class
  */

#include <cstdio>
#include <iostream>

#include "LZW.hpp"
#include "Dict.hpp"

#define BUF_SIZE (256 * 1024 * 1024)

s08t LZW::buffer08[BUF_SIZE];
u16t LZW::buffer16[BUF_SIZE];

void LZW::LZWEnc(const char* fnameOrg, const char* fnameEnc)
{
  // load origin on the buffer
  FILE* fpOrg = fopen(fnameOrg, "rb");
  s32t cnt = fread(buffer08, sizeof(s08t), BUF_SIZE, fpOrg);
  buffer08[cnt] = EOF;
  fclose(fpOrg);

  // encode buffer and write it to file
  FILE* fpEnc = fopen(fnameEnc, "wb");

  u32t pos = 0;
  Dict* dict = new Dict();

  while (buffer08[pos] != EOF)
  {
    std::pair<u32t, u16t> ret = dict->encode(buffer08 + pos);

    fwrite(&ret.second, sizeof(u16t), 1, fpEnc);
    pos += ret.first;
  }

  delete dict;

  fclose(fpEnc);
}

void LZW::LZWDec(const char* fnameEnc, const char* fnameDec)
{
  // load encoded file on the buffer
  FILE* fpEnc = fopen(fnameEnc, "rb");
  s32t cnt = fread(buffer16, sizeof(u16t), BUF_SIZE, fpEnc);
  buffer16[cnt] = EOF;
  fclose(fpEnc);
 
  // decode buffer and write it to file
  FILE* fpDec = fopen(fnameDec, "w");

  Dict* dict = new Dict();

  for (u32t pos = 0; ((short)buffer16[pos]) != EOF; ++pos)
  {
    std::string ret = dict->decode(buffer16 + pos);  
    fprintf(fpDec, "%s", ret.c_str());
  }

  delete dict;

  fclose(fpDec);
}
