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
    std::set<char> sigma;
    std::map<std::pair<int, char>, std::set<int>> transitions;
    int initialState;
    std::set<int> finalStates;

    bool isValid;

public:
    NFA();
    NFA(const NFA& other);
    NFA& operator=(const NFA& other);
    virtual ~NFA() = default;
    
    bool readFromFile(const std::string& filename);
    
    virtual bool validate() const;
    
    bool accepts(const std::string& input);
    
    void printDetails() const;

private:
    bool validateStates() const;
    bool validateSigma() const;
    bool validateTransitions() const;
    bool validateInitialState() const;
    bool validateFinalStates() const;
};

#endif