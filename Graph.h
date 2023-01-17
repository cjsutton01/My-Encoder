//
// Created by Cole Sutton on 12/6/22.
//

#ifndef CS236PROJECT3_REAL__GRAPH_H
#define CS236PROJECT3_REAL__GRAPH_H

#include "Rule.h"
#include "Predicate.h"
#include <iostream>
#include <set>
#include <map>
#include <vector>

using namespace std;

class Graph {
private:
    vector<Rule *> rules;
    map<int, set<int>> forwardGraph;
    map<int, set<int>> reverseGraph;
    map<int, bool> visitedNodes;
    //vector<bool>
    vector<int> postOrder;
    set<int> output;
    vector<set<int>> sccs;
    bool searchDone;
    // vector bool to store visited int
public:
    
    Graph() = default;
    ~Graph() = default;

    void createDependencyGraph(vector<Rule *> myRules) {
        for (unsigned int i = 0; i < myRules.size(); i++) {
            //initialization
            forwardGraph.insert({i, {}});
            reverseGraph.insert({i, {}});

        }
        for (unsigned int i = 0; i < myRules.size(); i++) {
            int bodySize = myRules[i]->getBody().size();
            for (int j = 0; j < bodySize; j++) {
                for (unsigned int k = 0; k < myRules.size(); k++) {
                    vector<Predicate *> bodyPredicates = myRules[i]->getBody();
                    if (bodyPredicates[j]->getId() == myRules[k]->getHeadID()) {
                        forwardGraph[i].insert(k);
                        reverseGraph[k].insert(i);
                    }
                }
                //for j body predicate
                //for k rule head predicate
                //if body predicate name at j == head predicate name at k
                //forwardGraph[i].insert(k);
                //[k].insert(i);
            }
        }
    };

    void printDependencyGraph() {
        for (auto &elem: forwardGraph) {
            cout << "R" << elem.first << ":";
            unsigned int i = 0;
            for (auto index: elem.second) {
                i++;
                cout << "R" << index;
                if (i != elem.second.size()) {
                    cout << ",";
                }
            }
            cout << endl;
        }
    }


    //find postorder
    void dfsForest() {
        for (unsigned int i = 0; i < visitedNodes.size(); i++){
            visitedNodes.at(i) = false;
        }
        for (auto n: reverseGraph) {
            dfs(n.first, reverseGraph);
        }
    }

    void dfs(int nodeIndex, map<int, set<int>> &currentGraph) {
        if(visitedNodes[nodeIndex]){
            return;
        }
       visitedNodes[nodeIndex] = true;
       for (auto n2 : currentGraph[nodeIndex]){
           if(visitedNodes[n2] == false){
               dfs(n2, currentGraph);
           }
       }
       if(!searchDone) {
           postOrder.push_back(nodeIndex);
       }
       output.insert(nodeIndex);
    }

    void dfsForestReverse(){
        searchDone = true;
        output.clear();
//        for(pair<int, bool>& n: visitedNodes){
//            n.second = false;
//        }
        for (unsigned int i = 0; i < visitedNodes.size(); i++){
            visitedNodes.at(i) = false;
        }

        for(int i = postOrder.size() - 1; i >= 0 ; i--){
            output.clear();
            (dfs(postOrder[i], forwardGraph));
            sccs.push_back(output);
        }
    }

    void printPostorder() {
        cout << "Post Order" << endl;
        for (auto value : postOrder){
            cout << value << endl;
        }
    }

    void printSCC() {
        cout << "SCC:" << endl;
        for( auto scc : sccs) {
            for(auto node : scc){
                cout << node << ", ";
            }
            cout << endl;
        }
    }



    void runGraph(vector<Rule *> myRules) {
        createDependencyGraph(myRules);
        dfsForest();
        //printPostorder();
        dfsForestReverse();
        //printPostorder();
        //printSCC();
    }

    const vector<set<int>> &getSccs() const {
        return sccs;
    }

};

#endif //CS236PROJECT3_REAL__GRAPH_H
