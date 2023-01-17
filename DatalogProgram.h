//
// Created by Cole Sutton on 10/4/22.
//

#ifndef CS236PROJECT1_DATALOGPROGRAM_H
#define CS236PROJECT1_DATALOGPROGRAM_H
#include <vector>
#include <set>

#include "Rule.h"
#include "Parameter.h"
#include "Predicate.h"

using namespace std;

class DatalogProgram {
private:
    std::vector<Rule*> rules;
    std::vector<Predicate*> queries;
    std::vector<Predicate*> facts;
    std::vector<Predicate*> schemes;
    std::set<std::string> domain;
public:
    void addQuery(Predicate *myQuery) {queries.push_back(myQuery);}
    void addFact(Predicate *myFact) {facts.push_back(myFact);}
    void addScheme(Predicate *myScheme) {schemes.push_back(myScheme);}
    void addRule(Rule *myRule) {rules.push_back(myRule);}


    const vector<Predicate *> &getSchemes() const {
        return schemes;
    }

    const vector<Predicate *> &getFacts() const {
        return facts;
    }

    const vector<Rule *> &getRules() const {
        return rules;
    }
    const vector<Rule *> &getRulesBody() const {
        return rules;
    }

    const vector<Predicate *> &getQueries() const {
        return queries;
    }

    void setDomain() {
        std::vector<std::string> domainParams;
        for (size_t i = 0; i < facts.size(); i++) {
            domainParams = facts.at(i)->getParams();
            for (size_t j = 0; j < domainParams.size(); j++) {
                domain.insert(domainParams.at(j));
            }
        }
    }


    void DatalogToString() {
        cout << "Success!" << endl;
        cout << "Schemes(" << to_string(schemes.size()) << "):" << endl;
        for(size_t i = 0; i < schemes.size(); i++){
            cout << "  ";
            schemes.at(i)->PredicateToString();
            cout << endl;
        }

        cout << "Facts(" << to_string(facts.size()) << "):" << endl;
        for(size_t i = 0; i < facts.size(); i++){
            cout << "  ";
            facts.at(i)->PredicateToString();
            cout << "." << endl;
        }

        cout << "Rules(" << to_string(rules.size()) << "):" << endl;
        for(size_t i = 0; i < rules.size(); i++){
            cout << "  ";
            rules.at(i)->RuleToString();
            cout << "." << endl;
        }

        cout << "Queries(" << to_string(queries.size()) << "):" << endl;
        for(size_t i = 0; i < queries.size(); i++){
            cout << "  ";
            queries.at(i)->PredicateToString();
            cout << "?" << endl;
        }
        cout << "Domain(" << to_string(domain.size()) << "):" << endl;
        set<string>::iterator it;
        for (it = domain.begin(); it != domain.end(); ++it) {
            cout << "  " << *it;
            cout << endl;
        }
    }



};

#endif //CS236PROJECT1_DATALOGPROGRAM_H
