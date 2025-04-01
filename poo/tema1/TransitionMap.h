#ifndef TRANSITION_MAP_H
#define TRANSITION_MAP_H

#include <map>
#include <set>
#include <utility>

class TransitionMap {
private:
    std::map<std::pair<int, char>, std::set<int>> transitions;

public:
    TransitionMap() = default;
    TransitionMap(const TransitionMap& other) = default;
    TransitionMap& operator=(const TransitionMap& other) = default;
    ~TransitionMap() = default;

    // Add a transition
    void addTransition(int fromState, char symbol, int toState);
    
    // Add multiple transitions to the same state
    void addTransition(int fromState, char symbol, const std::set<int>& toStates);
    
    // Get transitions for a state and symbol
    std::set<int> getTransitions(int state, char symbol) const;
    
    // Check if a transition exists
    bool hasTransition(int state, char symbol) const;
    
    // Get all transitions
    const std::map<std::pair<int, char>, std::set<int>>& getAllTransitions() const;
    
    // Clear all transitions
    void clear();
};

#endif 