// Andreiana Bogdan Mihail - grupa 151 - C++23
// pentru a rula programul, se compileaza cu make, iar apoi se ruleaza ./automaton
#include <iostream>
#include <string>
#include <limits> // Required for std::numeric_limits
#include <algorithm>
#include "NFA.h"
#include "DFA.h"

int main() {
    std::string filename;
    std::cout << "Enter the automaton file name: ";
    std::cin >> filename;
    
    std::string automataType;
    std::cout << "Enter the type (NFA/DFA): ";
    std::cin >> automataType;
    std::transform(automataType.begin(), automataType.end(), automataType.begin(), ::tolower);
    
    NFA* automaton = nullptr;
    if (automataType == "dfa") {
        automaton = new DFA();
    } else {
        automaton = new NFA();
    }
    
    std::cout << "\nAttempting to read automaton " << filename << "." << std::endl;
    
    if (automaton->readFromFile(filename)) {
        std::cout << "\n\t Automaton Details\n" << std::endl;
        std::cout << *automaton;
        
        std::string input;
        // consume the newline character left by previous std::cin
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        while (true) {
            std::cout << "\nEnter a string to check (or press Enter to exit): ";
            std::getline(std::cin, input);

            if (input.empty()) {
                break;
            }

            if (automaton->accepts(input)) {
                std::cout << "String \"" << input << "\" accepted!" << std::endl;
            } else {
                std::cout << "String \"" << input << "\" rejected!" << std::endl;
            }
        }
    } else {
        std::cout << "Failed to read or validate the automaton." << std::endl;
    }
    
    delete automaton;
    return 0;
}