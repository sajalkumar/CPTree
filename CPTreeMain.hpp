//
//  CPTreeMain.hpp
//  CPTree
//
//  Created by Sajal Kumar on 2/26/16.
//  Copyright © 2016 NMSUSongLab. All rights reserved.
//

#ifndef CPTreeMain_hpp
#define CPTreeMain_hpp

#include <stdio.h>
#include "utility.hpp"
//#include "binsplit.hpp"
#include "readTable.hpp"
#include "method.hpp"
#include "ChisqDirTest.h"
#include <boost/thread.hpp>
#include <boost/bind.hpp>

class CPTree
{
public:
    framestr treestruct;
    vector<frameint> currentiterator;
    vecstr columnnames;
    vecint loss;
    vecstr classlabels;
    vecint getLossMatrix();
    vecstr getClassLabels();
    vecstr getColumnNames();
    framestr getTreeStruct();
    CPTree(const vecstr &,int);
    CPTree(const vecstr &, int, const vecint &);
    void CPTreeMainRecursive(const framestr &);
    void CPTreeMainIterative(framestr,string,int,double);
};

framedouble getAllVariableStats1D(const vecstr & y, string methodname, const vecstr & classlabels, const vecstr arvalarray, const framestr & dataframe);

vecdouble getallvariableStatistics(const vecstr & y, string methodname, int arity, const vecstr & classlabels, const vecstr & arvalarray, const framestr & dataframe);

vecdouble getAllVariableStatsLinear(const vecstr & y, string methodname, const vecstr & classlabels, int arity, const vecint & chosenindex, const vecstr arvalarray, const framestr & dataframe);

vecint getNIndex(const vecdouble & vec, int n);

void getallvariableStatisticsT(const vecstr & y, string methodname, int arity, const vecstr & classlabels, const vecstr & arvalarray, const framestr & dataframe, int beg, int end1, vecdouble & allstatcollector);

vecdouble getallvariableStatisticsFast(const vecstr & y, string methodname, int arity, const vecstr & classlabels, const vecint & diffindex, const framestr & dataframe);

void getallvariableStatisticsFastThread(const vecstr & y, string methodname, int arity, const vecstr & classlabels, const vecint & diffindex, const framestr & dataframe, int beg, int end1, vecdouble & allstatcollector);

vecint getDifferentialVariables(const framestr & dataframe, int index, const vecstr & arvalarray);

vecstr create_node(const vecstr & info, int size);
int retBestAttribute(const vecdouble &, const vecdouble &);
double getSignificance(const vecstr & bestattr, const vecstr & y, const vecstr & classlabels, string method);

#endif /* CPTreeMain_hpp */
