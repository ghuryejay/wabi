#!/bin/bash

# mix_graph = $1
#cutoff = $2
#epsilon = $3
#repeat_file = $4
#map file = $5

./vc_algo $1 $2 $3 $4

python evaluate1.py  $4 $3 $5
