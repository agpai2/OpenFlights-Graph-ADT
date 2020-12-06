#include "Graph.h"
#include <cmath>
#include <map>
#include <iostream>
#include <vector>
#include <queue>
#include <limits.h> 

Graph::Graph() {
   adjMatrix.resize(100, std::vector<double>(100, 0));

}

Graph::Graph(std::map<int, std::vector<std::string>> airportMap, std::map<int, std::vector<std::string>> routeMap) {

    adjMatrix.resize(airportMap[0].size(), std::vector<double>(airportMap[0].size(), 0));

    for (size_t i = 0; i < airportMap[0].size(); i++) {
        
        // if (airportMap[4][i].length() == 3) {
            Airport airportTemp(i + 1, airportMap[1][i], airportMap[2][i],
                                airportMap[4][i], airportMap[5][i], std::stod(airportMap[6][i]), std::stod(airportMap[7][i]));
        
            airportCodeMap[airportMap[4][i]] = airportTemp;
        
        // } else {
        //     Airport airportTemp(i + 1, airportMap[1][i], airportMap[2][i],
        //                         "INVALID", airportMap[5][i], std::stod(airportMap[6][i]), std::stod(airportMap[7][i]));
        
        //     airportCodeMap[airportMap[4][i]] = airportTemp;
        // }
    }

    //adjMatrix.resize(airportCodeMap.size(), std::vector<double>(airportCodeMap.size(), 0));
    
    for (size_t i = 0; i < routeMap[0].size(); i++) {
        if (airportCodeMap.count(routeMap[2][i]) != 0 && airportCodeMap.count(routeMap[4][i]) != 0)
            addEdge(airportCodeMap[routeMap[2][i]], airportCodeMap[routeMap[4][i]]);

        // TODO deal with invalid
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
        for (size_t i = 0; i < adjMatrix[0].size(); i++) { 
            if (adjMatrix[curr][i] != 0 && (!visited[i])) { 
  
                // Push the adjacent node to the queue 
                q.push(i); 
  
                // Set this adjacent node to "visited"
                visited[i] = true; 
            } 
        } 
    } 
}

int Graph::getNumVertices() {
    return adjMatrix[0].size(); 
}

int Graph::getIncidentEdges(int airportIndex) {
    
    int dest = 0;
    for (size_t i = 0; i < adjMatrix[airportIndex - 1].size(); i++) {
        if (adjMatrix[airportIndex - 1][i] != 0) {
        dest++;
        }
    }
    return dest;

}

vector<vector<double>> Graph::getAdjacencyMatrix() {
    return adjMatrix;
}


double Graph::manhattanDistance(Airport source, Airport destination) {

    //Make this part a function later on

    long double one_deg = (M_PI) / 180;

    double source_lat = one_deg * source.getLatitude();
    double source_long = one_deg * source.getLongitude();
    double dest_lat = one_deg * destination.getLatitude();
    double dest_long = one_deg * destination.getLongitude();

    // Haversine Formula
    long double dlong = dest_long - source_long;
    long double dlat = dest_lat - source_lat;

    return abs(dlong) + abs(dlat);
}


double Graph::chebyshevDistance(Airport source, Airport destination) {

    long double one_deg = (M_PI) / 180;

    double source_lat = one_deg * source.getLatitude();
    double source_long = one_deg * source.getLongitude();
    double dest_lat = one_deg * destination.getLatitude();
    double dest_long = one_deg * destination.getLongitude();
        // Haversine Formula
    long double dlong = dest_long - source_long;
    long double dlat = dest_lat - source_lat;

    return max(abs(dlong), abs(dlat));
}

  
int Graph::minDist(std::vector<int>& dist, std::vector<bool>  &reached) { 
    int min = INT_MAX; 
    int minIndex; 

    for (int vertex = 0; vertex < getNumVertices(); vertex++) {
        if (reached[vertex] == false && dist[vertex] <= min) {
            min = dist[vertex], minIndex = vertex; 
        }
    }
  
    return minIndex; 
} 

std::vector<int> Graph::djikstra(int src, int dest) {  

    const int numVertices = getNumVertices(); 

    std::vector<int> distVec(numVertices);
    std::vector<bool> reachedVec(numVertices);
    std::vector<int> parentVec(numVertices); 

    // distance of the source node from itself is 0
    distVec[src] = 0;
  
    // the path starts at the source
    parentVec[src] = -1;

    for (int i = 0; i < numVertices; i++) { 
        if (i != src)
            distVec[i] = INT_MAX; 

        reachedVec[i] = false; 
    } 
  
    distVec[src] = 0; 
  
    for (int i = 0; i < numVertices; i++) { 
        int u = minDist(distVec, reachedVec); 
  
        reachedVec[u] = true; 
   
        for (int v = 0; v < numVertices; v++) { 
            if (!reachedVec[v] && adjMatrix[u][v] && (distVec[u] + adjMatrix[u][v] < distVec[v])) { 
                parentVec[v] = u; 
                distVec[v] = distVec[u] + adjMatrix[u][v]; 
            }  
        }
    } 

    vector<int> requiredPath;
    if (distVec[dest] != INT_MAX) {
        std::cout << src << " " << dest << distVec[dest] << std::endl;
        int j = dest;
        while (parentVec[j] != -1) {
            requiredPath.push_back(parentVec[j]);
            j = parentVec[j];
        }
        std::reverse(requiredPath.begin(), requiredPath.end());
    } else {
        std::cout << "Path doesn't exist" << std::endl;
    }

    return requiredPath;
}

std::vector<int> Graph::landmarkPath(std::string startNode, std::string intermediateNode, std::string endNode) {
    
    int src = airportCodeMap[startNode].getId() - 1;
    int landmark = airportCodeMap[intermediateNode].getId() - 1;
    int dest = airportCodeMap[endNode].getId() - 1;
    const int numVertices = getNumVertices(); 

    std::vector<int> landmarkPathSoln;

    // get path from A to C and store it in a vector of ints
    std::vector<int> pathFromAToC = djikstra(src, landmark);

    // get path from C to B and store it in a vector of ints
    std::vector<int> pathFromCToB = djikstra(landmark, dest);

    // combine the two vectors above and output that vector
    for (int i = 0; i < pathFromAToC.size(); i++) {
        landmarkPathSoln.push_back(pathFromAToC[i]);
    }

    for (int i = 0; i < pathFromCToB.size(); i++) {
        landmarkPathSoln.push_back(pathFromCToB[i]);
    }

    // push back the destination as well to the path
    landmarkPathSoln.push_back(dest);

    return landmarkPathSoln;
}