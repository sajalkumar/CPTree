//
//  EntropyMethod.hpp
//  CPTree
//
//  Created by Sajal Kumar  on 6/4/16.
//  Copyright © 2016 NMSUSongLab. All rights reserved.
//

#ifndef EntropyMethod_hpp
#define EntropyMethod_hpp

#include <stdio.h>
#include "utility.hpp"
#include <math.h>


vecdouble Entropymethod(const vecstr x, const vecstr & y, const vecstr & classlabels);
double entropy(const vecdouble & p);
void testentropy();

#endif /* EntropyMethod_hpp */
