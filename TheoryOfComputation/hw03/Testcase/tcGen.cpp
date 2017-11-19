/**
  *@File    main.cpp
  *@Author  Wonseok Lee
  *@Brief   main for testcase generator
  */

#include <cstdio>
#include <cstdlib>

int main(void)
{
  int pSize;
  int tSize;

  for (tSize = 20000; tSize <= 1000000; tSize += 20000)
  {
    for (pSize = 4; pSize <= 64; pSize += 4)
    {
      char buf[1024];
      sprintf(buf, "Infile-T%d-P%d.txt", tSize, pSize);
      FILE* fp = fopen(buf, "w");

      fprintf(fp, "%d\n", pSize);
      fprintf(fp, "%d\n", tSize);
      for (int i = 0; i < pSize; ++i)
        fprintf(fp, "%d ", rand());
      fprintf(fp, "\n");
      for (int i = 0; i < tSize; ++i)
        fprintf(fp, "%d ", rand());
      fprintf(fp, "\n");

      fclose(fp);
    }
  }

  return 0;
}
