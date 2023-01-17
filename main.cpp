#include <fstream>
#include <string>
#include <iostream>
#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"

using namespace std;

int main(int argc, char** argv) {

    ifstream inputFile(argv[1]);
    string myFile;
    myFile = string((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());

    //cout << myFile;

    Lexer *lexer = new Lexer();
    lexer->Run(myFile);

    Parser *parser = new Parser(lexer->getTokens());
    parser->parse();

    Interpreter *interpreter = new Interpreter(parser->getProgram());
    interpreter->runInterpreter();

    //

    delete lexer;
    delete parser;
    delete interpreter;



    return 0;
}