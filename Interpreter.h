//
// Created by Cole Sutton on 10/31/22.
//

#ifndef CS236PROJECT3_REAL__INTERPRETER_H
#define CS236PROJECT3_REAL__INTERPRETER_H

#include "DatalogProgram.h"
#include "Database.h"
#include "Relation.h"
#include <vector>

class Interpreter {
private:
    DatalogProgram myProgram;
    Database database;
    bool tuplesAdded;
    int iterationCounter;


public:
    Interpreter(DatalogProgram program){
        this->myProgram = program;
    }
    void runInterpreter();
    void interpretSchemes();
    void interpretFacts();
    void interpretRules();
    bool interpretSingleRule(Rule* rule);
    void interpretQueries();



};

#endif //CS236PROJECT3_REAL__INTERPRETER_H
