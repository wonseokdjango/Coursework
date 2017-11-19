/**
  *@File    main.cpp
  *@Author  Wonseok Lee
  *@Brief   main for Kubica
  */

#include <cstdio>
#include <vector>
#include <algorithm>

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
  printf("ANSWER\n");

  s64_t i = 0;
  s64_t j = 0;
  s64_t pSize = p.size() - 1;
  s64_t tSize = t.size() - 1;

  while (i <= tSize - pSize)
  {
    while (true)
    {      
      if (j >= pSize)
        break;

      s64_t a = locationTable.LMax[j + 1];
      s64_t b = locationTable.LMin[j + 1];
      s64_t y_a = (a == 0)? std::numeric_limits<s64_t>::min() : t[i + a];
      s64_t y_b = (b == 0)? std::numeric_limits<s64_t>::max() : t[i + b];

      if ((y_a > t[i + j + 1]) || (t[i + j + 1] > y_b))
        break;

      ++j;
    }

    if (j == pSize)
      printf("%lld ", i + 1);

    i = i + (j - orderBordersTable.failure[j]);
    j = std::max<s64_t>(0, orderBordersTable.failure[j]);
  }
  printf("\n");
  
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
