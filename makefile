all:
	g++ -o vc_algo -std=c++11  -I/usr/include/NetworKit-2742bfba9724/include  -L/usr/include/NetworKit-2742bfba9724  vc_algo.cpp -lNetworKit -fopenmp
	g++ -o sampling_algo -std=c++11  -I/usr/include/NetworKit-2742bfba9724/include  -L/usr/include/NetworKit-2742bfba9724  sampling_algo.cpp -lNetworKit -fopenmp
