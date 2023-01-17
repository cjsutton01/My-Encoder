//
// Created by Cole Sutton on 9/21/22.
//

#ifndef CS236PROJECT1_IDAUTOMATON_H
#define CS236PROJECT1_IDAUTOMATON_H

#include "Automaton.h"

class IDAutomaton : public Automaton
{
private:
    void S1(const std::string& input);
public:
    IDAutomaton() : Automaton(TokenType::ID) {}  // Call the base constructor

    void S0(const std::string& input) override;
};


#endif //CS236PROJECT1_IDAUTOMATON_H
