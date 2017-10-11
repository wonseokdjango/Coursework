#!/bin/bash

make

for tc in $(seq -f "%g" 0 9)
do
  ./hw1 bb_input/bb_in${tc}.txt bb_output/bb_out${tc}.txt
  ./checker bb_input/bb_in${tc}.txt bb_output/bb_out${tc}.txt cc_output/cc_out${tc}.txt  
done

make clean
