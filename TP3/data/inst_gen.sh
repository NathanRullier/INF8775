#!/bin/bash

for n in "10" "50" "100" "500" "1000"; do
    python3 ./inst_gen.py -s $n $n
done