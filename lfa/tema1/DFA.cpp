#include "DFA.h"

bool DFA::validate() {
    // First, validate as an NFA
    if (!NFA::validate()) {
        return false;
    }
    
    // Additional DFA constraint: at most one transition for each state-symbol pair
    for (const auto& [transition, toStates] : transitions) {
        if (toStates.size() > 1) {
            std::cerr << "Invalid DFA: state " << transition.first 
                      << " has multiple transitions on symbol '" << transition.second << "'" << std::endl;
            return false;
        }
    }
    
    return true;
} 