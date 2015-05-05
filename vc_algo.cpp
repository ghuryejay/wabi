//============================================================================
// Name        : Assembly_Genome.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <string>
#include <numeric>
#include <map>
#include <algorithm>

#include <NetworKit/graph/Graph.h>
#include <NetworKit/io/GMLGraphReader.h>
#include <NetworKit/centrality/ApproxBetweenness.h>
#include <NetworKit/centrality/Betweenness.h>
#include <NetworKit/centrality/ApproxBetweenness2.h>

using namespace std;
using namespace NetworKit;

int main(int argc, char* argv[]) {

	string filepath;
	cout<<argv[1]<<endl;
	int filterparam;
	filepath = argv[1];
	filterparam = atoi(argv[2]);
	string repeat_file = argv[3];
	clock_t start = clock();
	GMLGraphReader reader;
	Graph g = reader.read(argv[1]);
	ifstream ifile;
	ifile.open(argv[1]);
	string str;
	map<string,string> labelmap;
	string id;
	string label;
	while (std::getline(ifile, str)) {
		if(str.find("id") != string::npos){
			id = str.substr(7);
		}
		if(str.find("label") != string::npos) {
			label = str.substr(10);
			label.erase(0,1);
			label.erase(label.length()-1);
			labelmap[id] = label;
		}
	}

	cerr << "Nodes: " << g.nodes().size() << endl;
	cerr << "Edges: " << g.edges().size() << endl;
	double delta = 0.1;
	double epsilon = 0.1;
	ApproxBetweenness centrality(g, delta, epsilon, 2);
	centrality.run();
	ofstream myfile;
	filepath = filepath.substr(0,filepath.length()-4);
	myfile.open(repeat_file);
	vector<pair<node, double>> nodeRanks(g.nodes().size());
	nodeRanks = centrality.ranking();
	vector<double> scores = centrality.scores();
	vector<double> scores1 = scores;
	sort(scores1.begin(),scores1.end());
	double sum = std::accumulate(scores.begin(), scores.end(), 0.0);
	double mean = sum / scores.size();
	int first_quartile = scores1.size()/4;
	int median = scores1.size()/2;
	int third_quartile = first_quartile + median;
	double range = scores1.at(third_quartile) - scores1.at(first_quartile);
	double filter = scores1.at(third_quartile) + 1.5*range;

	double sq_sum = std::inner_product(scores.begin(), scores.end(), scores.begin(), 0.0);
	double stdev = std::sqrt(sq_sum / scores.size() - mean * mean);
	cerr<<"Mean: "<<mean<<endl;
	cerr<<"Std Dev: "<<stdev<<endl;
	cerr<<"bound: "<<mean + filterparam*stdev<<endl;
	cerr<<"filter: "<<filter<<endl;
	double bound = mean + filterparam*stdev;
	for (int i = 0; i < g.nodes().size(); i++) {
		int isrepeat = 0;
		if(nodeRanks.at(i).second >= bound){
			isrepeat = 1;
		}
		string String = static_cast<ostringstream*>( &(ostringstream() << nodeRanks.at(i).first) )->str();
//		myfile << nodeRanks.at(i).first <<"\t"<< nodeRanks.at(i).second<<"\t"<<labelmap[String]<< endl;
	myfile << nodeRanks.at(i).first <<"\t"<< nodeRanks.at(i).second<<"\t"<<labelmap[String]<<"\t"<<isrepeat<< endl;
	}
	cerr << "Execution Time = " << (double) (clock() - start) / CLOCKS_PER_SEC
			<< endl;
	return 0;
}

