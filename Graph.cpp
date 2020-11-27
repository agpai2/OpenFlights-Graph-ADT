#include "Graph.h"
#include <cmath>
#include <map>
#include <iostream>
#include <vector>
#include <queue>

Graph::Graph() {
   adjMatrix.resize(100, std::vector<double>(100, 0));
}

Graph::Graph(std::map<int, std::vector<std::string>> airportMap, std::map<int, std::vector<std::string>> routeMap) {

    adjMatrix.resize(airportMap[0].size(), std::vector<double>(airportMap[0].size(), 0));

    std::map<std::string, Airport> airportCodeMap;
    for (int i = 0; i < airportMap[0].size(); i++) {
        
        Airport airportTemp(i + 1, airportMap[1][i], airportMap[2][i],
                                airportMap[4][i], airportMap[5][i], std::stod(airportMap[6][i]), std::stod(airportMap[7][i]));
        
        airportCodeMap[airportMap[4][i]] = airportTemp;
    }
    
    for (int i = 0; i < routeMap[0].size(); i++) {
        if (airportCodeMap.count(routeMap[2][i]) != 0 && airportCodeMap.count(routeMap[4][i]))
            addEdge(airportCodeMap[routeMap[2][i]], airportCodeMap[routeMap[4][i]]);
    }

}

void Graph::addEdge(Airport source, Airport destination) {
    double euclideanDist = euclideanDistance(source, destination);
    adjMatrix[source.getId() - 1][destination.getId() - 1] = euclideanDist;
}


bool Graph::areAdjacent(Airport source, Airport destination) {
    return adjMatrix[source.getId() - 1][destination.getId() - 1] != 0.0;
}

void Graph::displayMatrix(int v) {
   int i, j;
   for(i = 0; i < v; i++) {
      for(j = 0; j < v; j++) {
        std::cout << adjMatrix[i][j] << " ";
      }
      std::cout << std::endl;
   }
}

double Graph::euclideanDistance(Airport source, Airport destination) {
    // logic taken from https://www.geeksforgeeks.org/program-distance-two-points-earth/
    long double one_deg = (M_PI) / 180;

    double source_lat = one_deg * source.getLatitude();
    double source_long = one_deg * source.getLongitude();
    double dest_lat = one_deg * destination.getLatitude();
    double dest_long = one_deg * destination.getLongitude();

    // Haversine Formula
    long double dlong = dest_long - source_long;
    long double dlat = dest_lat - source_lat;

    long double distance = pow(sin(dlat / 2), 2) + 
        cos(source_lat) * cos(dest_lat) * pow(sin(dlong / 2), 2);

    distance = 2 * asin(sqrt(distance));

    // Radius of Earth = 6371 Kilometers or 3956 Miles
    long double R = 6371;
    distance = distance * R;

    return distance;
}

void Graph::BFS(int start) {

    // Initially, none of the nodes have been visited
    vector<bool> visited(adjMatrix[0].size(), false);

    // Visit the start node and also enqueue this start node
    visited[start] = true;
    std::queue<int> q;
    q.push(start);

    int curr;
    while (!q.empty()) { 
        curr = q.front(); 
  
        // Print the current node 
        cout << curr << " "; 
        q.pop();
  
        // For every vertex v that is adjacent to the current vertex,
        // if it has not been already marked as visited, push v to
        // the queue and mark it as visited,
        for (int i = 0; i < adjMatrix[0].size(); i++) { 
            if (adjMatrix[curr][i] != 0 && (!visited[i])) { 
  
                // Push the adjacent node to the queue 
                q.push(i); 
  
                // Set this adjacent node to "visited"
                visited[i] = true; 
            } 
        } 
    } 
}





