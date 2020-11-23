#include "Graph.h"
#include <cmath>

Graph::Graph() {
    adjMatrix.resize(INT32_MAX);
}


void Graph::addEdge(Airport source, Airport destination) {
    double euclideanDist = euclideanDistance(source, destination);
    adjMatrix[source.getId() - 1][destination.getId() - 1] = euclideanDist;
}


bool Graph::areAdjacent(Airport source, Airport destination) {
    return adjMatrix[source.getId() - 1][destination.getId() - 1] != 0.0;

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





