all:
	g++ -o vc_algo -std=c++11  vc_algo.cpp -lNetworKit -fopenmp
	g++ -o sampling_algo -std=c++11 sampling_algo.cpp -lNetworKit -fopenmp
