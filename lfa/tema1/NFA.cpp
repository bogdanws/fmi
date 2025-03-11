#include "NFA.h"
#include "utils.h"

NFA::NFA() {
    isValid = false;
}

bool NFA::readFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }
    
    enum Section {
        NONE,
        SIGMA,
        STATES,
        TRANSITIONS
    };
    
    Section currentSection = NONE;
    std::string line;
    
    while (std::getline(file, line)) {
        // Skip comments
        if (line.empty() || line[0] == '#') {
            continue;
        }
        
        std::string trimmedLine = transformLine(line);
        
        // Check for section headers
        if (trimmedLine == "sigma:") {
            currentSection = SIGMA;
            continue;
        } else if (trimmedLine == "states:") {
            currentSection = STATES;
            continue;
        } else if (trimmedLine == "transitions:") {
            currentSection = TRANSITIONS;
            continue;
        } else if (trimmedLine == "end") {
            currentSection = NONE;
            continue;
        }
        
        switch (currentSection) {
            case SIGMA:
                {
                    std::string symbol = line;
                    symbol.erase(remove_if(symbol.begin(), symbol.end(), ::isspace), symbol.end());
                    if (!symbol.empty()) {
                        sigma.insert(symbol[0]); // Take only the first character
                    }
                }
                break;
                
            case STATES:
                // Format: "q0, S" or "q1" or "q4, F" (S=start, F=final)
                {
                    std::istringstream ss(line);
                    std::string stateName;
                    std::getline(ss, stateName, ',');
                    
                    stateName.erase(remove_if(stateName.begin(), stateName.end(), ::isspace), stateName.end());
                    
                    if (stateName.size() > 1 && stateName[0] == 'q') {
                        try {
                            int stateNum = std::stoi(stateName.substr(1));
                            states.insert(stateNum);
                            
                            // Check for state markers (S=start, F=final)
                            std::string restOfLine;
                            if (std::getline(ss, restOfLine)) {
                                // Remove whitespace
                                restOfLine.erase(remove_if(restOfLine.begin(), restOfLine.end(), ::isspace), restOfLine.end());
                                
                                if (restOfLine == "S") {
                                    initialState = stateNum;
                                } else if (restOfLine == "F") {
                                    finalStates.insert(stateNum);
                                } else if (restOfLine == "S,F" || restOfLine == "F,S") {
                                    initialState = stateNum;
                                    finalStates.insert(stateNum);
                                }
                            }
                        } catch (const std::exception& e) {
                            std::cerr << "Error parsing state: " << stateName << std::endl;
                            return false;
                        }
                    } else {
                        std::cerr << "Invalid state format: " << stateName << std::endl;
                        return false;
                    }
                }
                break;
                
            case TRANSITIONS:
                // Format: "q0, a, q1"
                {
                    std::istringstream ss(line);
                    std::string fromStateStr, symbolStr, toStateStr;
                    
                    // Parse fromState
                    if (!std::getline(ss, fromStateStr, ',')) {
                        std::cerr << "Error parsing transition source state from: " << line << std::endl;
                        return false;
                    }
                    fromStateStr.erase(remove_if(fromStateStr.begin(), fromStateStr.end(), ::isspace), fromStateStr.end());
                    
                    // Parse symbol
                    if (!std::getline(ss, symbolStr, ',')) {
                        std::cerr << "Error parsing transition symbol from: " << line << std::endl;
                        return false;
                    }
                    symbolStr.erase(remove_if(symbolStr.begin(), symbolStr.end(), ::isspace), symbolStr.end());
                    
                    // Parse toState
                    if (!std::getline(ss, toStateStr)) {
                        std::cerr << "Error parsing transition target state from: " << line << std::endl;
                        return false;
                    }
                    toStateStr.erase(remove_if(toStateStr.begin(), toStateStr.end(), ::isspace), toStateStr.end());
                    
                    // Convert state names to integers
                    try {
                        int fromState = -1, toState = -1;
                        
                        if (fromStateStr.size() > 1 && fromStateStr[0] == 'q') {
                            fromState = std::stoi(fromStateStr.substr(1));
                        } else {
                            std::cerr << "Invalid source state format: " << fromStateStr << std::endl;
                            return false;
                        }
                        
                        if (toStateStr.size() > 1 && toStateStr[0] == 'q') {
                            toState = std::stoi(toStateStr.substr(1));
                        } else {
                            std::cerr << "Invalid target state format: " << toStateStr << std::endl;
                            return false;
                        }
                        
                        // Add the transition if symbol is valid
                        if (!symbolStr.empty()) {
                            char symbol = symbolStr[0];
                            transitions[{fromState, symbol}].insert(toState);
                        } else {
                            std::cerr << "Empty transition symbol" << std::endl;
                            return false;
                        }
                    } catch (const std::exception& e) {
                        std::cerr << "Error parsing transition: " << line << std::endl;
                        return false;
                    }
                }
                break;
                
            case NONE:
                break;
        }
    }
    
    file.close();
    
    // Validate the NFA
    isValid = validate();
    return isValid;
}

