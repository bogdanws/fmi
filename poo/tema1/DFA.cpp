#include "DFA.h"

DFA::DFA(const DFA& other) : NFA(other) {
}

DFA& DFA::operator=(const DFA& other) {
    if (this != &other) {
        NFA::operator=(other);
    }
    return *this;
}

bool DFA::validate() const {
    // validate as NFA
    if (!NFA::validate()) {
        return false;
    }
    
    // additional constraint: at most one transition for each state-symbol
    for (const auto& [transition, toStates] : transitions) {
        if (toStates.size() > 1) {
            std::cerr << "Invalid DFA: state " << transition.first << " has multiple transitions on symbol '" << transition.second << "'" << std::endl;
            return false;
        }
    }
    
    return true;
} 