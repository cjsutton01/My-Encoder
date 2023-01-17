//
// Created by Cole Sutton on 11/1/22.
//
#include "Interpreter.h"
#include "Graph.h"
#include <vector>

using namespace std;

void Interpreter::runInterpreter() {
    interpretSchemes();
    interpretFacts();
    interpretRules();
    interpretQueries();
}

void Interpreter::interpretSchemes() {
    for (unsigned int i = 0; i < myProgram.getSchemes().size(); i++) {
        vector<string> columnNames;
        string name = myProgram.getSchemes().at(i)->getId(); //add name
        columnNames = (myProgram.getSchemes().at(i)->getParams()); //get vector of parameters(column names)
        Header myHeader(columnNames);
        Relation emptyRelation = Relation(name, myHeader);
        database.addRelation(emptyRelation);
    }
}


void Interpreter::interpretFacts() {
    for (unsigned int i = 0; i < myProgram.getFacts().size(); i++) {
        string tableName = myProgram.getFacts().at(i)->getId();
        Relation *newRelation = database.getRelationReference(tableName);
        newRelation->addTuple(Tuple(myProgram.getFacts().at(i)->getParams()));
    }
}


void Interpreter::interpretRules() {
    vector<Rule *> rules = myProgram.getRules();
    Graph myGraph;
    cout << "Dependency Graph" << endl;
    myGraph.runGraph(rules);
    myGraph.printDependencyGraph();
    cout << endl;

    cout << "Rule Evaluation" << endl;

    vector<set<int>> myListOfRules = myGraph.getSccs();


    tuplesAdded = false;

    for (auto list: myListOfRules) {
        if (list.size() != 0) {
            cout << "SCC: ";
            unsigned int i = 0;
            for (auto eachSCC: list) {
                i++;
                cout << "R" << eachSCC;
                if (i != list.size()) {
                    cout << ",";
                }
            }
            cout << endl;
            iterationCounter = 0;
            bool selfLoop = false;
            do {
                tuplesAdded = false;

                for (auto eachSCC: list) {
                    for(unsigned int i = 0; i < rules.at(eachSCC)->getBody().size(); i++){
                        if(rules.at(eachSCC)->getBody().at(i)->getId() == rules.at(eachSCC)->getHeadID()){
                            selfLoop = true;
                        }
//                        else {
//                            selfLoop = false;
//                        }
                    }
                    if(!selfLoop && list.size() == 1){
                        interpretSingleRule(rules.at(eachSCC));
                        tuplesAdded = false;
                    }
                    else {
                        interpretSingleRule(rules.at(eachSCC));
                    }
                }
                iterationCounter++;
            } while (tuplesAdded);

            cout << iterationCounter << " passes: ";
            unsigned int j = 0;
            for (auto eachSCC: list) {
                j++;
                cout << "R" << eachSCC;
                if (j != list.size()) {
                    cout << ",";
                }
            }
            //cout << endl << endl;
        }
        cout << endl;
    }
    cout << endl;
    //cout << endl << "Schemes populated after " << iterationCounter << " passes through the Rules." << endl << endl;
}

bool Interpreter::interpretSingleRule(Rule *rule) {
    //tuplesAdded = false;
    vector<Predicate *> bodyPredicates = rule->getBody();
    vector<Relation> queriedRelations;
    for (unsigned int i = 0; i < bodyPredicates.size(); i++) {
        map<string, int> seenBefore;
        vector<int> projectIndex;
        vector<string> renameValues;
        string tableName = bodyPredicates.at(i)->getId();
        Relation r = database.getRelationCopy(tableName);
        vector<string> queryParams = bodyPredicates.at(i)->getParams();
        for (unsigned int j = 0; j < queryParams.size(); j++) {
            if (queryParams[j].at(0) == '\'') {
                r = r.select1(j, queryParams[j]);
            } else if (seenBefore.count(queryParams[j]) == 1) {
                r = r.select2(j, seenBefore[queryParams[j]]);
            } else {
                seenBefore.insert({queryParams[j], j});
                projectIndex.push_back(j);
                renameValues.push_back(queryParams[j]);
            }
        }
        r = r.project(projectIndex);

        r = r.rename(renameValues);

        queriedRelations.push_back(r);
    }


    Relation joinedRelation = queriedRelations.at(0);
    for (unsigned int i = 1; i < queriedRelations.size(); i++) {
        joinedRelation.join(queriedRelations.at(i));
    }

    vector<int> columnIndexes = joinedRelation.convertStringToInt(rule);

    joinedRelation = joinedRelation.project(columnIndexes);

    joinedRelation = joinedRelation.rename(rule->getHeadParams());


    string tableName = rule->getHeadID();
    Relation *newRelation = database.getRelationReference(tableName);

    rule->RuleToString();
    cout << "." << endl;
    for (auto i: joinedRelation.getTuples()) {
        if (newRelation->addTuple(i)) {
            cout << "  ";
            i.tuplePrint(newRelation->getColumnNames());
            cout << endl;
            tuplesAdded = true;

        }
    }
    if (tuplesAdded) {
        //iterationCounter++;
        return true;
    } else {
        return false;
    }
}


void Interpreter::interpretQueries() {
    vector<Predicate *> predicateQueries = myProgram.getQueries();
    cout << "Query Evaluation" << endl;
    for (unsigned int i = 0; i < predicateQueries.size(); i++) {

        myProgram.getQueries().at(i)->PredicateToString();

        cout << "? ";

        map<string, int> seenBefore;
        vector<int> projectIndex;
        vector<string> renameValues;
        string tableName = predicateQueries.at(i)->getId();
        Relation r = database.getRelationCopy(tableName);
        vector<string> queryParams = predicateQueries.at(i)->getParams();
        for (unsigned int j = 0; j < queryParams.size(); j++) {
            if (queryParams[j].at(0) == '\'') {
                r = r.select1(j, queryParams[j]);
            } else if (seenBefore.count(queryParams[j]) == 1) {
                r = r.select2(j, seenBefore[queryParams[j]]);
            } else {
                seenBefore.insert({queryParams[j], j});
                projectIndex.push_back(j);
                renameValues.push_back(queryParams[j]);
            }
        }
        r = r.project(projectIndex);

        r = r.rename(renameValues);

        if (r.tupleNum() == 0) {
            cout << "No" << endl;
        } else {
            cout << "Yes(" << r.tupleNum() << ")" << endl;
            r.relationToString();
        }


    }
}








