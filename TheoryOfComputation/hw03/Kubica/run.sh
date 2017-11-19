#!/bin/bash
for ((t=20000; t<=1000000; t=t+20000))
do
  for ((p=4; p<=64; p=p+4))
  do
    echo "./go ../Testcase/Infile-T$t-P$p.txt ../Testcase/Outfile-Kubica-T$t-P$p.txt >> Elapsed_Kubica.txt" | bash
  done
done
