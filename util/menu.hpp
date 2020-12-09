#pragma once

#include <vector>
#include <map>
#include <string>

#include "../Graph.h"

/** 
 * Displays the elements of the adjacency matrix
 */
void displayAdjacencyMatrix();

/**
 * Finds the corresponding IATA codes of airport
 * from each of its ID and stores the path
 * 
 * @param vec - a vector that contains ID's of the airport
 * 
 * @return vector of IATA codes of aiports in the form of a path
 */
std::vector<std::string> printPath(std::vector<int> vec);

/** 
 * Displays the elements traversed during BFS
 */
void displayBFSTraversal();

/** 
 * Displays the elements in Dijkstra's path
 */
void displayDijkstraPath();

/** 
 * Displays the elements in Landmark path
 */
void displayLandmarkPath();

/** 
 * Displays a set a options a user can choose from
 */
void displayMenu();

/** 
 * Initializes the graph object
 * 
 * @param graph - an object built upon the graph ADT implemenation
 * @param airportMap - a map that maps IATA codes to corresponding airport objects
 */
void initMenu(Graph graph, std::map<int, std::vector<std::string>> airportMap);