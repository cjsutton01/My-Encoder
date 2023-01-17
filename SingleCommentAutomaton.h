//
// Created by Cole Sutton on 9/22/22.
//

#ifndef CS236PROJECT1_SINGLECOMMENTAUTOMATON_H
#define CS236PROJECT1_SINGLECOMMENTAUTOMATON_H

#include "Automaton.h"

class SingleCommentAutomaton : public Automaton
{
private:
    void S1(const std::string& input);
    void S2(const std::string& input);

public:
    SingleCommentAutomaton() : Automaton(TokenType::COMMENT) {}  // Call the base constructor

    void S0(const std::string& input) override;
};

#endif //CS236PROJECT1_SINGLECOMMENTAUTOMATON_H
