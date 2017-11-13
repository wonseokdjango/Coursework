/**
  *@File    LZW.hpp
  *@Author  Wonseok Lee
  *@Brief   Header for LZW class
  */

#ifndef _LZW_HPP_
#define _LZW_HPP_

#include "Types.hpp"

#define BUF_SIZE (256 * 1024 * 1024)

class LZW
{
public:

  static s08t buffer08[BUF_SIZE];
  static u16t buffer16[BUF_SIZE];

  static void LZWEnc(const char* fnameOrg, const char* fnameEnc);
  static void LZWDec(const char* fnameEnc, const char* fnameDec);
};

#endif
