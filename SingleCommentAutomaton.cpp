#include "SingleCommentAutomaton.h"
#include <cctype>

void SingleCommentAutomaton::S0(const std::string& input) {
    if (input[index] == '#') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void SingleCommentAutomaton::S1(const std::string& input) {
    if (input[index] == '|') {
        Serr();
    }
    else{
        inputRead++;
        index++;
        S2(input);
    }
}
void SingleCommentAutomaton::S2(const std::string& input) {
    if (index != (int)input.size() && input[index] != '\n') {
        inputRead++;
        index++;
        S2(input);
    }
}




