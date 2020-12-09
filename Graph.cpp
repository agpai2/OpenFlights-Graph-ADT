#include "Graph.h"
#include <cmath>
#include <map>
#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <limits.h> 


using namespace cs225;

Graph::Graph() {
    // 100 here is arbitrarily chosen
   adjMatrix.resize(100, std::vector<double>(100, 0));
}

Graph::Graph(std::map<int, std::vector<std::string>> airportMap, std::map<int, std::vector<std::string>> routeMap) {

    // resize adjacency matrix to have a size equal to the number of airports 
    adjMatrix.resize(airportMap[0].size(), std::vector<double>(airportMap[0].size(), 0));

    for (size_t i = 0; i < airportMap[0].size(); i++) {

        // create airport object with relevent data from the csv and insert into map; the various constants here
        // refer to column numbers in the dataset
        Airport airportTemp(i + 1, airportMap[1][i], airportMap[2][i],
                            airportMap[4][i], airportMap[5][i], std::stod(airportMap[6][i]), 
                            std::stod(airportMap[7][i]));
        
        airportCodeMap[airportMap[4][i]] = airportTemp;
    }
    
    // add edges in our graph
    for (size_t i = 0; i < routeMap[0].size(); i++) {
        if (airportCodeMap.count(routeMap[2][i]) != 0 && airportCodeMap.count(routeMap[4][i]) != 0)
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
    for (int i = 0; i < v; i++) {
        printf("[");
        for (int j = 0; j < v; j++) {
            std::cout << std::fixed << std::showpoint;
            std::cout << std::setprecision(2);

            std::cout << " " << adjMatrix[i][j] << " ";
        }
        printf("]\n");
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
    if (getNumberOfDestinations(start) == 0) {
        std::cout << "This airport has no destinations" << std::endl;
        return;
    }

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

int Graph::getNumberOfDestinations(int startAirport) {
    // To find the number of destinations reachable from startAirport,
    // we count the number of non-zero entries in the row corresponding to
    // startAiport in the adjacency matrix
    int dest = 0;
    for (size_t i = 0; i < adjMatrix[startAirport].size(); i++) {
        if (adjMatrix[startAirport][i] != 0) 
            dest++;
    }
    return dest;
}

std::map<std::string, Airport> Graph::getAirportCodeMap() {
    return airportCodeMap;
}

vector<vector<double>> Graph::getAdjacencyMatrix() {
    return adjMatrix;
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

std::vector<int> Graph::dijkstra(int src, int dest) {  
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
        // std::cout << src << " " << dest << distVec[dest] << std::endl;
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

    std::vector<int> landmarkPathSoln;

    // get path from A to C and store it in a vector of ints
    std::vector<int> pathFromAToC = dijkstra(src, landmark);

    // get path from C to B and store it in a vector of ints
    std::vector<int> pathFromCToB = dijkstra(landmark, dest);

    // combine the two vectors above and output that vector
    for (size_t i = 0; i < pathFromAToC.size(); i++) {
        landmarkPathSoln.push_back(pathFromAToC[i]);
    }

    for (size_t i = 0; i < pathFromCToB.size(); i++) {
        landmarkPathSoln.push_back(pathFromCToB[i]);
    }

    // push back the destination as well to the path
    landmarkPathSoln.push_back(dest);

    return landmarkPathSoln;
}

std::pair<double, double> Graph::getXYCoordinates(double lat, double longt, cs225::PNG image) {
    double temp_lat = lat >= 0 ? 90 - lat : 90 + abs(lat);
    double temp_long = longt + 180;

    double y = (temp_lat / 181) * image.height();
    double x = (temp_long / 361) * image.width();

    std::pair<double, double> coord(x, y);

    return coord;
}

void Graph::plotLandmarkPath(std::vector<string> path) {
    cs225::PNG plottedMap;
    plottedMap.readFromFile("images/map.png");

    // Plots the landmark points on the map
    for(size_t i = 0; i < path.size(); i++) {
        double lon = airportCodeMap[path[i]].getLongitude();
        double lat = airportCodeMap[path[i]].getLatitude();

        std::pair<double, double> coord = getXYCoordinates(lat, lon, plottedMap);

        for (int i = -1; i <= 1; i++) {
            cs225::HSLAPixel &pixel_x = plottedMap.getPixel(coord.first + i, coord.second);
            cs225::HSLAPixel &pixel_y = plottedMap.getPixel(coord.first, coord.second + i);

            cs225::HSLAPixel airportPixel(28, 1, 0.5, 1);

            pixel_x = airportPixel;
            pixel_y = airportPixel;
        }
    }

    for (size_t i = 0; i < path.size() - 1; i++) {
        double lon1 = airportCodeMap[path[i]].getLongitude();
        double lat1 = airportCodeMap[path[i]].getLatitude();

        std::pair<double, double> coord1 = getXYCoordinates(lat1, lon1, plottedMap);

        double lon2 = airportCodeMap[path[i + 1]].getLongitude();
        double lat2 = airportCodeMap[path[i + 1]].getLatitude();

        std::pair<double, double> coord2 = getXYCoordinates(lat2, lon2, plottedMap);

        for (int i = coord1.first; i < coord2.first; i++) {
            double y_val = (((coord2.second - coord1.second) / (coord2.first - coord1.first)) * 
                    abs((i - coord1.first))) + coord1.second;

            unsigned int y_entry = abs(round(y_val));
            unsigned int x_entry = i;
            if (abs(i) < plottedMap.width() && abs(round(y_val)) < plottedMap.height()) {
                cs225::HSLAPixel &pixel = plottedMap.getPixel(x_entry, y_entry);
                cs225::HSLAPixel pathPixel(300, 1, 0.5, 1);
                pixel = pathPixel;
            }
        }

        for (int i = coord2.first; i < coord1.first; i++) {
            double y_val = (((coord1.second - coord2.second) / (coord1.first - coord2.first)) * 
                    abs((i - coord2.first))) + coord2.second;

            unsigned int y_entry = abs(round(y_val));
            unsigned int x_entry = i;
            if (abs(i) < plottedMap.width() && abs(round(y_val)) < plottedMap.height()) {
                cs225::HSLAPixel &pixel = plottedMap.getPixel(x_entry, y_entry);
                cs225::HSLAPixel pathPixel(300, 1, 0.5, 1);
                pixel = pathPixel;
            }
        }
    }
    
    plottedMap.writeToFile("images/landmark_path.png");
}

void Graph::plotAirports() {

    PNG plottedMap;
    plottedMap.readFromFile("images/map.png");

    for (std::map<string, Airport>::iterator it = airportCodeMap.begin(); it != airportCodeMap.end(); ++it) {

        double lon = it->second.getLongitude();
        double lat = it->second.getLatitude();

        double temp_lat = lat >= 0 ? 90 - lat : 90 + abs(lat);
        double temp_long = lon + 180;

        double y = (temp_lat / 181) * plottedMap.height();
        double x = (temp_long / 361) * plottedMap.width();

        cs225::HSLAPixel &pixel = plottedMap.getPixel(x, y);
        cs225::HSLAPixel airportPixel(28, 1, 0.5, 1);

        pixel = airportPixel;
    }

    plottedMap.writeToFile("images/airports.png");
}
