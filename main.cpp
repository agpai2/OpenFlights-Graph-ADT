#include <iostream>
#include <vector>

#include "Graph.h"
#include "readFromFile.hpp"

int main(int argc, const char * argv[]) {
	//std::cout << "Filename: " << argv[1] << std::endl;
	
	// convert file to string representation
	std::cout << "String Representation:" << std::endl;
	//std::cout << file_to_string(argv[1]) << std::endl;
	
	// convert file to vector representation
	std::cout << "Vector Representation:" << std::endl;
	std::vector<std::string> vectorRepr = file_to_vector(argv[1]);

	std::vector<std::string> airportVec = read_csv(argv[1]);
	std::vector<std::string> routeVec = read_csv(argv[2]);

	std::cout << airportVec[0] << std::endl;
	std::cout << routeVec[0] << std::endl;

	// for (int i = 0; i < 200; i++) {
	//  	std::cout << routeVec[i] <<std::endl;
	// }

	Graph g(airportVec, routeVec);
	g.displayMatrix(15000);
}