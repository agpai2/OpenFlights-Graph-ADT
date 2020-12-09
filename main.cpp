#include <iostream>
#include <vector>
#include <map>
#include<string>
#include<sstream>

#include "Graph.h"
#include "Airport.h"
#include "util/readFromFile.hpp"

int main(int argc, const char * argv[]) {

	// they map each column number in the data to all the data in that column
	std::map<int, std::vector<std::string>> airportMap = csv_reader(argv[1]);
	std::map<int, std::vector<std::string>> routeMap = csv_reader(argv[2]);

	Graph graph(airportMap, routeMap);

	std::vector<int> vec = graph.landmarkPath("GKA", "CNY", "KZN");

	std::vector<std::string> path;
	for (size_t i = 0; i < vec.size(); i++) {
		path.push_back(airportMap[4][vec[i]]);
	}

	graph.plotLandmarkPath(path);
	graph.plotAirports();

	// std::stringstream ss;
  // std::copy(path.begin(), path.end(),std::ostream_iterator<std::string>(ss, " "));

	// std::cout << ss.str() << std::endl;
}