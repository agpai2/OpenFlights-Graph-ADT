#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;


std::string file_to_string(const std::string & filename) {
	std::ifstream text(filename);
	
	std::stringstream strStream;
	if (text.is_open()) {
		strStream << text.rdbuf();
	}

	return strStream.str();
}

std::vector<std::string> file_to_vector(const std::string & filename) {
	std::ifstream text(filename);
	std::vector<std::string> out;

	if (text.is_open()) {
		std::istream_iterator<std::string> iter(text);
		while (!text.eof()) {
			out.push_back(*iter);
			++iter;
		}
	}

	return out;
}

std::vector<std::string> read_csv(const std::string &filename) {
	std::ifstream file(filename);

	if (!file.is_open())
		throw std::runtime_error("Could not open file");

	std::string line, attribute;
	std::vector<std::string> result;

	if (file.good()) {
		while (std::getline(file, line)) {

			std::stringstream ss(line);
			// Extract each column name
			while (std::getline(ss, attribute, ',')) {
				// attribute.erase(std::remove(attribute.begin(), attribute.end(), '\"'), attribute.end());
				if (attribute.empty()) {
					result.push_back(attribute);
					continue;
				}
				if (attribute[0] == '"' && attribute[attribute.size() - 1] != '"') {
					std::string stringTemp = (attribute + ",");
					std::getline(ss, attribute, ',');
					stringTemp += attribute;
					result.push_back(stringTemp);
					continue;
				}
				result.push_back(attribute);
			}
		}
	}

	return result;
}