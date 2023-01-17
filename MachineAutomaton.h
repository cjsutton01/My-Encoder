//
// Created by Cole Sutton on 9/20/22.
//

#ifndef MACHINEAUTOMATON_H
#define MACHINEAUTOMATON_H

#include <string>
#include "Automaton.h"

using namespace std;

class MachineAutomaton : public Automaton
{
private:
    char checkToken;
public:
    MachineAutomaton(const char& check, TokenType type) {
        this->checkToken = check;
        this->type = type;
    }  // Call the base constructor

    void S0(const string& input) override;
};

#endif // COLONAUTOMATON_H



