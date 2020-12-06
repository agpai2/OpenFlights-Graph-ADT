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

TEST_CASE("Number of incident edges - Small Data", "[weight=1]") {
  std::string source = "PEN";

  std::unordered_set<std::string> destinations;
  for (size_t i = 0; i < sample_2[2].size(); i++) {
    if ((sample_2[2][i] == source)) {
      destinations.insert(sample_2[4][i]);
    }
  }

  int source_idx = small_graph.getAirportCodeMap()[source].getId() - 1;

  int dest = small_graph.getIncidentEdges(source_idx);

  // std::cout << "Sample IATA: " << sample_1[4][source_idx] << std::endl;
  // std::cout << "Destinations of PEN: " << edges << std::endl;
  // std::cout << "Index of PEN in sample1.csv: " << source_idx << std::endl;
  // std::cout << "Destinations of PEN in matrix: " << dest << std::endl;
  REQUIRE(destinations.size() == dest);
}

TEST_CASE("Number of incident edges - Big Data", "[weight=2]") {
  std::string source_airport = "KZN";

  std::unordered_set<std::string> destinations;
  for (size_t i = 0; i < routes[2].size(); i++) {
    if ((routes[2][i] == source_airport)) {
      destinations.insert(routes[4][i]);
    }
  }

  int source_idx = big_graph.getAirportCodeMap()[source_airport].getId() - 1;

  int dest = big_graph.getIncidentEdges(source_idx);

  // std::cout << "Airport IATA: " << airports[4][source_idx] << std::endl;
  // std::cout << "Destinations of KZN: " << edges << std::endl;
  // std::cout << "Index of KZN in airports.csv: " << source_idx << std::endl;
  // std::cout << "Destinations of KZN in matrix: " << dest;

  REQUIRE(destinations.size() == dest);
}

TEST_CASE("Check if nodes are adjacent - Small Data", "[weight=1]") {
  int index = 0;

  std::string src = sample_2[2][index];
  std::string destination = sample_2[4][index];

  int source_idx = small_graph.getAirportCodeMap()[src].getId() - 1;
  int dest_idx = small_graph.getAirportCodeMap()[destination].getId() - 1;

  Airport s(source_idx + 1, "", "", "", "", 0.0, 0.0);
  Airport d(dest_idx + 1, "", "", "", "", 0.0, 0.0);

  REQUIRE(small_graph.areAdjacent(s, d));
}

TEST_CASE("Check if nodes are adjacent - Big Data", "[weight=2]") {
  int index = rand() % routes[0].size();

  std::string source_airport = routes[2][index];
  std::string dest_airport = routes[4][index];

  int source_idx = big_graph.getAirportCodeMap()[source_airport].getId() - 1;
  int dest_idx = big_graph.getAirportCodeMap()[dest_airport].getId() - 1;

  Airport s(source_idx + 1, "", "", "", "", 0.0, 0.0);
  Airport d(dest_idx + 1, "", "", "", "", 0.0, 0.0);

  REQUIRE(big_graph.areAdjacent(s, d));
}

TEST_CASE("Breadth First Traversal", "[weight=1]") {

}

TEST_CASE("Landmark Path - Small Data", "[weight=1]") {
  std::vector<int> vec = small_graph.landmarkPath("PEN", "IDR", "BRL");

  std::vector<std::string> path;
  for (size_t i = 0; i < vec.size(); i++) {
    path.push_back(sample_1[4][vec[i]]);
	}

  std::stringstream ss;
  std::copy(path.begin(), path.end(),std::ostream_iterator<std::string>(ss, " "));

  REQUIRE(ss.str() == "PEN IDR CNY BRL ");
}

TEST_CASE("Landmark Path - Big Data", "[weight=2]") {
  std::vector<int> small_path = big_graph.landmarkPath("ASF", "MRV", "SCO");

  std::vector<std::string> path1;
  for (size_t i = 0; i < small_path.size(); i++) {
    path1.push_back(airports[4][small_path[i]]);
	}

  std::stringstream ss1;
  std::copy(path1.begin(), path1.end(),std::ostream_iterator<std::string>(ss1, " "));

  REQUIRE(ss1.str() == "ASF MRV SCO ");

  std::vector<int> big_path = big_graph.landmarkPath("GKA", "CNY", "KZN");

  std::vector<std::string> path2;
  for (size_t i = 0; i < big_path.size(); i++) {
    path2.push_back(airports[4][big_path[i]]);
	}

  std::stringstream ss2;
  std::copy(path2.begin(), path2.end(),std::ostream_iterator<std::string>(ss2, " "));

  REQUIRE(ss2.str() == "GKA POM NAN LAX SLC CNY SLC YYC YEG KEF HEL LED KZN ");
}