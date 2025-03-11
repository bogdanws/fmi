#ifndef DFA_H
#define DFA_H

#include "NFA.h"

class DFA : public NFA {
public:
    // Override validate to add the DFA-specific constraint (at most one transition for each state-symbol pair)
    bool validate() override;
};

#endif // DFA_H 