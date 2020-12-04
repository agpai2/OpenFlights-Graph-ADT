#define CATCH_CONFIG_MAIN
#include "../catch/catch.hpp"

#include "../Graph.h"
#include "../Airport.h"
#include "../readFromFile.hpp"

#include <sys/time.h>
#include <vector>
#include <unordered_set>
#include <utility>
#include <map>

#include <string>

std::vector<std::vector<double>> adjMatrix;
void createAdjacencyMatrix(int numberOfNodes) {
    for (int i = 0; i < numberOfNodes; i++) {
        for (int j = 0; j < numberOfNodes; j++) {
            struct timeval time;
            gettimeofday(&time, NULL);
            srand(time.tv_usec);
            double randVal = (double) rand() / RAND_MAX;
            if (randVal <= 4) {
                adjMatrix[i][j] = 0;
            } else {
                adjMatrix[i][j] = (randVal - 4) * 100;
            }
        }
    }
}

std::map<int, std::vector<std::string>> sample_1 = csv_reader("tests/sample1.csv");
std::map<int, std::vector<std::string>> sample_2 = csv_reader("tests/sample2.csv");

Graph small_graph(sample_1, sample_2);

std::map<int, std::vector<std::string>> airports = csv_reader("data/airports.csv");
std::map<int, std::vector<std::string>> routes = csv_reader("data/routes.csv");

Graph big_graph(airports, routes);

TEST_CASE("Graph Default Constructor", "[weight=1]") {
  Graph g = Graph();
  REQUIRE(g.getNumVertices() == 100);

  bool isZero = true;
  vector<vector<double>> matrix = g.getAdjacencyMatrix();
  for (int i = 0; i < g.getNumVertices(); i++) {
      for (int j = 0; j < g.getNumVertices(); j++) {
          if (matrix[i][j] != 0)
            isZero = false;  
            goto end;        
      }
  }

  end:
  
  REQUIRE(isZero);
}

TEST_CASE("Number of vertices - Small Data", "[weight=1]") {
  REQUIRE(small_graph.getNumVertices() == sample_1[0].size());
}

TEST_CASE("Number of vertices - Big Data", "[weight=2]") {
  REQUIRE(big_graph.getNumVertices() == airports[0].size());
}

TEST_CASE("Number of edges - Small Data", "[weight=1]") {

}

TEST_CASE("Number of edges - Big Data", "[weight=2]") {

}

TEST_CASE("Number of incident edges - Small Data", "[weight=1]") {
  std::string source = "PEN";
  int source_idx = 0;

  std::unordered_set<std::string> destinations;
  for (size_t i = 0; i < sample_2[2].size(); i++) {
    if ((sample_2[2][i] == source)) {
      destinations.insert(sample_2[4][i]);
    }
  }

  for (size_t i = 0; i < sample_1[4].size(); i++) {
    if (sample_1[4][i] == source) {
      source_idx = i + 1;
      break;
    }
  }

  vector<vector<double>> adj_matrix = small_graph.getAdjacencyMatrix();

  int dest = 0;
  for (size_t i = 0; i < adj_matrix[source_idx - 1].size(); i++) {
    if (adj_matrix[source_idx - 1][i] != 0) {
      dest++;
    }
  }

  // std::cout << "Sample IATA: " << sample_1[4][source_idx - 1] << std::endl;
  // std::cout << "Destinations of PEN: " << edges << std::endl;
  // std::cout << "Index of PEN in sample1.csv: " << source_idx << std::endl;
  // std::cout << "Destinations of PEN in matrix: " << dest << std::endl;
  REQUIRE(destinations.size() == dest);
}

TEST_CASE("Number of incident edges - Big Data", "[weight=2]") {
  std::string source_airport = "KZN";
  int source_idx = 0;

  std::unordered_set<std::string> destinations;
  for (size_t i = 0; i < routes[2].size(); i++) {
    if ((routes[2][i] == source_airport)) {
      destinations.insert(routes[4][i]);
    }
  }

  for (size_t i = 0; i < airports[4].size(); i++) {
    if (airports[4][i] == source_airport) {
      source_idx = i + 1;
      break;
    }
  }

  vector<vector<double>> adj_matrix = big_graph.getAdjacencyMatrix();

  int dest = 0;
  for (size_t i = 0; i < adj_matrix[source_idx - 1].size(); i++) {
    if (adj_matrix[source_idx - 1][i] != 0) {
      dest++;
    }
  }

  // std::cout << "Airport IATA: " << airports[4][source_idx - 1] << std::endl;
  // std::cout << "Destinations of KZN: " << edges << std::endl;
  // std::cout << "Index of KZN in airports.csv: " << source_idx << std::endl;
  // std::cout << "Destinations of KZN in matrix: " << dest;

  REQUIRE(destinations.size() == dest);
}

TEST_CASE("Check if nodes are adjacent - Small Data", "[weight=1]") {
  int index = 0;

  std::string src = sample_2[2][index];
  std::string destination = sample_2[4][index];

  int source_idx = 0;
  int dest_idx = 0;

  bool source = false;
  bool dest = false;
  for (size_t i = 0; i < sample_1[4].size(); i++) {
    if (sample_1[4][i] == src) {
      source_idx = i + 1;
      source = true;
    } else if (sample_1[4][i] == destination) {
      dest_idx = i + 1;
      dest = true;
    }

    if (source && dest) {
      break;
    }
  }

  Airport s(source_idx, "", "", "", "", 0.0, 0.0);
  Airport d(dest_idx, "", "", "", "", 0.0, 0.0);

  REQUIRE(small_graph.areAdjacent(s, d));
}

TEST_CASE("Check if nodes are adjacent - Big Data", "[weight=2]") {
  int index = rand() % routes[0].size();

  std::string source_airport = routes[2][index];
  std::string dest_airport = routes[4][index];

  int source_idx = 0;
  int dest_idx = 0;

  bool source = false;
  bool dest = false;
  for (size_t i = 0; i < airports[4].size(); i++) {
    if (airports[4][i] == source_airport) {
      source_idx = i + 1;
      source = true;
    } else if (airports[4][i] == dest_airport) {
      dest_idx = i + 1;
      dest = true;
    }

    if (source && dest) {
      break;
    }
  }

  Airport s(source_idx, "", "", "", "", 0.0, 0.0);
  Airport d(dest_idx, "", "", "", "", 0.0, 0.0);

  REQUIRE(big_graph.areAdjacent(s, d));
}

TEST_CASE("Breadth First Traversal", "[weight=1]") {

}