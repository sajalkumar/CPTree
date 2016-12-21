//
//  FunChisqMethod.cpp
//  CPTree
//
//  Created by Sajal Kumar on 4/21/16.
//  Copyright © 2016 NMSUSongLab. All rights reserved.
//

#include "FunChisqMethod.hpp"

vecdouble Funchisqmethod(const vecstr x, const vecstr & y, const vecstr & classlabels, string methodname, string type)
{
    double pvalue=1;
    double st=0;
    size_t df=0;
    vecstr neox=retunique(x);
    frameint table;
    vecdouble res;
    vecint temp;
    for(int i=0;i<classlabels.size();i++)
    {
        vecstr neox1=selectOP(x, which_is_equal(y, classlabels[i]));
        for(int j=0;j<neox.size();j++)
        {
            temp.push_back((int)which_is_equal(neox1, neox[j]).size());
        }
        table.push_back(temp);
        temp.clear();
    }
    table=Transposeframe(table);
    pvalue = ChisqDirTest(table, st, df, methodname,type);
    res.push_back(st);
    res.push_back(pvalue);
    return res;
}


vecdouble FunchisqmethodBB(const vecstr x, const vecstr & y, const vecstr & classlabels, string methodname, string type)
{
    double pvalue=1;
    double st=0;
    size_t df=0;
    vecstr neox=retunique(x);
    frameint table;
    vecdouble res;
    vecint temp;
    for(int i=0;i<classlabels.size();i++)
    {
        vecstr neox1=selectOP(x, which_is_equal(y, classlabels[i]));
        for(int j=0;j<neox.size();j++)
        {
            temp.push_back((int)which_is_equal(neox1, neox[j]).size());
        }
        table.push_back(temp);
        temp.clear();
    }
    table=Transposeframe(table);
    pvalue = ChisqDirTest(table, st, df, methodname,type);
    res.push_back(st);
    res.push_back(pvalue);
    return res;
}
