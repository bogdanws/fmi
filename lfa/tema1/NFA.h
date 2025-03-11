#ifndef NFA_H
#define NFA_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <queue>

class NFA {
protected:
    std::set<int> states;
    std::set<char> sigma; // alphabet
    // Transitions: state x symbol -> set of states
    std::map<std::pair<int, char>, std::set<int>> transitions;
    int initialState;
    std::set<int> finalStates;

    bool isValid;

public:
    NFA();
    
    bool readFromFile(const std::string& filename);
    
    virtual bool validate();
    
    bool accepts(const std::string& input);
    
    void printDetails() const;

private:
    // Helper methods for validation
    bool validateStates() const;
    bool validateSigma() const;
    bool validateTransitions() const;
    bool validateInitialState() const;
    bool validateFinalStates() const;
};

#endif // NFA_H 