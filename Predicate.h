//
// Created by Cole Sutton on 10/4/22.
//

#ifndef CS236PROJECT1_PREDICATE_H
#define CS236PROJECT1_PREDICATE_H

#include <utility>
#include <iostream>
#include <vector>
#include "Parameter.h"

class Predicate {
private:
    std::string ID;
    std::vector<Parameter> param;
public:
//    std::string getID() {return ID;}
//    std::vector<Parameter> getParam() {return param;}

    void setId(std::string id) {
        ID = std::move(id);
    }
    void addParameter(std::string myParameter) {
        Parameter parameter(myParameter);
        param.push_back(parameter); // param size not reseting for every new predicate object, and param is empty
    }

    const std::string &getId() const {
        return ID;
    }

    const std::vector<std::string> getParams() const {
        std::vector<std::string> myParams;
        for(unsigned int i = 0; i < param.size(); i++) {
            myParams.push_back(param.at(i).getMyParam());
        }
        return myParams;
    }

    const int getParamsSize() const {
        return param.size();
    }

    void PredicateToString() {
        std::cout << ID << "(" << param.at(0).getMyParam();
        for(size_t i = 1; i < param.size(); i++){
            std::cout << "," << param.at(i).getMyParam();
        }
        std::cout << ")";
    }




};

#endif //CS236PROJECT1_PREDICATE_H
