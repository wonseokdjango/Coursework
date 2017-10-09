/**
*@File    hw1.cpp
*@Author  Wonseok Lee
*@Brief   Baker-Bird 2d pattern matching algorithm is implemented at this file
*/

#include <cstdio>
#include <cstdlib>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <queue>

using namespace std;

/**
*@Class State
*@Brief State class for Aho-Corasick pattern automaton
*/
class State {
public:
  State* go[26];
  State* failure;
  set<unsigned int> output;

  State();
  ~State();
  void insert(const int _id, const char* _pattern);
  static void connectFailure(State* _root);
};

void BakerBird(const State* _root, const unsigned int _textSize, const char (*_text)[101]);

int main(int _argc, char* _argv[]) {

  // Usage check
  if (_argc != 3) {
    printf("usage : ./hw1 in_file out_file\n");
    exit(-1);
  }

  // Read input
  unsigned int textSize;
  unsigned int patternSize;
  char text[100][101];
  char pattern[100][101];
  
  FILE *fpIn = fopen(_argv[1], "r");
  if (fpIn == NULL) {
    printf("file open failed\n");
    exit(-1);
  }

  fscanf(fpIn, " %d %d", &patternSize, &textSize);  
  
  for (int pRow = 0; pRow < patternSize; ++pRow)
    fscanf(fpIn, " %s", pattern[pRow]);
  for (int tRow = 0; tRow < textSize; ++tRow)
    fscanf(fpIn, " %s", text[tRow]);
  
  fclose(fpIn);

  // Get distinct patterns
  unsigned int id = 1;
  map<string, unsigned int> distincts; ///< Distinct patterns
  
  for (int pRow = 0; pRow < patternSize; ++pRow) {
    if (distincts.insert(pair<string, unsigned int>(pattern[pRow], id)).second)
      ++id;
  }

  // Build automaton of distinct patterns
  State* root = new State(); ///< Root of automaton

  map<string, unsigned int>::iterator mapIt;
  for (mapIt = distincts.begin(); mapIt != distincts.end(); ++mapIt)
    root->insert(mapIt->second, mapIt->first.c_str());

  State::connectFailure(root);

  // Execute BakerBird algorithm
  BakerBird(root, textSize, text);

  // free resources.
  delete root;

  return 0;
}

/**
*@Brief Default constructor 
*/
State::State() {
  for (int it = 0; it < 26; ++it)
    go[it] = NULL;

  failure = NULL;
}

/**
*@Brief Default destructor
*/
State::~State() {
  for (int ch = 0; ch < 26; ++ch) {
    if (go[ch] != NULL)
      delete go[ch];
  }
}

/**
*@Brief     Build up automaton which includes _pattern
*@Param[in] _id       Unique identifier of pattern _pattern
*@Param[in] _pattern  Pattern string to be added to automaton
*/
void State::insert(const int _id, const char* _pattern) {
  // Set output
  if (_pattern[0] == '\0') {
    output.insert(_id);
    return;
  }

  // Scan further
  unsigned int edge = _pattern[0] - 'a';
  if (go[edge] == NULL)
    go[edge] = new State();
  go[edge]->insert(_id, _pattern + 1);
}

/**
*@Brief     Connect failure link of automaton
*@Param[in] _root Root of automaton
*/
void State::connectFailure(State *_root) {
  _root->failure = _root;
  
  queue<State*> q;
  q.push(_root);
  
  while (q.empty() == false) {
    State* parent = q.front();
    q.pop();

    for (int edge = 0; edge < 26; ++edge) {
      State* child = parent->go[edge];
      if (child == NULL)
        continue;

      if (parent == _root)
        child->failure = _root;
      else {
        State* link = parent->failure;
        while (link != _root && link->go[edge] == NULL)
          link = link->failure;

        child->failure = (link->go[edge] == NULL) ? _root : link->go[edge];
      }

      if (child->failure->output.empty() != false) {
        set<unsigned int>::iterator it;
        for (it = child->failure->output.begin(); it != child->failure->output.end(); ++it)
          child->output.insert(*it);
      }

      q.push(child);
    }
  }
}

/**
*@Brief Baker Bird 2d pattern matching algorithm
*@Param[in] _root     Root of automaton
*@Param[in] _textSize Size of text
*@Param[in] _text     Text
*/
void BakerBird(const State* _root, const unsigned int _textSize, const char (*_text)[101]) {

  for (int tRow = 0; tRow < _textSize; ++tRow) {
    const State *current = _root;
    vector<unsigned int> row(_textSize, 0);

    for (int tCol = 0; tCol < _textSize; ++tCol) {
      int edge = _text[tRow][tCol] - 'a';

      while (current != _root && current->go[edge] == NULL)
        current = current->failure;

      if (current->go[edge] != NULL)
        current = current->go[edge];

      if (current->output.empty() == false)
        row[tCol] = *(current->output.begin());
    }

    // TODO
  }
}
