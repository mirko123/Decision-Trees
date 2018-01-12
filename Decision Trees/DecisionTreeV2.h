//
//  DecisionTreeV2.h
//  Decision Trees
//
//  Created by Мирослав Николов on 9.01.18 г..
//  Copyright © 2018 г. Мирослав Николов. All rights reserved.
//

#ifndef DecisionTreeV2_h
#define DecisionTreeV2_h

#include <queue>
#include <math.h>
#include <limits>
#include <stack>
#include <unordered_set>
#include "Node.h"


class DecisionTreeV2 {
    
    bool Compare(const string &first, const string &second)
    {
        vector<Cancer> cancers = states.top();
        long double v1 = calculateInformationGain(cancers,first);
        long double v2 = calculateInformationGain(cancers,second);
        return v1 < v2;
    }
    
    
//    void initQueue() {
//        for(auto &field : _cancers[0].fields)
//        {
//            string fieldName = field.first;
//            queue.push(fieldName);
//        }
//    }
    
    long double InformationGain(string result, string fieldName) {
        long double gain;
        
        return gain;
    }
    
    string findBestFieldIG(vector<Cancer> &state, unordered_set<string> &filterFields) {
//        long double maxIG = numeric_limits<long double>::min();
        long double maxIG = -10000000;
        string maxIGfieldName = "";
        
        for(auto &fieldName : filterFields)
        {
            if(fieldName == "Class") {
                continue;
            }
            
            long double newIG = calculateInformationGain(state, fieldName);
            if(maxIG < newIG) {
                maxIG = newIG;
                maxIGfieldName = fieldName;
            }
        }
        if(maxIG == 0 || state.size() == 0) {
            maxIGfieldName = "Class";
        }
        
//        if (state.size() == 0) {
//            throw new invalid_argument("error");
//        }
        return maxIGfieldName;
    }
    
//    unordered_map<string, int> rootTypes = getTypes(newState, "Class");
    string mostPopularType(vector<Cancer> &states, string fieldName) {
        unordered_map<string, int> types = getTypes(states, fieldName);
        int currentMax = 0;
        string maxType;
        
        for(auto &type : types)
        {
            if(currentMax < type.second) {
                currentMax = type.second;
                maxType = type.first;
            }
        }
        return maxType;
    }
    
    bool parseFinalNode(Node* node, vector<Cancer> &currentState) {
//        unordered_map<string, int> rootTypes;
        if (node->fieldName == "Class") {
            Node *newChild = new Node (node);
            newChild->fieldName = "Final";
            
            unordered_map<string, int> nodeClassTypes = getTypes(currentState, "Class");
            
            string finalClassType = "";
            int maxTypeCount = 0;
            for(auto &type : nodeClassTypes)
            {
                if(type.second > maxTypeCount) {
                    maxTypeCount = type.second;
                    finalClassType = type.first;
                }
            }
            
            if(maxTypeCount == 0) {
                finalClassType = node->father->mostPopularClass;
            }
            
            newChild->edge_fieldVal = finalClassType;
            
            return true;
        }
        else {
            return false;
        }
    }
public:
//    stack<vector<pair<string, string>>> filterParams;
    Node *root;
    stack<vector<Cancer>> states;
    stack<vector<pair<string, string>>> filterBy;
    stack<unordered_set<string>> remainderFields;
    stack<Node*> nodes;
    vector<Cancer> _cancers;
    vector<Cancer> cancersRecurrence;
//    priority_queue<string, vector<string>, function<bool(string, string)>> queue;
//    unordered_map<string, long double> fieldsEntropy;
    
