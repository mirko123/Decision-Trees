//
//  main.cpp
//  Decision Trees
//
//  Created by Мирослав Николов on 7.01.18 г..
//  Copyright © 2018 г. Мирослав Николов. All rights reserved.
//

#include <iostream>
#include "Cancer.h"
//#include "PlayTenis.h"
#include "FileManager.h"
//#include "DecisionTree.h"
#include "DecisionTreeV2.h"
#include "ParseTree.h"
using namespace std;


void test() {
    vector<Cancer> playtenis_;
    vector<string> stringFields;
    
    string fileName = "data.txt";
    FileManager::ParseFile(fileName, playtenis_);
    
    
    DecisionTreeV2 tree(playtenis_);
    
    string line;
    getline (cin, line, '\n');
    
    while(line != "end" && line != "quit" && line != "exit") {
        Cancer newCancer(line);
        cout<<ParseTree(tree.root, newCancer)<<endl;
        
        getline (cin, line, '\n');
    }
    
//    cout<<ParseTree(tree.root, tree._cancers[0])<<endl;
//    unordered_map<string, int> types = tree.getTypes(playtenis_,"age");
    
//    vector<Cancer> filt = tree.filterClass(playtenis_, "Outlook", "Rainy");
// 
//    cout<<tree.calculateEntropy(filt)<<endl;
//    cout<<tree.calculateInformationGain(playtenis_,"Windy")<<endl;
    
}

int main(int argc, const char * argv[]) {
    test();
    
    
//    vector<Cancer> cancers;
//    vector<string> stringFields;
//    
//    string fileName = "data.txt";
//    FileManager::ParseFile(fileName, cancers);
//    
//    
////    for(auto cancer : cancers)
////    {
////        cancer.Print();
////    }
//
//    
//    DecisionTreeV2 tree(cancers);
//    unordered_map<string, int> types = tree.getTypes(cancers,"age");
//    
////    cout<<tree.probability(types,"40-49")<<endl;
////    double entropy = tree.calculateEntropy("age");
////    cout<< "calc: " << entropy<<endl;
////    entropy = tree.getEntropy("age");
////    cout<< "nocl: " << entropy<<endl;

    
    return 0;
}
