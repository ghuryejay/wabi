#!/bin/bash

# mix_graph = $1
#cutoff = $2
#repeat_file = $3
#fasta_file = $4

make

./vc_algo $1 $2 $3

python evaluate.py $4 $3
