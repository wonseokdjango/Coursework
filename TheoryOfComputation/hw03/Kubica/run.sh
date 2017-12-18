#!/bin/bash
for ((t=40000; t<=40000; t=t+20000))
do
  for ((p=16; p<=16; p=p+4))
  do
    echo "./go ../Testcase/Infile-T$t-P$p.txt ../Testcase/Outfile-Kubica-T$t-P$p.txt > Elapsed_Kubica.txt" | bash
  done
done
