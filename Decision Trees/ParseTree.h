//
//  ParseTree.h
//  Decision Trees
//
//  Created by Мирослав Николов on 12.01.18 г..
//  Copyright © 2018 г. Мирослав Николов. All rights reserved.
//

#ifndef ParseTree_h
#define ParseTree_h

#include "Node.h"

Node* getChield(Node *root, string val) {
    for(auto &child : root->chields)
    {
        if(child->edge_fieldVal == val) {
            return child;
        }
    }
    return root->chields[0];
}

string ParseTree(Node *root, Cancer &cancer) {
    if(root->fieldName == "Class") {
        return root->chields[0]->edge_fieldVal;
    }
    
    string canerFieldVal = cancer.fields[root->fieldName];
    Node* child = getChield(root, canerFieldVal);
    
    return ParseTree(child, cancer);
}

#endif /* ParseTree_h */
