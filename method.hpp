//
//  method.hpp
//  CPTree
//
//  Created by Sajal Kumar  on 3/30/16.
//  Copyright © 2016 NMSUSongLab. All rights reserved.
//

#ifndef method_hpp
#define method_hpp

#include <stdio.h>
#include "CPX2Method.h"
#include "GiniMethod.hpp"
#include "FunChisqMethod.hpp"
#include "ChiSqMethod.hpp"
#include "EntropyMethod.hpp"
#include "utility.hpp"

vecdouble method(const framestr &, const vecstr &, const vecstr &, string, int, int);

#endif /* method_hpp */
