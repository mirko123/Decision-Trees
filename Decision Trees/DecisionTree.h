//
//  DecisionTree.h
//  Decision Trees
//
//  Created by Мирослав Николов on 7.01.18 г..
//  Copyright © 2018 г. Мирослав Николов. All rights reserved.
//

#ifndef DecisionTree_h
#define DecisionTree_h

#include <queue>
#include <math.h>

class DecisionTree {
    
    bool Compare(const string &first, const string &second)
    {
        long double v1 = getEntropy(first);
        long double v2 = getEntropy(second);
        return true;
    }
    
    void setFieldsEntropy() {
        for(auto field : cancers[0].fields)
        {
            string fieldName = field.first;
            long double entropy = calculateEntropy(fieldName);
            fieldsEntropy[fieldName] = entropy;
//            cout<<entropy<< endl << getEntropy(fieldName) <<endl <<endl;
            
        }
    }
    
    void initQueue() {
        for(auto field : cancers[0].fields)
        {
            string fieldName = field.first;
            queue.push(fieldName);
        }
    }
    
    long double InformationGain(string result, string fieldName) {
        long double gain;
        
        return gain;
    }
    
    vector<Cancer> filterClass(vector<Cancer> &cancers, string value) {
        vector<Cancer> newCancers;
        for(auto &cancer : cancers) {
            if(cancer.fields["Class"] == value) {
                newCancers.push_back(cancer);
            }
        }
        return newCancers;
    }
    
public:
    vector<Cancer> cancers;
    vector<Cancer> cancersRecurrence;
    priority_queue<string, vector<string>, function<bool(string, string)>> queue;
    unordered_map<string, long double> fieldsEntropy;
    
    DecisionTree() {
        
    }
    DecisionTree(vector<Cancer> &cancers): queue([this] (string a, string b) { return Compare(a, b); }) {
        this->cancers = cancers;
        setFieldsEntropy();
        
        initQueue();
        
        cancersRecurrence = filterClass(this->cancers, "recurrence-events");
    }
    
    unordered_map<string, int> getTypes(string fieldName) {
        unordered_map<string, int> types;
        for(auto cancer : cancers)
        {
            string cancerType = cancer.getFieldType(fieldName);
            types[cancerType] += 1;
        }
        
        return types;
    }
    
    double probability(unordered_map<string, int> &types, string typeName) {
        return (double)(types[typeName])/cancers.size();
    }
    
    double calculateEntropy(string fieldName) {
        double entropy;
        unordered_map<string, int> types = getTypes(fieldName);
        
        long double value = 0;
        for(auto type : types)
        {
            long double p = probability(types, type.first);
            long double newVal = (long double)p*log2(p);
            value -= newVal;
        }
        
        return entropy;
    }
    long double getEntropy(string fieldName) {
        return fieldsEntropy[fieldName];
    }
};

#endif /* DecisionTree_h */
