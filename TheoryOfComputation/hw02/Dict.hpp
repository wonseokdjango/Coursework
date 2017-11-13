/**
  *@File    Dict.hpp
  *@Author  Wonseok Lee
  *@Brief   Header for dictionary class using trie for LZW compression/decompression
  */

#ifndef _DICT_HPP_
#define _DICT_HPP_

#include <map>
#include <string>
#include <utility>

#include "Types.hpp"

class Trie
{
public:
  u16t code;
  Trie* next[256];

  Trie(void);
  ~Trie(void);
};

class Dict
{
private:
  u16t maxCode;
  std::map<u16t, std::string> codeMap;

public:
  Dict(void);
  ~Dict(void);

  Trie* root;
  std::pair<u32t, u16t> encode(const s08t* _text);
  std::string decode(const u16t* _text);
};

#endif
