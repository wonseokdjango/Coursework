#!/bin/bash

for ((t=20000; t<=1000000; t=t+20000))
do
  for ((p=4; p<=64; p=p+4))
  do
    diff ./Testcase/Outfile-Kubica-T$t-P$p.txt ./Testcase/Outfile-Baseline-T$t-P$p.txt
  done
done
