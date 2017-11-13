/**
  *@File    Dict.cpp
  *@Author  Wonseok Lee
  *@Brief   Source for dictionary class using trie for LZW compression/decompression
  */

#include <cstdio>
#include <iostream>

#include "Dict.hpp"

#define MAX_CODE_VAL 65535

Trie::Trie(void)
{
  code = 0;
  for (u32t idx = 0; idx <= 255; ++idx)
    next[idx] = 0;
}

Trie::~Trie(void)
{
  for (u32t idx = 0; idx <= 255; ++idx)
  {
    if (next[idx])
      delete next[idx];
  }
}

Dict::Dict(void)
{
  maxCode = 256; // LZW code starts from Max(ASCII) + 1

  root = new Trie();

  for (u32t ch = 0; ch <= 255; ++ch)
  {
    root->next[ch] = new Trie();
    root->next[ch]->code = ch;
    
    codeMap.insert(std::pair<u16t, std::string>(ch, std::string(1, ch)));
  }
}

Dict::~Dict(void)
{
  delete root;
}

std::pair<u32t, u16t> Dict::encode(const s08t* _text)
{
  u32t pos = 0;
  Trie* current = root;
  
  while (_text[pos] != EOF)
  {
    if (current->next[_text[pos]] == NULL)
    {
      if (maxCode < MAX_CODE_VAL - 1)
      {
        current->next[_text[pos]] = new Trie();
        current->next[_text[pos]]->code = maxCode++;
      }
      return std::pair<u32t, u16t>(pos, current->code);
    }
    else
      current = current->next[_text[pos++]];
  }

  return std::pair<u32t, u16t>(pos, current->code);
}

std::string Dict::decode(const u16t* _text)
{
  Trie* current = root;

  std::string prev = codeMap.find(_text[0])->second;

  if (((s16t)_text[1]) == EOF)
    return prev;

  std::string next = codeMap.find(_text[1])->second;

  std::string toAdd = prev + next.substr(0, 1);
  for (u32t idx = 0; idx < toAdd.size(); ++idx)
  {
    if (current->next[toAdd[idx]] == NULL)
    {
      if (maxCode < MAX_CODE_VAL - 1)
      {
        current->next[toAdd[idx]] = new Trie();
        current->next[toAdd[idx]]->code = maxCode++;

        codeMap.insert(std::pair<u16t, std::string>(maxCode - 1, toAdd));
      }
    }
    else
      current = current->next[toAdd[idx]];
  }

  return prev;
}
