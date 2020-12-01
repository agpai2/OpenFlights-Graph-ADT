#define CATCH_CONFIG_MAIN
#include "../catch/catch.hpp"

#include "../Graph.h"
#include "../Airport.h"
#include "../readFromFile.hpp"

#include <sys/time.h>
#include <vector>
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
  std::map<int, std::vector<std::string>> small_dat_1 = csv_reader("tests/sample1.csv");
  std::map<int, std::vector<std::string>> small_dat_2 = csv_reader("tests/sample2.csv");

  Graph g(small_dat_1, small_dat_2);

  REQUIRE(g.getNumVertices() == small_dat_1[0].size());
}

TEST_CASE("Number of vertices - Big Data", "[weight=2]") {
  std::map<int, std::vector<std::string>> big_dat_1 = csv_reader("data/airports.csv");
  std::map<int, std::vector<std::string>> big_dat_2 = csv_reader("data/routes.csv");

  Graph g(big_dat_1, big_dat_2);

  REQUIRE(g.getNumVertices() == big_dat_1[0].size());
}

TEST_CASE("Number of edges - Small Data", "[weight=1]") {

}

TEST_CASE("Number of edges - Big Data", "[weight=2]") {

}

TEST_CASE("Number of incident edges - Small Data", "[weight=1]") {
  // Run through the routes map, and count total destinations 
  // any ariport to the others

  // match the ID of that source airport in the adj matrix and check if those 
  //actually exist
}

TEST_CASE("Number of incident edges - Big Data", "[weight=2]") {

}

TEST_CASE("Check if nodes are adjacent - Small Data", "[weight=1]") {

}

TEST_CASE("Check if nodes are adjacent - Big Data", "[weight=2]") {

}

TEST_CASE("Breadth First Traversal", "[weight=1]") {

}