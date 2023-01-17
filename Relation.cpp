#include "Relation.h"
#include <map>


Relation Relation::select1(int index, string value) {
    Relation newRelation(value, Header());
    for (Tuple tuple: tuples) {
        if (tuple.getRowValues()[index] == value) {
            newRelation.addTuple(tuple);
        }
    }
    return newRelation;
}

Relation Relation::select2(int index1, int index2) {
    Relation newRelation;
    for (Tuple tuple: tuples) {
        if (tuple.getRowValues()[index1] == tuple.getRowValues()[index2]) {
            newRelation.addTuple(tuple);
        }
    }
    return newRelation;
}

Relation Relation::project(vector<int> columnsToProject) {
    vector<string> colNames = columnNames.getColumnNames();
    Relation newRelation(name, Header(colNames));
    for (Tuple newTuple: tuples) {
        vector<string> values;
        for (int index: columnsToProject) {
            values.push_back(newTuple.getRowValues()[index]);
        }
        newRelation.addTuple(Tuple(values));
    }
    return newRelation;
}

Relation Relation::rename(vector<string> columnsToRename) {
    Relation newRelation(name, Header(columnsToRename));
    newRelation.setTuples(tuples);
    return newRelation;
}

Relation Relation::join(Relation relationToJoin) {
    map<int, int> commonIndexes;

    combineHeaders(relationToJoin, commonIndexes);

    set<Tuple> newTuples;
    Relation newRelation(name, columnNames);
    newRelation.setTuples(newTuples);

    for (auto i: relationToJoin.getTuples()) {
        for (auto j: tuples) {
            bool canJoin = isJoinable(i, j, commonIndexes);
            if (canJoin) {
                newRelation.addTuple(combineTuples(i, j, commonIndexes));
            }
            if (myCommonIndexes.empty()) {
                newRelation.addTuple(combineTuples(i, j, commonIndexes));
            }
        }
    }

    tuples = newRelation.getTuples();
    myCommonIndexes.clear();
    return newRelation;
}


vector<int> Relation::convertStringToInt(Rule *myRule) {

    vector<string> headBodyParam = myRule->getHeadParams();

    vector<int> convertedIndexes;

    for (unsigned int i = 0; i < headBodyParam.size(); i++) {
        for (unsigned int j = 0; j < columnNames.getColumnNames().size(); j++) {
            if (headBodyParam.at(i) == columnNames.getColumnNames().at(j)) {
                convertedIndexes.push_back(j);
            }
        }
    }

    return convertedIndexes;
}


void Relation::combineHeaders(Relation relationToJoin, map<int, int> commonIndexes) {
    vector<string> relationToJoinHeader = relationToJoin.getColumnNames();
    vector<string> currentHeader = columnNames.getColumnNames();
    vector<string> newHeader = columnNames.getColumnNames();


    for (unsigned int i = 0; i < relationToJoinHeader.size(); i++) {
        bool isFound = false;
        for (unsigned int j = 0; j < currentHeader.size(); j++) {
            if (relationToJoinHeader.at(i) == currentHeader.at(j)) {
                isFound = true;
                myCommonIndexes.insert({i, j});
                break;
            }
        }
        if (!isFound) {
            newHeader.push_back(relationToJoinHeader.at(i));
        }
    }

    columnNames = newHeader;
}

bool
Relation::isJoinable(Tuple tuple1, Tuple tuple2, map<int, int> commonIndexes) { // only for relations with common column

    for (auto i: myCommonIndexes) {
        if (tuple1.getRowValues().at(i.first) != tuple2.getRowValues().at(i.second)) {
            return false;
        }
    }
    return true;

}

Tuple Relation::combineTuples(Tuple tuple1, Tuple tuple2, map<int, int> commonIndexes) {

    //loop over tuple1
    //loop over commonIndex
    //check if i = commonIndex
    //if is in, skip
    //if not add tuple1.at(i) to tuple2


    if (!myCommonIndexes.empty()) {
        for (unsigned int i = 0; i < tuple1.getRowValues().size(); i++) {
            bool isAdded = false;
            for (auto j: myCommonIndexes) {
                if ((int)i == j.first) {
                    isAdded = true;
                }
            }
            if (isAdded == false) {
                tuple2.addValueToTuple(tuple1.getRowValues().at(i));
            }
        }
    } else {
        for (unsigned int i = 0; i < tuple1.getRowValues().size(); i++) {
            tuple2.addValueToTuple(tuple1.getRowValues().at(i));
        }
    }
    return tuple2;

}









