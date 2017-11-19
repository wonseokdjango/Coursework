/**
  *@File    main.cpp
  *@Author  Wonseok Lee
  *@Brief   main
  */

#include <cstdio>
#include <vector>

#include "common.hpp"

static void readInput(char* _fname, std::vector<pat_t>& _p, std::vector<s64_t>& _t);

int main(int argc, char* argv[])
{
  std::vector<pat_t> p;
  std::vector<s64_t> t;

  readInput(argv[1], p, t);
  
  LocationTable locationTable(p);
  OrderBordersTable orderBordersTable(p, locationTable);

  // KMP-ways.



  return 0;
}

void readInput(char* _fname, std::vector<pat_t>& _p, std::vector<s64_t>& _t)
{
  // read input.
  FILE* fpIn = fopen(_fname, "r");

  s64_t pLen;
  s64_t tLen;

  fscanf(fpIn, " %lld %lld", &pLen, &tLen);

  _p.assign(pLen + 1, pat_t());
  _t.assign(tLen + 1, 0);

  for (s64_t pos = 1; pos <= pLen; ++pos)
  {
    fscanf(fpIn, " %lld", &_p[pos].val);
    _p[pos].pos = pos;
  }

  for (s64_t pos = 1; pos <= tLen; ++pos)
    fscanf(fpIn, " %lld", &_t[pos]);

  fclose(fpIn);
}
