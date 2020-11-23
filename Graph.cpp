#include "Graph.h"


Graph::Graph() {
    adjMatrix.resize(_MAX_INT_DIG);
}


void Graph::addEdge(Airport source, Airport destination) {

    double euclideanDist = euclideanDistance(source, destination);
    adjMatrix[source.getId() - 1][destination.getId() - 1] = euclideanDist;
}


bool Graph::isAdjacent(Airport source, Airport destination) {

    return adjMatrix[source.getId() - 1][destination.getId() - 1] != 0.0;

}

double Graph::euclideanDistance(Airport source, Airport destination) {
    return 0.0;
}





