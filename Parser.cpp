#include "Parser.h"
#include "Predicate.h"
#include <iostream>
#include <vector>

Parser::~Parser() {

}

void Parser::parse() {
    for( int i = 0; i < (int)tokens.size(); i++) {
        if(tokens.at(i)->getToken() == TokenType::COMMENT) {
            tokens.erase(tokens.begin() + i, tokens.begin() + i + 1);
            i--;
        }
    }
    try {
        datalogProgramParser();
        //program.setDomain();
        //program.DatalogToString();
    }
    catch(std::string &badToken) {
        std::cout << "Failure!" << std::endl;
        std::cout << "  " << badToken << std::endl;
        exit(1);
    }

}
void Parser::datalogProgramParser() {
    matchToken(TokenType::SCHEMES);
    matchToken(TokenType::COLON);
    schemeParser();
    schemeListParser();
    matchToken(TokenType::FACTS);
    matchToken(TokenType::COLON);
    factListParser();
    matchToken(TokenType::RULES);
    matchToken(TokenType::COLON);
    ruleListParser();
    matchToken(TokenType::QUERIES);
    matchToken(TokenType::COLON);
    queryParser();
    queryListParser();
    matchToken(TokenType::EOF_TYPE);
}

//should be completed
void Parser::schemeParser() {
    Predicate *schemesPred = new Predicate();
    schemesPred->setId(matchToken(TokenType::ID));
    matchToken(TokenType::LEFT_PAREN);
    schemesPred->addParameter(matchToken(TokenType::ID));
    schemeIDListParser(schemesPred);
    matchToken(TokenType::RIGHT_PAREN);
    program.addScheme(schemesPred);
    //delete schemesPred;
}

void Parser::schemeListParser() {
    while(tokens[myIndex]->getToken() != TokenType::FACTS) {
        schemeParser();
        schemeListParser();
    }
}

void Parser::factListParser() {
    while(tokens[myIndex]->getToken() != TokenType::RULES) {
        factParser();
        factListParser();
    }
}

//fix addparameter
void Parser::factParser() {
    Predicate *factsPred = new Predicate();
    factsPred->setId(matchToken(TokenType::ID));
    matchToken(TokenType::LEFT_PAREN);
    factsPred->addParameter(matchToken(TokenType::STRING));
    stringListParser(factsPred);
    matchToken(TokenType::RIGHT_PAREN);
    matchToken(TokenType::PERIOD);
    program.addFact(factsPred);
}

void Parser::ruleListParser() {
    while(tokens[myIndex]->getToken() != TokenType::QUERIES) {
        ruleParser();
        ruleListParser();
    }
}

//need to add to program
void Parser::ruleParser() {
    Rule *rulesPred = new Rule();
    headPredicateParser(rulesPred);
    matchToken(TokenType::COLON_DASH);

    rulePredicateParser(rulesPred);
    rulePredicateListParser(rulesPred);
    matchToken(TokenType::PERIOD);
    program.addRule(rulesPred);
}


void Parser::queryParser() {
    Predicate *queriesPred = new Predicate();
    queryPredicateParser(queriesPred);
    matchToken(TokenType::Q_MARK);
    program.addQuery(queriesPred);
}

void Parser::queryListParser() {
    while(tokens[myIndex]->getToken() != TokenType::EOF_TYPE) {
        queryParser();
        queryListParser();
    }
}

void Parser::headPredicateParser(Rule *rulesPred) {
    rulesPred->setHeadID(matchToken(TokenType::ID));
    matchToken(TokenType::LEFT_PAREN);
    rulesPred->setHeadParam(matchToken(TokenType::ID));
    ruleIDListParser(rulesPred);
    matchToken(TokenType::RIGHT_PAREN);
}

