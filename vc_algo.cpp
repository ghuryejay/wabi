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
	clock_t start = clock();
	GMLGraphReader reader;
	Graph g = reader.read(argv[1]);
	ifstream ifile;
	ifile.open(argv[1]);
	string str;
	map<string,string> labelmap;
	string id;
	string label;
	int cnt = 1;
	while (std::getline(ifile, str)) {
		if(cnt %4 == 0){
			id = str.substr(7);
		}
		if((cnt-1)%4 == 0 && cnt != 1) {
			label = str.substr(10);
			labelmap[id] = label;
		}
		cnt += 1;
	}

	cout << "Nodes: " << g.nodes().size() << endl;
	cout << "Edges: " << g.edges().size() << endl;
	double delta = 0.1;
	double epsilon = 0.1;
	//Betweenness centrality(g);
	ApproxBetweenness centrality(g, delta, epsilon, 2);
	//ApproxBetweenness2 centrality(g,100,false);
	centrality.run();
	ofstream myfile;
	filepath = filepath.substr(0,filepath.length()-4);
	myfile.open(filepath+".repeats");
	vector<pair<node, double>> nodeRanks(g.nodes().size());
	nodeRanks = centrality.ranking();
	vector<double> scores = centrality.scores();
	vector<double> bc_nonzero;
	bc_nonzero = scores;
//	for(int i = 0;i < scores.size();i++){
//		if(scores.at(i) != 0){
//			bc_nonzero.push_back(scores.at(i));
//		}
//	}
	cout<<bc_nonzero.size()<<endl;
	double sum = std::accumulate(bc_nonzero.begin(), bc_nonzero.end(), 0.0);
	double mean = sum / bc_nonzero.size();

	double sq_sum = std::inner_product(bc_nonzero.begin(), bc_nonzero.end(), bc_nonzero.begin(), 0.0);
	double stdev = std::sqrt(sq_sum / bc_nonzero.size() - mean * mean);
	cout<<"Mean: "<<mean<<endl;
	cout<<"Std Dev: "<<stdev<<endl;
	cout<<"bound: "<<mean + filterparam*stdev<<endl;
	double bound = mean + filterparam*stdev;
	for (int i = 0; i < g.nodes().size(); i++) {
		if(nodeRanks.at(i).second >= bound){
			string String = static_cast<ostringstream*>( &(ostringstream() << nodeRanks.at(i).first) )->str();
			myfile << nodeRanks.at(i).first <<"\t"<< nodeRanks.at(i).second<<"\t"<<labelmap[String]<< endl;
		}
	}
	cout << "Execution Time = " << (double) (clock() - start) / CLOCKS_PER_SEC
			<< endl;
	return 0;
}

