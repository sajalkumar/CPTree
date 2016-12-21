//
//  StatDistributions.h
//  gln
//
//  Created by Joe Song on 11/2/11.
//  Copyright (c) 2011 New Mexico State University. All rights reserved.
//

#ifndef gln_StatDistributions_h
#define gln_StatDistributions_h

#include <iostream>
#include <cassert>
#include "boost/math/distributions/fisher_f.hpp"
#include "boost/math/distributions/gamma.hpp"
#include "boost/math/distributions/normal.hpp"
using namespace boost::math;


double FPvalue(double Fstat, int df1, int df2);

double ChisqPvalue(double x, size_t df);

double GammaPvalue(double x, double shape, double scale);

double NormalPvalue(double x, double mean, double stdev, bool two_sided);

#endif
