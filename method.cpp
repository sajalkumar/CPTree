//
//  method.cpp
//  CPTree
//
//  Created by Sajal Kumar  on 3/30/16.
//  Copyright © 2016 NMSUSongLab. All rights reserved.
//

#include "method.hpp"

vecdouble method(const framestr & attributes, const vecstr & y, const vecstr & classlabels, string methodname, int arity, int mode)
{
    if(methodname == "gini")
    {
        
        if(arity==1||mode==1)
        {
            return Ginimethod(attributes[0], y, classlabels);
        }
        else
        {
            vecstr x=mergetwo(attributes[0], attributes[1], ",");
            return Ginimethod(x, y, classlabels);
        }
        
    } else if(methodname=="entropy")
    {
        if(arity==1||mode==1)
        {
            return Entropymethod(attributes[0], y, classlabels);
        }
        else
        {
            vecstr x=mergetwo(attributes[0], attributes[1], ",");
            return Entropymethod(x, y, classlabels);
        }
        
    } else if(methodname == "cpx2")
    {
        return CPX2method(attributes[0], attributes[1], y, mode);
    } else if(methodname == "funchisq")
    {
        if(arity==1||mode==1)
        {
            return Funchisqmethod(attributes[0], y, classlabels, "","non-constant");
        }
        else
        {
            vecstr x=mergetwo(attributes[0], attributes[1], ",");
            return Funchisqmethod(x, y, classlabels, "","non-constant");
        }
    } else if(methodname == "funchisqnorm")
    {
        
        if(arity==1||mode==1)
        {
            return Funchisqmethod(attributes[0], y, classlabels, "normalized","non-constant");
        }
        else
        {
            vecstr x=mergetwo(attributes[0], attributes[1], ",");
            return Funchisqmethod(x, y, classlabels, "normalized","non-constant");
        }
        
    } else if(methodname=="funchisqall")
    {
        if(arity==1||mode==1)
        {
            return Funchisqmethod(attributes[0], y, classlabels, "","all");
        }
        else
        {
            vecstr x=mergetwo(attributes[0], attributes[1], ",");
            return Funchisqmethod(x, y, classlabels, "","all");
        }
    } else if(methodname=="funchisqnormall")
    {
        if(arity==1||mode==1)
        {
            return Funchisqmethod(attributes[0], y, classlabels, "normalized","all");
        }
        else
        {
            vecstr x=mergetwo(attributes[0], attributes[1], ",");
            return Funchisqmethod(x, y, classlabels, "normalized","all");
        }
    } else if(methodname=="chisq"||methodname=="chisqcs")
    {
        if(arity==1||mode==1)
        {
            return Chisqmethod(attributes[0], y, classlabels);
        }
        else
        {
            vecstr x=mergetwo(attributes[0], attributes[1], ",");
            return Chisqmethod(x, y, classlabels);
        }

    } else{
        cout<<"No method name specified, returning 0,1"<<endl;
        vecdouble temp;
        temp.push_back(0);
        temp.push_back(1);
        return temp;
    }
}