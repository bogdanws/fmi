#ifndef DFA_H
#define DFA_H

#include "NFA.h"

class DFA : public NFA {
public:
    DFA() = default;
    DFA(const DFA& other);
    DFA& operator=(const DFA& other);
    ~DFA() override = default;

    bool validate() const override;
};

#endif