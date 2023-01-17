//
// Created by Cole Sutton on 10/31/22.
//

#ifndef CS236PROJECT1_RELATION_H
#define CS236PROJECT1_RELATION_H

#include <set>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include "Header.h"
#include "Tuple.h"
#include "Rule.h"
#include "DatalogProgram.h"

using namespace std;

class Relation {
private:
    string name;
    Header columnNames;
    Header schemaColumnNames;
    set<Tuple> tuples;
    map<int, int> myCommonIndexes;
    DatalogProgram myProgram;

public:
    Relation() = default;
    Relation(string name, Header columnNames) {
        this->name = name;
        this->columnNames = columnNames;
    }

    string getName() {return name;}

    void setColumnNames(const Header &columnNames) {
        Relation::columnNames = columnNames;
    }

    bool addTuple(Tuple newTuple) {
        //tuples.insert(newTuple);
        return tuples.insert(newTuple).second;
    }


    void setTuples(const set<Tuple> &tuples) {Relation::tuples = tuples;};

    int tupleNum() {
        return tuples.size();
    }

    const vector<string> &getColumnNames() const {
        return columnNames.getColumnNames();
    }

    const set<Tuple> &getTuples() const {
        return tuples;
    }

    Relation select1 (int index, string value);

    Relation select2 (int index1, int index2);

    Relation project (vector<int> columnsToProject);

    Relation rename (vector<string> columnsToRename);

    Relation join(Relation myRelation);

    void combineHeaders(Relation myRelation, map<int, int> commonIndexes);
    bool isJoinable(Tuple tuple1, Tuple tuple2, map<int, int> commonIndexes);
    Tuple combineTuples(Tuple tuple1, Tuple tuple2, map<int, int> commonIndexes);

    vector<int> convertStringToInt(Rule *myRule);

    void relationToString(){
        for(Tuple tuple: tuples) {
            if(columnNames.getColumnNames().size() != 0) {
                cout << "  ";
            }
            for (size_t i = 0; i < columnNames.getColumnNames().size(); i++) {
                cout << columnNames.getColumnNames().at(i) << "=" << tuple.getRowValues().at(i);
                if(i != columnNames.getColumnNames().size() - 1) {
                    cout << ", ";
                }
            }
            if(columnNames.getColumnNames().size() != 0) {
                cout << endl;
            }
        }
    }

    void joinedRelationToString(){
        for(Tuple tuple: tuples) {
            cout << "  ";
            for (size_t i = 0; i < columnNames.getColumnNames().size(); i++) {
                cout << columnNames.getColumnNames().at(i) << "=" << tuple.getRowValues().at(i);
                if(i != columnNames.getColumnNames().size() - 1) {
                    cout << ", ";
                }
            }
            if(columnNames.getColumnNames().size() != 0) {
                cout << endl;
            }
        }
    }




};

#endif //CS236PROJECT1_RELATION_H
