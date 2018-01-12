//
//  FileManager.h
//  KNN iris
//
//  Created by Мирослав Николов on 28.12.17 г..
//  Copyright © 2017 г. Мирослав Николов. All rights reserved.
//

#ifndef FileManager_h
#define FileManager_h

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

class FileManager {
    
public:
    static void ParseFile(string fileName, vector<Cancer> &cancers) {
        
        //    string line;
        ifstream file(fileName);
        
        if (file.is_open())
        {
            string line;
            while ( getline (file, line, '\n') )
            {
                Cancer newCancer(line);
                cancers.push_back(newCancer);
            }
            file.close();
        }
        
        else cout << "Unable to open file";
    }
    
    static int linesCount(string fileName) {
        ifstream file (fileName);
        int counter = count(std::istreambuf_iterator<char>(file),
                            std::istreambuf_iterator<char>(), '\n');
        
        return counter;
    }
};

#endif /* FileManager_h */
