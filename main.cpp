#include <iostream>
#include <vector>

#include "Graph.h"
#include "readFromFile.hpp"

int main(int argc, const char * argv[]) {
	
	Graph g;
	//std::cout << "Filename: " << argv[1] << std::endl;
	
	// convert file to string representation
	std::cout << "String Representation:" << std::endl;
	//std::cout << file_to_string(argv[1]) << std::endl;
	
	// convert file to vector representation
	std::cout << "Vector Representation:" << std::endl;
	std::vector<std::string> vectorRepr = file_to_vector(argv[1]);

	std::vector<std::string> vec = read_csv(argv[1]);
}