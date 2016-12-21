//
//  EntropyMethod.cpp
//  CPTree
//
//  Created by Sajal Kumar  on 6/4/16.
//  Copyright © 2016 NMSUSongLab. All rights reserved.
//

#include "EntropyMethod.hpp"

vecdouble Entropymethod(const vecstr x, const vecstr & y, const vecstr & classlabels)
{
    vecdouble prior=getPrior(y, classlabels);
    vecdouble res;
    double information_gain=0;
    
    //calculating the impurity in parent
    double parent=entropy(prior);
    
    vecstr unx=retunique(x);
    
    for(int i=0;i<unx.size();i++)
    {
        prior.clear();
        prior=getPrior(selectOP(y, which_is_equal(x, unx[i])), classlabels);
        information_gain+=((double)which_is_equal(x, unx[i]).size()/y.size())*entropy(prior);
    }
    
    information_gain=parent-information_gain;
    res.push_back(information_gain);
    res.push_back(information_gain);
    return res;
    
}

/*Given a vector of probabilities, this method computes the gini index*/
double entropy(const vecdouble & p)
{
    double res=0;
    for(int i=0;i<p.size();i++)
    {
        if(p[i]!=0)
            res=res+(-p[i]*log2(p[i]));
        
    }
    return res;
}

void testentropy()
{
    vecstr x;
    x.push_back("0");
    x.push_back("1");
    x.push_back("0");
    x.push_back("1");
    x.push_back("0");
    x.push_back("1");
    x.push_back("0");
    x.push_back("1");
    x.push_back("0");
    x.push_back("1");
    x.push_back("0");
    x.push_back("1");
    x.push_back("0");
    x.push_back("1");
    x.push_back("0");
    x.push_back("1");
    
    vecstr y;
    y.push_back("0");
    y.push_back("1");
    y.push_back("1");
    y.push_back("0");
    y.push_back("0");
    y.push_back("1");
    y.push_back("1");
    y.push_back("0");
    y.push_back("0");
    y.push_back("1");
    y.push_back("1");
    y.push_back("0");
    y.push_back("0");
    y.push_back("1");
    y.push_back("1");
    y.push_back("0");
    
    vecstr classlabels;
    classlabels.push_back("0");
    classlabels.push_back("1");
    
    vecdouble res=Entropymethod(x, y, classlabels);
    printvector(res);
}