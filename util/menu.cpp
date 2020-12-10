#include <iostream>
#include <vector>
#include <map>
#include<string>
#include<sstream>

#include "../Graph.h"

Graph graph_;
std::map<int, std::vector<std::string>> airportMap_;

void displayAdjacencyMatrix() {
  std::cout << "Enter the matrix dimension to be printed (-1 for full matrix) ";
  int dim;
  std::cin >> dim;

  graph_.displayMatrix(dim);
}

std::vector<std::string> printPath(std::vector<int> vec) {
  std::vector<std::string> path;
	for (size_t i = 0; i < vec.size(); i++) {
		path.push_back(airportMap_[4][vec[i]]);
	}

  std::stringstream ss;
  std::copy(path.begin(), path.end(),std::ostream_iterator<std::string>(ss, " "));

  std::cout << std::endl;
	std::cout << ss.str() << std::endl;

  return path;
}

void displayBFSTraversal() {
  std::cout << "Enter the IATA code of the airport to start traversal ";
  std::string iata;
  std::cin >> iata;
  graph_.BFS(iata);
}

void displayDijkstraPath() {
  std::string start, end;
  std::cout << "Enter the IATA of the start airport for Dijkstra path" << std::endl;
  std::cin >> start;
  std::cout << "Enter the IATA of the end airport for Dijkstra path" << std::endl;
  std::cin >> end;

  printPath(graph_.dijkstra(start, end));
}

void displayLandmarkPath() {
  std::string start, mid, end;
  std::cout << "Enter the IATA of the start airport for Landmark path" << std::endl;
  std::cin >> start;
  std::cout << "Enter the IATA of the mid airport for Landmark path" << std::endl;
  std::cin >> mid;
  std::cout << "Enter the IATA of the end airport for Landmark path" << std::endl;
  std::cin >> end;

  std::vector<std::string> path = printPath(graph_.landmarkPath(start, mid, end));
  graph_.plotLandmarkPath(path);
}

void displayMenu() {
  while (1) {
		std::cout << std::endl;
		std::cout << "Airport Visualization System" << std::endl << std::endl;

		std::cout << "1) Display Adjacency martix" << std::endl;
		std::cout << "2) Display BFS Traversal" << std::endl;
		std::cout << "3) Display Dijkstra's path" << std::endl;
		std::cout << "4) Display and plot Landmark path" << std::endl;
		std::cout << "5) Plot airports on map" << std::endl;
		std::cout << "6) Exit" << std::endl << std::endl;

		std::cout << "Enter your choice" << std::endl;
		int option;
    char* str;
		std::cin >> str;
    option = atof(str);

		switch(option) {
      case 0: {
        std::cout << "\n";
				std::cout << "Invalid Option. Please enter valid option number" << std::endl;
        break;
      }
			case 1: {
        displayAdjacencyMatrix();
        break;
      }
			case 2: {
				displayBFSTraversal();
				break;
			}

			case 3: {
        displayDijkstraPath();
        break;
      }

			case 4: { 
				displayLandmarkPath();
				break; 
			}
			case 5: { 
				graph_.plotAirports();
				break; 
			}
			case 6: {
				exit(0);
      }

			default: { 
				exit(0);
			}
		}
	}
}

void initMenu(Graph graph, std::map<int, std::vector<std::string>> airportMap) {
  graph_ = graph;
  airportMap_ = airportMap;

  displayMenu();
}