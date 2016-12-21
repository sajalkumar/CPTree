//
//  CorrelationTest.hpp
//  CPTree
//
//  Created by Sajal Kumar on 5/16/16.
//  Copyright © 2016 NMSUSongLab. All rights reserved.
//

#ifndef CorrelationTest_hpp
#define CorrelationTest_hpp

#include <stdio.h>
#include <gsl/gsl_statistics_double.h>
#include "utility.hpp"
#include <boost/thread.hpp>
#include <boost/bind.hpp>

using namespace std;

void corTest(const framedouble & tab, int beg, int end, vecint & res);

vecint corTestMain(const framestr & tab);

#endif /* CorrelationTest_hpp */
