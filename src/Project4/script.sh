#!/bin/bash

ARG1=5000

COUNT=5000

make

while [ $ARG1 -le 100000 ]
do
    ./prog $ARG1 >> output.txt 
    ARG1=$(($ARG1 + $COUNT))
done

make clean