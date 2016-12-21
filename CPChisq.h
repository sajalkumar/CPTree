//
//  CPChisq.hpp
//  CPChisq
//
//  Created by Sajal Kumar on 3/3/16.
//  Copyright © 2016 NMSUSongLab. All rights reserved.
//

#ifndef CPChisq_hpp
#define CPChisq_hpp

#include <stdio.h> 
#include "StatDistributions.h"
#include "utility.hpp"

using namespace std;

vector<double>  cpx2(const vector<vector<vector<double> > > & );

double getPvaluecpx2(); 

double getSum(const vector<vector<double> > &);

vector<vector<double> >  getExpected(const vector<vector<double> > &);

vector<double>  getRowSum(const vector<vector<double> > &);

vector<double>  getColumnSum(const vector<vector<double> > &);

double chisqst(const vector<vector<double> > &,const vector<vector<double> > &);

vector<vector<double> >  getpooled(const vector<vector<double> > &, const vector<vector<double> > &);

vector<vector<double> >  getExpectedRef(const vector<vector<double> > & ,const vector<vector<double> > &,double);
#endif /* CPChisq_hpp */
