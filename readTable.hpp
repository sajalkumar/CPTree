//
//  readTable.hpp
//  CPTree
//
//  Created by Sajal Kumar on 2/25/16.
//  Copyright © 2016 NMSUSongLab. All rights reserved.
//

#ifndef readTable_hpp
#define readTable_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "utility.hpp"

vecstr readall(std::string);
framestr readTable(const vecstr &,char);


#endif /* readTable_hpp */
