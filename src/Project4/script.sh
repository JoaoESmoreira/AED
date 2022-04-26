#!/bin/bash

ARG1=10000000

COUNT=5000000

make

while [ $ARG1 -le 100000000 ]
do
    ./prog >> output.txt $ARG1
    ARG1=$(($ARG1 + $COUNT))
done

make clean