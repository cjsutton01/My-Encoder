//
// Created by Cole Sutton on 9/20/22.
//

#ifndef CS236PROJECT1_RULESAUTOMATON_H
#define CS236PROJECT1_RULESAUTOMATON_H

#include "Automaton.h"

class RulesAutomaton : public Automaton
{
private:
    void S1(const std::string& input);
    void S2(const std::string& input);
    void S3(const std::string& input);
    void S4(const std::string& input);


public:
    RulesAutomaton() : Automaton(TokenType::RULES) {}  // Call the base constructor

    void S0(const std::string& input) override;
};

#endif //CS236PROJECT1_RULESAUTOMATON_H
