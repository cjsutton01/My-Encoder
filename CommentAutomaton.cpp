#include "CommentAutomaton.h"
#include <cctype>

void CommentAutomaton::S0(const std::string& input) {
    if (input[index] == '#') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void CommentAutomaton::S1(const std::string& input) {
    if (input[index] == '|') {
        inputRead++;
        index++;
        S2(input);
    }
    else {
        Serr();
    }
}

void CommentAutomaton::S2(const std::string& input) {
    if (input[index] == '|') {
        inputRead++;
        index++;
        S3(input);
    }
    else if (index == (int)input.size()){
        type = TokenType::UNDEFINED;
        //Serr();
        return;
    }
    else {
        if(input[index] == '\n'){
            newLines++;
        }
        inputRead++;
        index++;
        S2(input);
    }
}

void CommentAutomaton::S3(const std::string& input) {
    if (input[index] == '#') {
        inputRead++;
        index++;
        return;
    }
    else if(index == (int)input.size()){
        type = TokenType::UNDEFINED;
        //Serr();
        return;
    }
    else {
        if(input[index] == '\n'){
            newLines++;
        }
        inputRead++;
        index++;
        S2(input);
    }
}

