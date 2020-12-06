#include <iostream>
#include <vector>
#include <map>

#include "Graph.h"
#include "readFromFile.hpp"

int main(int argc, const char * argv[]) {
	std::map<int, std::vector<std::string>> airportMap = csv_reader(argv[1]);
	std::map<int, std::vector<std::string>> routeMap = csv_reader(argv[2]);
	Graph graph(airportMap, routeMap);
	//graph.displayMatrix(30);
	//graph.BFS(0);
	std::vector<int> vec = graph.landmarkPath("GKA", "CNY", "KZN");

	for (int i = 0; i < vec.size(); i++) {
		std::cout << airportMap[4][vec[i]] << ", ";
	}
}