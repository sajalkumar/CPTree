//
//  ChiSqMethod.cpp
//  CPTree
//
//  Created by Sajal Kumar  on 6/4/16.
//  Copyright © 2016 NMSUSongLab. All rights reserved.
//

#include "ChiSqMethod.hpp"

vecdouble Chisqmethod(const vecstr x, const vecstr & y, const vecstr & classlabels)
{
    double pvalue=1,st=0;
    size_t df=0;
    vecstr neox=retunique(x);
    framedouble table;
    vecdouble res;
    vecdouble temp;
    vecint temp2;
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
    st=chisqst(table, getExpected((framedouble)table));
    
    if(table.size()-1==0)
        df=table[0].size();
    else if(table[0].size()-1==0)
        df=table.size();
    else
        df = table.size() * table[0].size();
    
    pvalue = ChisqPvalue(st, df);
    res.push_back(st);
    res.push_back(pvalue);
    return res;
}
