//
// Created by Cole Sutton on 9/20/22.
//

#ifndef CS236PROJECT1_STRING_H
#define CS236PROJECT1_STRING_H

#include "Automaton.h"

class StringAutomaton : public Automaton
{
private:
    void S1(const std::string& input);
    void S2(const std::string& input);

public:
    StringAutomaton() : Automaton(TokenType::STRING) {}  // Call the base constructor

    void S0(const std::string& input) override;
};

#endif //CS236PROJECT1_STRING_H
