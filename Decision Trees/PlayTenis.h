//
//  PlayTenis.h
//  Decision Trees
//
//  Created by Мирослав Николов on 9.01.18 г..
//  Copyright © 2018 г. Мирослав Николов. All rights reserved.
//

#ifndef PlayTenis_h
#define PlayTenis_h

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
        fields["Outlook"]="";
        fields["Temperature"]="";
        fields["Humidity"]="";
        fields["Windy"]="";
        fields["Class"]="";
    }
    Cancer(string line) {
        stringstream ss(line);
        
        string val;
        getline(ss,val, ',');
        setField("Outlook", val);
        getline(ss,val, ',');
        setField("Temperature", val);
        getline(ss,val, ',');
        setField("Humidity", val);
        getline(ss,val, ',');
        setField("Windy", val);
        getline(ss,val, ',');
        setField("Class", val);
    }
    
    string getFieldType(string fieldName) {
        return fields[fieldName];
    }
    void setField(string fieldName, string value) {
//        if(value != "?") {
//            value = value.substr(1, value.size() - 2);
//        }
        fields[fieldName] = value;
    }
    
    void Print() {
        for(auto &field : fields)
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



#endif /* PlayTenis_h */
