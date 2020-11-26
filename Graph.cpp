#include "Graph.h"
#include <cmath>
#include <map>
#include <iostream>

Graph::Graph() {
    //Maybe not required
    //Change it to variable read
    adjMatrix.resize(15000);
}

Graph::Graph(std::vector<std::string> airportVec, std::vector<std::string> routeVec) {
    adjMatrix.resize(15000);
    for (int i = 0; i < 15000; i++) {
        for (int j = 0; j < 15000; j++) {
            adjMatrix[i].push_back(0);
        }
    }

    std::map<std::string, Airport> airportMap;
    for (int i = 0; i < 2818; i++) {
        
        Airport airportTemp(i + 1, airportVec[i*14 + 1], airportVec[i*14 + 2],
                                airportVec[i*14 + 4], airportVec[i*14 + 5], std::stod(airportVec[i*14 + 6]), std::stod(airportVec[i*14 + 7]));
        
        airportMap[airportVec[i*14 + 4]] = airportTemp;
    }
    
    for (int i = 0; i*9 + 4 < routeVec.size(); i++) {
        addEdge(airportMap[routeVec[i*9 + 2]], airportMap[routeVec[i*9 + 4]]);
    }
}

void Graph::addEdge(Airport source, Airport destination) {
    double euclideanDist = euclideanDistance(source, destination);
    adjMatrix[0][0] = 42;
    std::cout << source.getId() << " " << destination.getId() << " " << std:: endl;
    //adjMatrix[source.getId() - 1][destination.getId() - 1] = euclideanDist;
    //adjMatrix[destination.getId() - 1][source.getId() - 1] = euclideanDist;
}


bool Graph::areAdjacent(Airport source, Airport destination) {
    return adjMatrix[source.getId() - 1][destination.getId() - 1] != 0.0;

}

void Graph::displayMatrix(int v) {
   int i, j;
   for(i = 0; i < 5; i++) {
      for(j = 0; j < 5; j++) {
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





