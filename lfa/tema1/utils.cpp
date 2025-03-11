#include "utils.h"

std::string transformLine(std::string line) {
    std::string trimmedLine = line;
    trimmedLine.erase(remove_if(trimmedLine.begin(), trimmedLine.end(), ::isspace), trimmedLine.end());
    std::transform(trimmedLine.begin(), trimmedLine.end(), trimmedLine.begin(), ::tolower);
    return trimmedLine;
} 