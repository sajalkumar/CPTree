//
//  binsplit.hpp
//  CPTree
//
//  Created by Sajal Kumar on 2/25/16.
//  Copyright © 2016 NMSUSongLab. All rights reserved.
//

#ifndef binsplit_hpp
#define binsplit_hpp

#include <stdio.h>
#include "utility.hpp"

int bestattribute(framedouble, framestr);
int bestsplitret();
framestr leftchild(framestr,int);
framestr rightchild(framestr,int);

#endif /* binsplit_hpp */
