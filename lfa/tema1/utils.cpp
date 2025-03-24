#include "utils.h"
#include <stdexcept>

std::string transformLine(std::string line) {
    std::string trimmedLine = line;
    trimmedLine.erase(remove_if(trimmedLine.begin(), trimmedLine.end(), ::isspace), trimmedLine.end());
    std::transform(trimmedLine.begin(), trimmedLine.end(), trimmedLine.begin(), ::tolower);
    return trimmedLine;
}

std::string removeWhitespace(std::string str) {
    str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
    return str;
}

int parseStateName(const std::string& stateName) {
    if (!isValidStateName(stateName)) {
        return -1;
    }
    
    try {
        return std::stoi(stateName.substr(1));
    } catch (const std::exception&) {
        return -1;
    }
}

bool isValidStateName(const std::string& stateName) {
    if (stateName.size() < 2 || stateName[0] != 'q') {
        return false;
    }
    
    // Check if all characters after 'q' are digits
    return std::all_of(stateName.begin() + 1, stateName.end(), ::isdigit);
} 