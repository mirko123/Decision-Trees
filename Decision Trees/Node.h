//
//  Node.h
//  Decision Trees
//
//  Created by Мирослав Николов on 12.01.18 г..
//  Copyright © 2018 г. Мирослав Николов. All rights reserved.
//

#ifndef Node_h
#define Node_h

class Node {
public:
    string fieldName;
    string edge_fieldVal;
    Node *father;
    vector<Node*> chields;
    string mostPopularClass;
    
    Node(Node *father) {
        this->father = father;
        if(father != nullptr) {
            father->chields.push_back(this);
        }
    }
};

#endif /* Node_h */
