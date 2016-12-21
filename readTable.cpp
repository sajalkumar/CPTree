//
//  readTable.cpp
//  CPTree
//
//  Created by Sajal Kumar on 2/25/16.
//  Copyright © 2016 NMSUSongLab. All rights reserved.
//

#include "readTable.hpp"

using namespace std;

vecstr readall(string path){
    string line;
    vecstr alllines;
    ifstream myfile;
    myfile.open(path);
    if(myfile.is_open())
    {
        while (getline(myfile,line))
        {
            alllines.push_back(line);
        }
        
        myfile.close();
    }
    return alllines;
}


framestr readTable(const vecstr & allines, char sep)
{
    vecstr records;
    framestr table;
    size_t pos;
    string ref;
    for(int i=0;i<allines.size();i++)
    {
        ref=allines[i];
        if((pos=ref.find("\r"))!=-1)
            ref.replace(pos, ref.size()-1, "");
        while (!ref.empty()&&ref.find_first_of(sep)!=-1) {
            pos=ref.find_first_of(sep);
            records.push_back(ref.substr(0,pos));
            ref.erase(0,pos+1);
        }
        records.push_back(ref);
        table.push_back(records);
        records.clear();
    }
    return table;
}

