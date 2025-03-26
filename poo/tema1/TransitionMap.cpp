#include "TransitionMap.h"

void TransitionMap::addTransition(int fromState, char symbol, int toState) {
    transitions[{fromState, symbol}].insert(toState);
}

void TransitionMap::addTransition(int fromState, char symbol, const std::set<int>& toStates) {
    transitions[{fromState, symbol}] = toStates;
}

std::set<int> TransitionMap::getTransitions(int state, char symbol) const {
    auto it = transitions.find({state, symbol});
    if (it != transitions.end()) {
        return it->second;
    }
    return std::set<int>();
}

bool TransitionMap::hasTransition(int state, char symbol) const {
    return transitions.find({state, symbol}) != transitions.end();
}

const std::map<std::pair<int, char>, std::set<int>>& TransitionMap::getAllTransitions() const {
    return transitions;
}

void TransitionMap::clear() {
    transitions.clear();
} 