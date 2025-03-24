#ifndef DFA_H
#define DFA_H

#include "NFA.h"

class DFA : public NFA {
public:
    bool validate() const override;
};

#endif