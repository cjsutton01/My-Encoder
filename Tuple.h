//
// Created by Cole Sutton on 10/31/22.
//

#ifndef CS236PROJECT1_TUPLE_H
#define CS236PROJECT1_TUPLE_H
#include <vector>
#include "Header.h"

using namespace std;

class Tuple {
private:
    std::vector<std::string> rowValues;
public:
    Tuple() = default;
    Tuple(std::vector<std::string> rowValues){
        this->rowValues = rowValues;
    }

    const std::vector<std::string> &getRowValues() const {
        return rowValues;
    }

    void addValueToTuple(std::string newValue){
        rowValues.push_back(newValue);
    }

    bool operator<(const Tuple &rhs) const {
        return rowValues < rhs.rowValues;
    }

    void tuplePrint(vector<string> columnNames) const{
        for (size_t i = 0; i < columnNames.size(); i++) {
            cout << columnNames.at(i) << "=" << getRowValues().at(i);
            if(i != columnNames.size() - 1) {
                cout << ", ";
            }
        }
    };

};

#endif //CS236PROJECT1_TUPLE_H
