#include <iostream>
#include <vector>
#include <map>
#include<string>
#include<sstream>

#include "Graph.h"
#include "Airport.h"
#include "util/readFromFile.hpp"
#include "util/menu.hpp"

int main(int argc, const char * argv[]) {

	// they map each column number in the data to all the data in that column
	std::map<int, std::vector<std::string>> airportMap = csv_reader(argv[1]);
	std::map<int, std::vector<std::string>> routeMap = csv_reader(argv[2]);

	Graph graph(airportMap, routeMap);

	initMenu(graph, airportMap);
}