    DecisionTreeV2() {
        this->root = new Node(NULL);
    }
    DecisionTreeV2(vector<Cancer> &cancers)
//    : queue([this] (string a, string b) { return Compare(a, b); })
    {
        this->_cancers = cancers;
        this->states.push(_cancers);
        this->filterBy.push(vector<pair<string, string> >());
//        this->remainderFields.push(Cancer::getFields(_cancers[0]));
        
//        setFieldsEntropy();
        
//        initQueue();
        
        
        
        
        cancersRecurrence = filterClass(this->_cancers, "Class","recurrence-events");
        
        
        
        
        unordered_set<string> rootFields = Cancer::getFields(_cancers[0]);
//        remainderFields.pop();
        
//        for(auto &field : _cancers[0].fields) {
//            currentFields.push_back(field.first);
//        }
        
//        vector<pair<string, string> > rootfilter;
        
        this->root = new Node(nullptr);
        
        string rootFieldVal = findBestFieldIG(cancers, rootFields);
        rootFields.erase(rootFieldVal);
        this->remainderFields.push(rootFields);
        
        unordered_map<string, int> rootTypes = getTypes(cancers, rootFieldVal);
        this->root->fieldName = rootFieldVal;
        
//        for(auto &type : rootTypes)
//        {
//            Node newChild(root);
//            newChild.edge_fieldVal = type.first;
//            
//            vector<pair<string, string> > filters;
//            pair<string, string> newFilter(newChild.father->fieldName, type.first);
//            filters.push_back(newFilter);
//            
//            vector<Cancer> &fatherState = cancers;
//            vector<Cancer> currentState = filterClass(fatherState, filters);
//            states.push(currentState);
//            filterBy.push(filters);
//            
//            this->root->chields.push_back(newChild);
//        }
//        
        nodes.push(root);
        
        
  
        while (!nodes.empty()) {
            Node *currentNode = nodes.top();
            
            nodes.pop();
            
            vector<Cancer> currentState = states.top();
            states.pop();
            
            vector<pair<string, string>> filters = filterBy.top();
            filterBy.pop();
            
            unordered_set<string> currentFields = remainderFields.top();
            remainderFields.pop();
            
            unordered_map<string, int> rootTypes = getTypes(cancers, currentNode->fieldName);
            
            bool isFinalLeaf = parseFinalNode(currentNode, currentState);
            
            if(!isFinalLeaf) {
                for(auto &type : rootTypes)
                {
                    Node *newChild = new Node (currentNode);
                    newChild->edge_fieldVal = type.first;
                    
                    vector<pair<string, string>> newFilters = filters;
                    newFilters.push_back(pair<string, string>(currentNode->fieldName, newChild->edge_fieldVal));
                    filterBy.push(newFilters);
                    
                    vector<Cancer> newState = filterClass(currentState, newFilters);
                    newChild->mostPopularClass = mostPopularType(newState, "Class");
                    states.push(newState);
                    
                    string IGbestfield = findBestFieldIG(newState, currentFields);
                    newChild->fieldName = IGbestfield;
                    
                    unordered_set<string> newRemainderFields = currentFields;
                    
                    newRemainderFields.erase(IGbestfield);
                    
                    remainderFields.push(newRemainderFields);
                    
                    nodes.push(newChild);
                }
                    
            }
//            cout<<"here"<<endl;
            
        }
        
//        cout<<rootVal<<endl;
        
    }
    
    vector<Cancer> filterClass(vector<Cancer> &cancers, string fieldName, string fieldVal) {
        vector<Cancer> newCancers;
        for(auto &cancer : cancers) {
            if(cancer.fields[fieldName] == fieldVal) {
                newCancers.push_back(cancer);
            }
        }
        return newCancers;
    }
    
    vector<Cancer> filterClass(vector<Cancer> &cancers, vector<pair<string, string>> &outfilters) {
        vector<Cancer> newCancers;
        for(auto &cancer : cancers) {
            bool check = true;
            
            for(auto &filter : outfilters) {
                if(cancer.fields[filter.first] != filter.second) {
                    check = false;
                    break;
                }
            }
            
            if(check) {
                newCancers.push_back(cancer);
            }
        }
        return newCancers;
    }
    
    unordered_map<string, int> getTypes(vector<Cancer> &cancers, string fieldName) {
        unordered_map<string, int> types;
        for(auto cancer : cancers)
        {
            string cancerType = cancer.getFieldType(fieldName);
            types[cancerType] += 1;
        }
        
        return types;
    }
    
    double probability(unordered_map<string, int> &types, string typeName, int countOfAll) {
        return (double)(types[typeName])/countOfAll;
    }
    
    double calculateEntropy(vector<Cancer> &cancers) {
        string fieldNameClasses = "Class";
//        double entropy;
        unordered_map<string, int> types = getTypes(cancers, fieldNameClasses);
        
        long double value = 0;
        for(auto type : types)
        {
            long double p = probability(types, type.first, cancers.size());
            long double newVal = (long double)p*log2(p);
            value -= newVal;
        }
        
        return value;
    }
    
    long double calculateInformationGain(vector<Cancer> &cancers, string fieldName) {
        long double E_s = calculateEntropy(cancers);
        unordered_map<string, int> types = getTypes(cancers, fieldName);
        
        long double sum = 0;
        for(auto type : types)
        {
            vector<Cancer> filteredCancers = filterClass(cancers, fieldName, type.first);
            
            long double p = probability(types, type.first, cancers.size());
            long double entropy = calculateEntropy(filteredCancers);
            long double currentValue = p*entropy;
            sum += currentValue;
        }
        
        return E_s - sum;
    }
};


#endif /* DecisionTreeV2_h */
