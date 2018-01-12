//
//  Cancer.h
//  Decision Trees
//
//  Created by Мирослав Николов on 7.01.18 г..
//  Copyright © 2018 г. Мирослав Николов. All rights reserved.
//

#ifndef Cancer_h
#define Cancer_h

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Cancer {
public:
    unordered_map<string, string> fields;
    
    Cancer() {
        fields["age"]="";
        fields["menopause"]="";
        fields["tumor-size"]="";
        fields["inv-nodes"]="";
        fields["node-caps"]="";
        fields["deg-malig"]="";
        fields["breast"]="";
        fields["breast-quad"]="";
        fields["irradiat"]="";   
        fields["Class"]="";
    }
    Cancer(string line) {
        stringstream ss(line);
        
        string val;
        getline(ss,val, ',');
        setField("age", val);
        getline(ss,val, ',');
        setField("menopause", val);
        getline(ss,val, ',');
        setField("tumor-size", val);
        getline(ss,val, ',');
        setField("inv-nodes", val);
        getline(ss,val, ',');
        setField("node-caps", val);
        getline(ss,val, ',');
        setField("deg-malig", val);
        getline(ss,val, ',');
        setField("breast", val);
        getline(ss,val, ',');
        setField("breast-quad", val);
        getline(ss,val, ',');
        setField("irradiat", val);
        getline(ss,val, ',');
        setField("Class", val);
    }
    
    string getFieldType(string fieldName) {
        return fields[fieldName];
    }
    void setField(string fieldName, string value) {
        if(value != "?") {
            value = value.substr(1, value.size() - 2);
        }
        fields[fieldName] = value;
    }
    
    void Print() {
        for(auto field : fields)
        {
            cout<<field.second<<" ";
        }
        cout<<endl;
    }
    
    static unordered_set<string> getFields(Cancer &cancer) {
        unordered_set<string> fields;
        for(auto &field : cancer.fields)
        {
            fields.insert(field.first);
        }
        return fields;
    }
};

#endif /* Cancer_h */