bool NFA::validate() {
    return validateStates() && validateSigma() && validateTransitions() && 
           validateInitialState() && validateFinalStates();
}

bool NFA::validateStates() const {
    // States set should not be empty
    return !states.empty();
}

bool NFA::validateSigma() const {
    // Alphabet should not be empty
    return !sigma.empty();
}

bool NFA::validateTransitions() const {
    // Check if all transitions use valid states and symbols
    for (const auto& [transition, toStates] : transitions) {
        int fromState = transition.first;
        char symbol = transition.second;
        
        // Check if fromState is valid
        if (states.find(fromState) == states.end()) {
            std::cerr << "Invalid transition: state " << fromState << " not in the set of states" << std::endl;
            return false;
        }
        
        // Check if symbol is valid
        if (sigma.find(symbol) == sigma.end()) {
            std::cerr << "Invalid transition: symbol " << symbol << " not in the alphabet" << std::endl;
            return false;
        }
        
        // Check if all target states are valid
        for (int toState : toStates) {
            if (states.find(toState) == states.end()) {
                std::cerr << "Invalid transition: target state " << toState << " not in the set of states" << std::endl;
                return false;
            }
        }
    }
    
    return true;
}

bool NFA::validateInitialState() const {
    // Check if initialState is in the set of states
    return states.find(initialState) != states.end();
}

bool NFA::validateFinalStates() const {
    // Check if all final states are in the set of states
    for (int state : finalStates) {
        if (states.find(state) == states.end()) {
            std::cerr << "Invalid final state: " << state << " not in the set of states" << std::endl;
            return false;
        }
    }
    
    return !finalStates.empty();
}

bool NFA::accepts(const std::string& input) {
    if (!isValid) {
        std::cerr << "Cannot check acceptance: automaton is not valid" << std::endl;
        return false;
    }
    
    // Start with the initial state
    std::set<int> currentStates = {initialState};
    
    // Process each character in the input
    for (char c : input) {
        if (sigma.find(c) == sigma.end()) {
            // Input contains a symbol not in the alphabet
            return false;
        }
        
        // Compute the next set of states
        std::set<int> nextStates;
        for (int state : currentStates) {
            auto it = transitions.find({state, c});
            if (it != transitions.end()) {
                // Add all possible destination states
                nextStates.insert(it->second.begin(), it->second.end());
            }
        }
        
        currentStates = nextStates;
        
        // If we have no active states, reject
        if (currentStates.empty()) {
            return false;
        }
    }
    
    // Check if any of the current states is a final state
    for (int state : currentStates) {
        if (finalStates.find(state) != finalStates.end()) {
            return true;
        }
    }
    
    return false;
}

void NFA::printDetails() const {
    std::cout << "States: ";
    for (int state : states) {
        std::cout << state << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Alphabet: ";
    for (char symbol : sigma) {
        std::cout << symbol << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Transitions:" << std::endl;
    for (const auto& [transition, toStates] : transitions) {
        int fromState = transition.first;
        char symbol = transition.second;
        
        std::cout << "  " << fromState << " -- " << symbol << " --> ";
        for (int toState : toStates) {
            std::cout << toState << " ";
        }
        std::cout << std::endl;
    }
    
    std::cout << "Initial state: " << initialState << std::endl;
    
    std::cout << "Final states: ";
    for (int state : finalStates) {
        std::cout << state << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Automaton is " << (isValid ? "valid" : "invalid") << std::endl;
} 