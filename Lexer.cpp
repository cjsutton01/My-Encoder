#include "Lexer.h"
#include "Token.h"
#include "MachineAutomaton.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "FactsAutomaton.h"
#include "RulesAutomaton.h"
#include "QueriesAutomaton.h"
#include "SchemesAutomaton.h"
#include "IDAutomaton.h"
#include "String.h"
#include "CommentAutomaton.h"
#include "SingleCommentAutomaton.h"

#include <iostream>
#include <cctype>

Lexer::Lexer() {
    automata.push_back(new MachineAutomaton(',', TokenType::COMMA));
    automata.push_back(new MachineAutomaton('.', TokenType::PERIOD));
    automata.push_back(new MachineAutomaton('?', TokenType::Q_MARK));
    automata.push_back(new MachineAutomaton('(', TokenType::LEFT_PAREN));
    automata.push_back(new MachineAutomaton(')', TokenType::RIGHT_PAREN));
    automata.push_back(new MachineAutomaton(':', TokenType::COLON));
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new MachineAutomaton('*', TokenType::MULTIPLY));
    automata.push_back(new MachineAutomaton('+', TokenType::ADD));
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new IDAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new SingleCommentAutomaton());
    automata.push_back(new CommentAutomaton());
    // TODO: Add the other needed automata here
}

Lexer::~Lexer() {
    // TODO: need to clean up the memory in `automata` and `tokens`
}


void Lexer::Run(std::string& input) {
    //int tokenCounter = 0;
    int lineNumber = 1;
    while(!input.empty()) {
        int maxRead = 0;
        Automaton* maxAutomaton = automata[0];
        while(isspace(input[0])){
            if(input[0] == '\n'){
                lineNumber+= 1;
            }
            input = input.substr(1);
        }
        if(input.empty()){
            break;
        }
        for(int i = 0; i < (int)automata.size(); i++) {
            int inputRead = automata[i]->Start(input);
            if (inputRead > maxRead) {
                maxRead = inputRead;
                maxAutomaton = automata[i];
            }
        }
        if (maxRead > 0) {
            Token *newToken = maxAutomaton->CreateToken(input.substr(0, maxRead), lineNumber);
            lineNumber += maxAutomaton->NewLinesRead();
            tokens.push_back(newToken);
        } else {
            maxRead = 1;
            auto *undefToken = new Token(TokenType::UNDEFINED, input.substr(0, maxRead), lineNumber);
            tokens.push_back(undefToken);
        }
        input = input.substr(maxRead);

    }
    auto *eofToken = new Token(TokenType::EOF_TYPE, "", lineNumber);
    tokens.push_back(eofToken);


//    for( int i = 0; i < (int)tokens.size(); i++){
//        cout << tokens.at(i)->toString();
//        tokenCounter += 1;
//        cout << endl;
//    }
//    cout << "Total Tokens = " << tokenCounter << endl;
}
