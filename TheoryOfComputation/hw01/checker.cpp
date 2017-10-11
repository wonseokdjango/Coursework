/**
*@File    checker.cpp
*@Author  Wonseok Lee
*@Brief   Checker program of hw1 is implemented at this file
*/

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

int main(int _argc, char* _argv[]) {

  if (_argc != 4) {
    printf("usage : ./checker BB_in_file BB_out_file ckeck_file\n");
    exit(-1);
  }

  FILE* fpBBIn = fopen(_argv[1], "r");
  if (fpBBIn == NULL) {
    printf("file open error\n");
    exit(-1);
  }

  FILE* fpBBOut = fopen(_argv[2], "r");
  if (fpBBOut == NULL) {
    printf("file open error\n");
    exit(-1);
  }

  FILE *fpCCOut = fopen(_argv[3], "w");
  if (fpCCOut == NULL) {
    printf("file open error\n");
    exit(-1);
  }
  
  // Read input
  unsigned int textSize;
  unsigned int patternSize;
  char text[100][101];
  char pattern[100][101];
 
  fscanf(fpBBIn, " %d %d", &patternSize, &textSize);  
  
  for (int pRow = 0; pRow < patternSize; ++pRow)
    fscanf(fpBBIn, " %s", pattern[pRow]);
  for (int tRow = 0; tRow < textSize; ++tRow)
    fscanf(fpBBIn, " %s", text[tRow]);

  // Baker Bird
  int r, c;
  vector<pair<int, int> > bb_answer;

  while (fscanf(fpBBOut, " %d %d", &r, &c) > 0)
    bb_answer.push_back(pair<int, int>(r, c));

  // Exhausitive search
  vector<pair<int, int> > naive_answer;

  for (int row = 0; row + patternSize <= textSize; ++row) {
    for (int col = 0; col + patternSize <= textSize; ++col) {
      bool matched = true;
      for (int pr = 0; pr < patternSize; ++pr) {
        for (int pc = 0; pc < patternSize; ++pc) {
          if (text[row + pr][col + pc] != pattern[pr][pc]) {
            matched = false;
            break;
          }
        }
        if (matched == false)
          break;
      }

      if (matched == true)
        naive_answer.push_back(pair<int, int>(row + patternSize - 1, col + patternSize - 1));
    }
  }

  if (bb_answer.size() != naive_answer.size())
    fprintf(fpCCOut, "no");
  else {
    bool correct = true;
    for (unsigned int idx = 0; idx < bb_answer.size(); ++idx) {
      if (bb_answer[idx].first != naive_answer[idx].first || bb_answer[idx].second != bb_answer[idx].second) {
        correct = false;
        break;
      }
    }
    fprintf(fpCCOut, correct ? "yes" : "no");
  }

  fclose(fpBBIn);
  fclose(fpBBOut);
  fclose(fpCCOut);

  return 0;
}
