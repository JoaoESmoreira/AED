#!/bin/bash

ARG1=50000

COUNT=50000

make

while [ $ARG1 -le 1000000 ]; do
    ./prog $ARG1 >> output.txt 
    ARG1=$(($ARG1 + $COUNT))
done

make clean

