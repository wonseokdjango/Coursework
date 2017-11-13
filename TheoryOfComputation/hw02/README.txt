Theory Of Computation HW 2
Lempel-Ziv-Welch Compression

2017-21586 Wonseok Lee

- Environment
  OS       : Ubuntu 14.04.5 LTS
  Language : C++
  Compiler : g++ 4.8.4

- Quick start
  You can enter './hw2 input_path encode_path decode_path [-e]'

  This shell compiles whole sources and executes LZW compression

    input_path  : input file path you want to compress and decompress
    encode_path : encoded file path you want to write encoding of input file
    decode_path : decoded file path you want to write decoding of encoded file

  If you input option '-e' then input and decoded file are displayed on display
  (40 character per line)

  This shell reports belows:
    a. Execution time for encoding and decoding
    b. File size of encoded file
    c. diff between input and decoded file 

- How to Compile
  I made makefile for compiling. Just type 'make'

- How to Run
  './hw2 input_path encode_path decode_path [-e]'
