#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <algorithm>

// Remove whitespace and convert to lowercase
std::string transformLine(std::string line);

// Remove all whitespace from a string
std::string removeWhitespace(std::string str);

// Parse a state name in the format "qX" and return the number (X)
// Returns -1 if the format is invalid
int parseStateName(const std::string& stateName);

// Validate if a string is a valid state name (starts with a 'q' followed by a number)
bool isValidStateName(const std::string& stateName);

#endif // UTILS_H 