//
// Created by Cole Sutton on 10/31/22.
//

#ifndef CS236PROJECT1_DATABASE_H
#define CS236PROJECT1_DATABASE_H

#include "Relation.h"
#include <map>

class Database {
private:
    map<std::string, Relation> relations;

public:
    void addRelation(Relation newRelation) {
        relations.insert({newRelation.getName(), newRelation});
    }
    Relation* getRelationReference (string relationName){
        return &relations.at(relationName);
    };

    Relation getRelationCopy (string relationName) {
        return relations.at(relationName);
    }
    //print relations
    // iterate through the map
    // print out queries

};

#endif //CS236PROJECT1_DATABASE_H
