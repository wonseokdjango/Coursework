#include <cstdio>
#include <iostream>

#include "LZW.hpp"
#include "Trie.hpp"

#define BUF_SIZE (256 * 1024 * 1024)

char g_char_buffer[BUF_SIZE];
unsigned short g_short_buffer[BUF_SIZE];

void LZWCompression(const char* origin, const char* encoded)
{
  // load on buffer
  FILE* fpOrigin = fopen(origin, "rb");
  
  int cnt = fread(g_char_buffer, sizeof(char), BUF_SIZE, fpOrigin);
  g_char_buffer[cnt] = EOF;

  fclose(fpOrigin);

  // encode
  FILE* fpEncoded = fopen(encoded, "wb");

  int pos = 0; 
  Trie* trie = new Trie();

  while (g_char_buffer[pos] != EOF)
  {
    std::pair<int, int> ret = trie->longestPrefixEncode(g_char_buffer + pos);
    
    short buf = 0;
    int upper = ((ret.second << 16) >> 24);
    int lower = ((ret.second << 24) >> 24);

    buf |= (((short)lower) << 0);
    buf |= (((short)upper) << 8);

    fwrite(&buf, sizeof(short), 1, fpEncoded);

    pos += ret.first;
  }

  fclose(fpEncoded);
}

void LZWDecompression(const char* encoded, const char* decoded)
{
  // load on buffer
  FILE* fpEncoded = fopen(encoded, "rb");
  
  int cnt = fread(g_short_buffer, sizeof(short), BUF_SIZE, fpEncoded);
  g_short_buffer[cnt] = EOF;

  fclose(fpEncoded);

  // decode
  FILE* fpDecoded = fopen(decoded, "wb");

  Trie* trie = new Trie();

  for (int pos = 0; (short)g_short_buffer[pos] != EOF; ++pos)
  {
    printf("WONSEOK> HERE0 : %d\n", g_short_buffer[pos]);
    std::string ret = trie->longestPrefixDecode(g_short_buffer + pos);
    for (int idx = 0; idx < ret.size(); ++idx)
      fwrite(&ret[idx], sizeof(char), 1, fpDecoded);
  }

  fclose(fpDecoded);
}
