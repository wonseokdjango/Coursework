/**
  *@File    main.cpp
  *@Author  Wonseok Lee
  *@Brief   main for baseline
  */

#include <cstdio>
#include <vector>
#include <algorithm>

#include <time.h>

typedef long long s64_t;

int main(int argc, char* argv[])
{
  clock_t s, e;

  s64_t pSize;
  s64_t tSize;
  std::vector<std::pair<s64_t, s64_t> > p;
  std::vector<s64_t> t;

  // read input
  FILE* fp = fopen(argv[1], "r");
  if (fp == NULL)
  {
    printf("file open failed\n");
    return 0;
  }
  
  fscanf(fp, " %lld %lld", &pSize, &tSize);
  p.assign(pSize, std::pair<s64_t, s64_t>(0, 0));
  t.assign(tSize, 0);

  for (int pos = 0; pos < pSize; ++pos)
  {
    fscanf(fp, " %lld", &p[pos].first);
    p[pos].second = pos;
  }
  for (int pos = 0; pos < tSize; ++pos)
    fscanf(fp, " %lld", &t[pos]);

  fclose(fp);

  // naive
  fp = fopen(argv[2], "w");

  s = clock();

  fprintf(fp, "ANSWER %lld %lld ", tSize, pSize);
  std::vector<std::pair<s64_t, s64_t> > buf(pSize, std::pair<s64_t, s64_t>(0, 0));
  sort(p.begin(), p.end());

  for (s64_t s = 0; s <= tSize - pSize; ++s)
  {
    for (s64_t copy = 0; copy < pSize; ++copy)
    {
      buf[copy].first = t[s + copy];
      buf[copy].second = copy;
    }

    sort(buf.begin(), buf.end());

    s64_t matched;
    for (matched = 0; buf[matched].second == p[matched].second; ++matched);
    if (matched == pSize)
      fprintf(fp, "%lld ", s + 1);
  }
  fprintf(fp, "\n");

  e = clock();
  double elapsed = ((double)(e - s) * 1000) / CLOCKS_PER_SEC;
  
  printf("Elapsed %lld %lld : %.8lf (msec)\n", (s64_t)pSize, (s64_t)tSize, elapsed);

  fclose(fp);

  return 0;
}
