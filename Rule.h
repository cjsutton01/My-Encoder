//
// Created by Cole Sutton on 10/4/22.
//

#ifndef CS236PROJECT1_RULE_H
#define CS236PROJECT1_RULE_H

#include <vector>
#include <iostream>
#include "Predicate.h"
using namespace std;
class Rule {
private:
    Predicate head;
    std::vector<Predicate*> body;
public:
    void setHeadID(std::string myID) {
        head.setId(myID);
    }
    void setHeadParam(std::string myParam){
        head.addParameter(myParam);
    }
    void addBodyPredicate(Predicate *myPredicate) {
        body.push_back(myPredicate);
    }

    const std::string &getHeadID() const {
        return head.getId();
    }

//    const Predicate &getWholeHead() const {
//        return head;
//    }


    const vector<Predicate *> &getBody() const {
        return body;
    }

    const vector<string> getHeadParams(/*pass in index*/) const {
        vector<string> params = head.getParams();
        return params;
    }

    void RuleToString() {
        head.PredicateToString();
        cout << " :- ";
        body.at(0)->PredicateToString();
        for(size_t i = 1; i < body.size(); i++) {
            cout << ",";
            body.at(i)->PredicateToString();
        }


    }


};

#endif //CS236PROJECT1_RULE_H
