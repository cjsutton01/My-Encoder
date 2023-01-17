#include "MachineAutomaton.h"

//#include "ColonAutomaton.h"

void MachineAutomaton::S0(const std::string& input) {
    //
    if (input[index] == checkToken) {
        inputRead = 1;
    }
    else {
        Serr();
    }
}