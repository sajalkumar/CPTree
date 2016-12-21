//
//  GiniMethod.hpp
//  CPTree
//
//  Created by Sajal Kumar on 3/29/16.
//  Copyright © 2016 NMSUSongLab. All rights reserved.
//

#ifndef GiniMethod_hpp
#define GiniMethod_hpp

#include <stdio.h>
#include "utility.hpp"
#include "StatDistributions.h"

vecdouble Ginimethod(const vecstr x, const vecstr & y, const vecstr & classlabels);
double gini(const vecdouble & p);
void testgini();
#endif /* GiniMethod_hpp */
