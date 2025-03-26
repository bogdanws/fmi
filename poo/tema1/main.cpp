// Andreiana Bogdan Mihail - grupa 151 - C++23
// pentru a rula programul, se compileaza cu make, iar apoi se ruleaza ./automaton
#include <iostream>
#include <string>
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
        std::cout << "\nEnter a string to check if it's accepted by the automaton: ";
        std::cin >> input;
        
        if (automaton->accepts(input)) {
            std::cout << "String accepted!" << std::endl;
        } else {
            std::cout << "String rejected!" << std::endl;
        }
    } else {
        std::cout << "Failed to read or validate the automaton." << std::endl;
    }
    
    delete automaton;
    return 0;
}