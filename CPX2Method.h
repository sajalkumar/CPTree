//
//  Method.hpp
//  CPTree
//
//  Created by Sajal Kumar on 2/26/16.
//  Copyright © 2016 NMSUSongLab. All rights reserved.
//

#ifndef Method_hpp
#define Method_hpp

#include <stdio.h>
#include "utility.hpp"
#include "CPChisq.h"

vecdouble CPX2method(const vecstr &,const vecstr &, const vecstr &, int);
vector<framedouble> contigencytables(const vecstr & x1, const vecstr & x2, const vecstr & y, int);
#endif /* Method_hpp */
