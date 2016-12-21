//
//  ChisqDirTest.h
//  CPTree
//
//  Created by Sajal Kumar on 4/21/16.
//  Copyright © 2016 NMSUSongLab. All rights reserved.
//

#ifndef ChisqDirTest_h
#define ChisqDirTest_h

#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include "utility.hpp"
#include "CPChisq.h"

#include "StatDistributions.h"
using namespace std;

void ChisquareTest1DNoPValue(const vector<int> & x_obs,
                             const vector<double> & p_null, int K,
                             double & chisquare, size_t & df);

double ChisqDirTest(const vector< vector<int> > & table_obs, double & chisquare, size_t & df, const string & method, string type);

void test_ChisqDirTest();

#endif /* ChisqDirTest_h */
