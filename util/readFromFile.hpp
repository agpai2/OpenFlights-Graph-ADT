#pragma once

#include <string>
#include <vector>
#include <map>

// adapted from CS 225 Final Project AMA

/** 
 * Reads a text file into a string
 * @param filename The file to read from 
 * @return a string containing filename's contents
 */
std::string file_to_string(const std::string & filename);

/** 
 * Reads a text file into a vector
 * @param filename The file to read from
 * @return a vector containing filename's contents
 */
std::vector<std::string> file_to_vector(const std::string & filename);

/** 
 * Reads a csv file into a map
 * @param filename The file to read from
 * @return a map containing filename's contents
 */
std::map<int, std::vector<std::string>> csv_reader(const std::string &filename);