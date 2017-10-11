#include <cstdio>
#include <cstdlib>
#include <string>
#include <time.h>
#include <algorithm>

using namespace std;

int main(void) {

  srand(time(NULL));
  
  int numOfInput = 10;
  for (int tc = 0; tc < numOfInput; ++tc) {
    string fname = string("bb_in") + to_string(tc) + string(".txt");
    
    FILE *fp = fopen(fname.c_str(), "w");

    int tSize = rand() % 100 + 1;
    int pSize = rand() % 5 + 1;

    fprintf(fp, "%d %d\n", pSize, tSize);
    for (int row = 0; row < pSize; ++row) {
      for (int col = 0; col < pSize; ++col) {
        fprintf(fp, "%c", 'a' + rand() % 3);
      }
      fprintf(fp, "\n");
    }
    for (int row = 0; row < tSize; ++row) {
      for (int col = 0; col < tSize; ++col) {
        fprintf(fp, "%c", 'a' + rand() % 3);
      }
      fprintf(fp, "\n");
    }

    fclose(fp);
  }

  return 0;
}
