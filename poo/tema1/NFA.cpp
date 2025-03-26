#include "NFA.h"
#include "utils.h"

NFA::NFA() {
    isValid = false;
}

NFA::NFA(const NFA& other) {
    states = other.states;
    sigma = other.sigma;
    transitions = other.transitions;
    initialState = other.initialState;
    finalStates = other.finalStates;
    isValid = other.isValid;
}

NFA& NFA::operator=(const NFA& other) {
    if (this != &other) {
        states = other.states;
        sigma = other.sigma;
        transitions = other.transitions;
        initialState = other.initialState;
        finalStates = other.finalStates;
        isValid = other.isValid;
    }
    return *this;
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
    
    initialState = -1;
    
    while (std::getline(file, line)) {
        // skip comments
        if (line.empty() || line[0] == '#') {
            continue;
        }
        
        std::string trimmedLine = transformLine(line);
        
        // Section headers
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
                    std::string symbol = removeWhitespace(line);
                    if (!symbol.empty()) {
                        sigma.insert(symbol[0]); // only take the first character
                    }
                }
                break;
                
            case STATES:
                // format: "q0, S" / "q1" / "q2, F" (S=start, F=final)
                {
                    std::istringstream ss(line);
                    std::string stateName;
                    std::getline(ss, stateName, ',');
                    
                    stateName = removeWhitespace(stateName);
                    
                    if (isValidStateName(stateName)) {
                        int stateNum = parseStateName(stateName);
                        if (stateNum != -1) {
                            states.insert(stateNum);
                            
                            // check for state markers (S=start, F=final)
                            std::string restOfLine;
                            if (std::getline(ss, restOfLine)) {
                                restOfLine = removeWhitespace(restOfLine);
                                
                                if (restOfLine == "S") {
                                    if (initialState != -1 && initialState != stateNum) {
                                        std::cerr << "Error: Multiple start states defined. States " << initialState << " and " << stateNum << " are both marked as start states." << std::endl;
                                        return false;
                                    }
                                    initialState = stateNum;
                                } else if (restOfLine == "F") {
                                    finalStates.insert(stateNum);
                                } else if (restOfLine == "S,F" || restOfLine == "F,S") {
                                    if (initialState != -1 && initialState != stateNum) {
                                        std::cerr << "Error: Multiple start states defined. States " << initialState << " and " << stateNum << " are both marked as start states." << std::endl;
                                        return false;
                                    }
                                    initialState = stateNum;
                                    finalStates.insert(stateNum);
                                }
                            }
                        } else {
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
                // format: "q0, a, q1"
                {
                    std::istringstream ss(line);
                    std::string fromStateStr, symbolStr, toStateStr;
                    
                    // parse fromState
                    if (!std::getline(ss, fromStateStr, ',')) {
                        std::cerr << "Error parsing transition source state from: " << line << std::endl;
                        return false;
                    }
                    fromStateStr = removeWhitespace(fromStateStr);
                    
                    // parse symbol
                    if (!std::getline(ss, symbolStr, ',')) {
                        std::cerr << "Error parsing transition symbol from: " << line << std::endl;
                        return false;
                    }
                    symbolStr = removeWhitespace(symbolStr);
                    
                    // parse toState
                    if (!std::getline(ss, toStateStr)) {
                        std::cerr << "Error parsing transition target state from: " << line << std::endl;
                        return false;
                    }
                    toStateStr = removeWhitespace(toStateStr);
                    
                    // convert state names to integers
                    int fromState = parseStateName(fromStateStr);
                    int toState = parseStateName(toStateStr);
                    
                    if (fromState == -1) {
                        std::cerr << "Invalid source state format: " << fromStateStr << std::endl;
                        return false;
                    }
                    
                    if (toState == -1) {
                        std::cerr << "Invalid target state format: " << toStateStr << std::endl;
                        return false;
                    }
                    
                    // add the transition if symbol is valid
                    if (!symbolStr.empty()) {
                        char symbol = symbolStr[0];
                        transitions[{fromState, symbol}].insert(toState);
                    } else {
                        std::cerr << "Empty transition symbol" << std::endl;
                        return false;
                    }
                }
                break;
                
            case NONE:
                break;
        }
    }
    
    file.close();
    
    // validate the NFA
    isValid = validate();
    return isValid;
}

bool NFA::validate() const {
    std::vector<std::string> errors;
    
    if (!validateStates()) errors.push_back("State validation failed");
    if (!validateSigma()) errors.push_back("Alphabet validation failed");
    if (!validateTransitions()) errors.push_back("Transition validation failed");
    if (!validateInitialState()) errors.push_back("Initial state validation failed");
    if (!validateFinalStates()) errors.push_back("Final states validation failed");

    if (!errors.empty()) {
        std::cerr << "Validation errors:\n";
        for (const auto& err : errors) {
            std::cerr << " - " << err << "\n";
        }
        return false;
    }
    return true;
}

bool NFA::validateStates() const {
    return !states.empty();
}

bool NFA::validateSigma() const {
    return !sigma.empty();
}

bool NFA::validateTransitions() const {
    // check if all transitions use valid states and symbols
    for (const auto& [transition, toStates] : transitions) {
        int fromState = transition.first;
        char symbol = transition.second;
        
        // check if fromState is valid
        if (states.find(fromState) == states.end()) {
            std::cerr << "Invalid transition: state " << fromState << " not in the set of states" << std::endl;
            return false;
        }
        
        // check if symbol is valid
        if (sigma.find(symbol) == sigma.end()) {
            std::cerr << "Invalid transition: symbol " << symbol << " not in the alphabet" << std::endl;
            return false;
        }
        
        // check if all target states are valid
        for (int toState : toStates) {
            if (states.find(toState) == states.end()) {
                std::cerr << "Invalid transition: state " << toState << " not in the set of states" << std::endl;
                return false;
            }
        }
    }
    
    return true;
}

bool NFA::validateInitialState() const {
    // check if initialState is valid
    if (initialState == -1) {
        std::cerr << "Invalid initial state: no start state specified" << std::endl;
        return false;
    }
    
    // check if initialState is in the set of states
    if (states.find(initialState) == states.end()) {
        std::cerr << "Invalid initial state: state " << initialState << " not in the set of states" << std::endl;
        return false;
    }
    
    return true;
}

bool NFA::validateFinalStates() const {
    // check if all final states are in the set of states
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
        std::cerr << "Cannot accept: automaton is not valid" << std::endl;
        return false;
    }
    
    std::set<int> currentStates = {initialState};
    
    for (char c : input) {
        if (sigma.find(c) == sigma.end()) {
            return false;
        }
        
        // compute the next set of states
        std::set<int> nextStates;
        for (int state : currentStates) {
            auto it = transitions.find({state, c});
            if (it != transitions.end()) {
                nextStates.insert(it->second.begin(), it->second.end());
            }
        }
        
        currentStates = nextStates;
        
        if (currentStates.empty()) {
            return false;
        }
    }
    
    // check if any of the current states is a final state
    for (int state : currentStates) {
        if (finalStates.find(state) != finalStates.end()) {
            return true;
        }
    }
    
    return false;
}

void NFA::printDetails() const {
    std::cout << *this;
}

std::ostream& operator<<(std::ostream& os, const NFA& nfa) {
    os << "States: ";
    for (int state : nfa.states) {
        os << state << " ";
    }
    os << "\n";
    
    os << "Alphabet: ";
    for (char symbol : nfa.sigma) {
        os << symbol << " ";
    }
    os << "\n";
    
    os << "Transitions:\n";
    for (const auto& [transition, toStates] : nfa.transitions) {
        int fromState = transition.first;
        char symbol = transition.second;
        
        os << "  " << fromState << " -- " << symbol << " --> ";
        for (int toState : toStates) {
            os << toState << " ";
        }
        os << "\n";
    }
    
    os << "Initial state: " << nfa.initialState << "\n";
    
    os << "Final states: ";
    for (int state : nfa.finalStates) {
        os << state << " ";
    }
    os << "\n";
    
    os << "Automaton is " << (nfa.isValid ? "valid" : "invalid") << "\n";
    
    return os;
} 