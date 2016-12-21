//
//  binsplit.cpp
//  CPTree
//
//  Created by Sajal Kumar on 2/25/16.
//  Copyright © 2016 NMSUSongLab. All rights reserved.
//

#include "binsplit.hpp"

int bestsplit;

int bestattribute(framedouble goodness, framestr dataframe)
{
    vecdouble indicator;
    double absbest;
    int bestindicator;
    for(int i=0;i<goodness.size();i++)
    {
        indicator.push_back(findmax(goodness[i]));
    }
    absbest=findmax(indicator);
    //bestindicator=which_is_equal<double>(indicator, absbest)[0];
    //bestsplit=which_is_equal(goodness[bestindicator], bestindicator)[0];
    return bestindicator;
}


int bestsplitret()
{
    return bestsplit;
}



framestr leftchild(framestr frame, int bestsplit)
{
    frame=Transposeframe(frame);
    framestr newframe;
    for(int i=0;i<=bestsplit;i++)
        newframe.push_back(frame[i]);
    return Transposeframe(newframe);
}



framestr rightchild(framestr frame, int bestsplit)
{
    frame=Transposeframe(frame);
    framestr newframe;
    for(int i=bestsplit+1;i<frame.size();i++)
        newframe.push_back(frame[i]);
    return Transposeframe(newframe);
}


