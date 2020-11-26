#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <map>

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

std::map<int, std::vector<std::string>> csv_reader(const std::string &filename) {
	std::ifstream file(filename);

	if (!file.is_open())
		throw std::runtime_error("Could not open file");

	std::string line, attribute;
	std::map<int, std::vector<std::string>> result;

	if (file.good()) {
		while (std::getline(file, line)) {
			std::stringstream ss(line);
			int count = 0;
			while (std::getline(ss, attribute, ',')) {
				if (attribute.empty()) {
					result[count++].push_back(attribute);
					continue;
				}
				if (attribute[0] == '"' && attribute[attribute.size() - 1] != '"') {
					std::string stringTemp = (attribute + ",");
					std::getline(ss, attribute, ',');
					stringTemp += attribute;
					stringTemp.erase(std::remove(stringTemp.begin(), stringTemp.end(), '\"'), stringTemp.end());
					result[count++].push_back(stringTemp);
					continue;
				}
				attribute.erase(std::remove(attribute.begin(), attribute.end(), '\"'), attribute.end());
				result[count++].push_back(attribute);
			}
		}
	}

	return result;
}