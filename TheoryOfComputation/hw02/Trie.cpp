#include <iostream>
#include <cstdio>

#include "Trie.hpp"

Node::Node(void)
{
  code = 0;
  for (int idx = 0; idx < 256; ++idx)
    next[idx] = 0;
}

Node::~Node(void)
{
  for (int idx = 0; idx < 256; ++idx)
  {
    if (next[idx])
      delete next[idx];
  }

  delete this;
}

const char* Trie::alphabet =
  "abcdefghijklmnopqrstuvwxyz"
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
  "0123456789"
  "?! ,.:;\n\r";

Trie::Trie(void)
{
  maxCode = 256; // max ASCII + 1
  for (int pos = 0; alphabet[pos] != '\0'; ++pos)
  {
    root.next[alphabet[pos]] = new Node();
    root.next[alphabet[pos]]->code = alphabet[pos];

    std::pair<int, std::string> dict;
    dict.first = alphabet[pos];
    dict.second = std::string(1, alphabet[pos]);

    codeMap.insert(dict);
  }
}

Trie::~Trie(void)
{
  // Do nothing
}

std::pair<int, int> Trie::longestPrefixEncode(const char* _text)
{
  int pos = 0;
  Node* current = &root;
  
  while (_text[pos] != EOF)
  {
    if (current->next[_text[pos]] == NULL)
    {
      if (maxCode < 65535)
      {
        current->next[_text[pos]] = new Node();
        current->next[_text[pos]]->code = maxCode++;
      }
      return std::pair<int, int>(pos, current->code);
    }
    else
      current = current->next[_text[pos++]];
  }

  return std::pair<int, int>(pos, current->code);
}

std::string Trie::longestPrefixDecode(const unsigned short* _text)
{
  int pos = 0;
  Node* current = &root;

  std::string prev = codeMap.find(_text[pos])->second;
  
  printf("WONSEOK> HERE1: %d\n", _text[0]);
  
  if (((short)_text[pos + 1]) == EOF)
    return prev;
  
  printf("WONSEOK> HERE2\n");

  std::string next = codeMap.find(_text[pos + 1])->second;

  std::string toAdd = prev + next.substr(0, 1);
  for (int idx = 0; idx < toAdd.size(); ++idx)
  {
    if (current->next[toAdd[idx]] == NULL)
    {
      if (maxCode < 65535)
      {
        current->next[toAdd[idx]] = new Node();
        current->next[toAdd[idx]]->code = maxCode++;

        std::pair<int, std::string> dict;
        dict.first = current->next[toAdd[idx]]->code;
        dict.second = toAdd;

        codeMap.insert(dict);
      }
    }
    else
      current = current->next[toAdd[idx]];
  }

  return prev;
}
