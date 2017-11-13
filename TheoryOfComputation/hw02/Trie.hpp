#ifndef _TRIE_HPP_
#define _TRIE_HPP_

#include <map>
#include <string>
#include <utility>

class Node
{
public:
  int code;
  Node* next[256];

  Node(void);
  ~Node(void);
};

class Trie
{
private:
  static const char* alphabet;
  int maxCode;
  std::map<int, std::string> codeMap;

public:
  Trie(void);
  ~Trie(void);

  Node root;
  std::pair<int, int> longestPrefixEncode(const char* _text); // 1byte consume
  std::string longestPrefixDecode(const unsigned short* _text); // 2byte consume
};

#endif
