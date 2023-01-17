//
// Created by Cole Sutton on 10/3/22.
//

#ifndef CS236PROJECT1_PARSER_H
#define CS236PROJECT1_PARSER_H
#include <vector>
#include "Token.h"
#include "DatalogProgram.h"

class Parser{
private:
    DatalogProgram program;
    std::vector<Token*> tokens;
    int myIndex = 0;
public:
    Parser(){};
    Parser(std::vector<Token*> myTokens){
        this->tokens = myTokens;
    };

    ~Parser();

    void parse();

    void datalogProgramParser();

    std::string matchToken(TokenType myToken);

    void schemeParser();

    void schemeListParser();

    void factListParser();

    void factParser();

    void ruleListParser();

    void ruleParser();

    void queryParser();

    void queryListParser();

    void headPredicateParser(Rule *rulesPred);

    void rulePredicateParser(Rule *rulesPred);
    void queryPredicateParser(Predicate *queriesPred);

    void rulePredicateListParser(Rule *rulesPred);
    void queryPredicateListParser(Predicate *queriesPred);

    void ruleParameterListParser(Predicate *ruleBody);
    void queryParameterListParser(Predicate *queriesPred);

    void stringListParser(Predicate *factsPred);

    void schemeIDListParser(Predicate *schemesPred);
    void ruleIDListParser(Rule *rulesPred);

    void ruleParameterParser(Predicate *ruleBody);
    void queryParameterParser(Predicate *queriesPred);

    const DatalogProgram getProgram() const;


};

#endif //CS236PROJECT1_PARSER_H
