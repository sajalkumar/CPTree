//
//  Method.cpp
//  CPTree
//
//  Created by Sajal Kumar on 2/26/16.
//  Copyright © 2016 NMSUSongLab. All rights reserved.
//

#include "CPX2Method.h"
using namespace std;

vecdouble CPX2method(const vecstr & x1, const vecstr & x2, const vecstr & y, int mode)
{
    vector<double> res;
    vector<framedouble> tb=contigencytables(x1, x2, y, mode);
    if(tb.size()>1)
    {
        res=cpx2(tb);
        /*if(mode!=1)
        {
            vecint size;
            size.push_back((int)tb[0].size()-1);
            size.push_back((int)tb[0][1].size()-1);
            res[0]=sqrt(res[0]/y.size()*findmin(size));
        }
        else
        {
            res[0]=sqrt(res[0]/y.size());
        }*/
    }
    else{
        res.push_back(0);
        res.push_back(1);
    }
    return res;
}

vector<framedouble> contigencytables(const vecstr & x1, const vecstr & x2, const vecstr & y, int mode)
{
    vector<framedouble> table;
    vecstr labels=retunique(y);
    vecstr neox1,neox2,mneo,unneox1,unneox2;
    framedouble currenttable;
    vecdouble temp;
    if(mode!=1)
    {
        unneox1=retunique(x1);
        unneox2=retunique(x2);
        for(int i=0;i<labels.size();i++)
        {
            neox1=selectOP(x1, which_is_equal(y, labels[i]));
            neox2=selectOP(x2, which_is_equal(y, labels[i]));
            mneo=mergetwo(neox1, neox2,"");
            for(int j=0;j<unneox1.size();j++)
            {
                for(int k=0;k<unneox2.size();k++)
                {
                    temp.push_back((double)which_is_equal(mneo, (unneox1[j]+unneox2[k])).size());
                }
                currenttable.push_back(temp);
                temp.clear();
            }
            
            table.push_back(currenttable);
            currenttable.clear();
        }
    }
    else
    {
        unneox1=retunique(x1);
        for(int i=0;i<labels.size();i++)
        {
            neox1=selectOP(x1, which_is_equal(y, labels[i]));
            for(int j=0;j<unneox1.size();j++)
            {
                temp.push_back((double)which_is_equal(neox1, unneox1[j]).size());
            }
            currenttable.push_back(temp);
            temp.clear();
            
            table.push_back(currenttable);
            currenttable.clear();
        }
    }
    
    return table;
}