void Parser::rulePredicateParser(Rule *rulesPred) {
    Predicate *ruleBody = new Predicate();
    ruleBody->setId(matchToken(TokenType::ID));
    matchToken(TokenType::LEFT_PAREN);
    ruleParameterParser(ruleBody);
    ruleParameterListParser(ruleBody);
    matchToken(TokenType::RIGHT_PAREN);
    rulesPred->addBodyPredicate(ruleBody);
}

void Parser::queryPredicateParser(Predicate *queriesPred) {
    queriesPred->setId(matchToken(TokenType::ID));
    matchToken(TokenType::LEFT_PAREN);
    queryParameterParser(queriesPred);
    queryParameterListParser(queriesPred);
    matchToken(TokenType::RIGHT_PAREN);
    //program.addQuery(queriesPred);
}

//rule
void Parser::rulePredicateListParser(Rule *rulesPred) {
    while(tokens[myIndex]->getToken() != TokenType::PERIOD) {
        matchToken(TokenType::COMMA);
        rulePredicateParser(rulesPred);
        rulePredicateListParser(rulesPred);
    }
}
//query
void Parser::queryPredicateListParser(Predicate *queriesPred) {
    while(tokens[myIndex]->getToken() != TokenType::PERIOD) {
        matchToken(TokenType::COMMA);
        queryPredicateParser(queriesPred);
        queryPredicateListParser(queriesPred);
    }
}
//rule
void Parser::ruleParameterListParser(Predicate *ruleBody) {
    while(tokens[myIndex]->getToken() != TokenType::RIGHT_PAREN) {
        matchToken(TokenType::COMMA);
        ruleParameterParser(ruleBody);
        ruleParameterListParser(ruleBody);
    }
}
//query
void Parser::queryParameterListParser(Predicate *queriesPred) {
    while(tokens[myIndex]->getToken() != TokenType::RIGHT_PAREN) {
        matchToken(TokenType::COMMA);
        queryParameterParser(queriesPred);
        queryParameterListParser(queriesPred);
    }
}

void Parser::stringListParser(Predicate *factsPred) {
    while(tokens[myIndex]->getToken() != TokenType::RIGHT_PAREN) {
        matchToken(TokenType::COMMA);
        factsPred->addParameter(matchToken(TokenType::STRING));
        stringListParser(factsPred);
    }
}
//schemeidList
void Parser::schemeIDListParser(Predicate *schemesPred) {
    while (tokens[myIndex]->getToken() != TokenType::RIGHT_PAREN) {
        matchToken(TokenType::COMMA);
        schemesPred->addParameter(matchToken(TokenType::ID));
        schemeIDListParser(schemesPred);
    }
}
//rule to head predicateIdList
void Parser::ruleIDListParser(Rule *rulesPred) {
    while (tokens[myIndex]->getToken() != TokenType::RIGHT_PAREN) {
        matchToken(TokenType::COMMA);
        rulesPred->setHeadParam(matchToken(TokenType::ID));
        ruleIDListParser(rulesPred);
    }
}
//rule
//fix add parameter
void Parser::ruleParameterParser(Predicate *myBody) {
    if (tokens[myIndex]->getToken() == TokenType::STRING) {
        myBody->addParameter(matchToken(TokenType::STRING));
    } else {
        myBody->addParameter(matchToken(TokenType::ID));
    }
}
//query
//fix add parameter
void Parser::queryParameterParser(Predicate *queriesPred) {
    if (tokens[myIndex]->getToken() == TokenType::STRING) {
        queriesPred->addParameter(matchToken(TokenType::STRING));
    } else {
        queriesPred->addParameter(matchToken(TokenType::ID));
    }
}


std::string Parser::matchToken(TokenType myToken) {
    std::string myValue = tokens[myIndex]->getDesc();
    if (tokens[myIndex]->getToken() == myToken) {
        myIndex++;
        return myValue;
    } else {
        std::string badValue = tokens[myIndex]->toString();
        throw badValue;
    }
}

const DatalogProgram Parser::getProgram() const {
    return program;
}
