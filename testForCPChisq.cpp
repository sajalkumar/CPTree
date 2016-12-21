//
//  testForCPChisq.cpp
//  CPChisq
//
//  Created by Sajal Kumar on 3/10/16.
//  Copyright © 2016 NMSUSongLab. All rights reserved.
//

#include "testForCPChisq.h"
#include "CPChisq.h"
using namespace std;

void testCPChisq()
{
    vector< vector<double>  >  x_obs(2, vector<double> (4));
    vector< vector<double>  >  y_obs(2, vector<double> (4));
    vector<vector<vector<double> > >  tables;
    vector<double>  res;
    
    
    x_obs[0][0] = 1, x_obs[0][1] = 3, x_obs[0][2] = 2, x_obs[0][3] = 4;
    x_obs[1][0] = 10, x_obs[1][1] = 3, x_obs[1][2] = 20, x_obs[1][3] = 4;
    
    y_obs[0][0] = 1, y_obs[0][1] = 3, y_obs[0][2] = 2, y_obs[0][3] = 4;
    y_obs[1][0] = 10, y_obs[1][1] = 3, y_obs[1][2] = 20, y_obs[1][3] = 4;
    
    tables.push_back(x_obs);
    tables.push_back(y_obs);
    
    res=cpx2(tables);
    cout<<"Test 1"<<endl;
    assert(res[0]==0.0 && res[1]==1.0);
    cout<<"Stat Expected = 0.0, got "<<res[0]<<" Pvalue expected = 1, got "<<res[1]<<endl;
    
    vector< vector<double>  >  x1_obs(4, vector<double> (4));
    
    x1_obs[0][0] = 0, x1_obs[0][1] = 0, x1_obs[0][2] = 0, x1_obs[0][3] = 0;
    x1_obs[1][0] = 0, x1_obs[1][1] = 0, x1_obs[1][2] = 0, x1_obs[1][3] = 0;
    x1_obs[2][0] = 0, x1_obs[2][1] = 0, x1_obs[2][2] = 0, x1_obs[2][3] = 0;
    x1_obs[3][0] = 0, x1_obs[3][1] = 0, x1_obs[3][2] = 0, x1_obs[3][3] = 0;
    
    tables.clear();
    tables.push_back(x1_obs);
    tables.push_back(x1_obs);
    
    res=cpx2(tables);
    cout<<"Test 2"<<endl;
    assert(res[0]==0.0 && res[1]==1.0);
    cout<<"Stat Expected = 0.0, got "<<res[0]<<" Pvalue expected = 1, got "<<res[1]<<endl;
    
    vector< vector<double>  >  x2_obs(3, vector<double> (3));
    
    x2_obs[0][0] = 4, x2_obs[0][1] = 0, x2_obs[0][2] = 0;
    x2_obs[1][0] = 0, x2_obs[1][1] = 4, x2_obs[1][2] = 0;
    x2_obs[2][0] = 0, x2_obs[2][1] = 0, x2_obs[2][2] = 4;
    
    tables.clear();
    tables.push_back(x2_obs);
    tables.push_back(x2_obs);
    
    res=cpx2(tables);
    cout<<"Test 3"<<endl;
    assert(res[0]==0.0 && res[1]==1.0);
    cout<<"Stat Expected = 0.0, got "<<res[0]<<" Pvalue expected = 1, got "<<res[1]<<endl;

    
    vector< vector<double>  >  x3_obs(3, vector<double> (3));
    
    x3_obs[0][0] = 0, x3_obs[0][1] = 4, x3_obs[0][2] = 4;
    x3_obs[1][0] = 4, x3_obs[1][1] = 0, x3_obs[1][2] = 4;
    x3_obs[2][0] = 4, x3_obs[2][1] = 4, x3_obs[2][2] = 0;
    
    tables.clear();
    tables.push_back(x2_obs);
    tables.push_back(x3_obs);
    
    res=cpx2(tables);
    cout<<"Test 4"<<endl;
    assert(res[0]==36.0 && res[1]>=0.00000028930);
    cout<<"Stat Expected = 36.0, got "<<res[0]<<" Pvalue expected = 2.8937e-07, got "<<res[1]<<endl;
    
    vector< vector<double>  >  x4_obs(3, vector<double> (3));
    
    x3_obs[0][0] = 4, x3_obs[0][1] = 0, x3_obs[0][2] = 4;
    x3_obs[1][0] = 0, x3_obs[1][1] = 4, x3_obs[1][2] = 0;
    x3_obs[2][0] = 1, x3_obs[2][1] = 0, x3_obs[2][2] = 1;
    
    x2_obs[0][0] = 4, x2_obs[0][1] = 0, x2_obs[0][2] = 1;
    x2_obs[1][0] = 0, x2_obs[1][1] = 4, x2_obs[1][2] = 0;
    x2_obs[2][0] = 4, x2_obs[2][1] = 0, x2_obs[2][2] = 1;
    
    x4_obs[0][0] = 1, x4_obs[0][1] = 0, x4_obs[0][2] = 1;
    x4_obs[1][0] = 4, x4_obs[1][1] = 0, x4_obs[1][2] = 4;
    x4_obs[2][0] = 0, x4_obs[2][1] = 4, x4_obs[2][2] = 0;
    
    
    tables.clear();
    tables.push_back(x2_obs);
    tables.push_back(x3_obs);
    tables.push_back(x4_obs);
    
    res=cpx2(tables);
    cout<<"Test 5"<<endl;
    assert(res[0]==42.0 && res[1]>=0.0000013542);
    cout<<"Stat Expected = 42.0, got "<<res[0]<<" Pvalue expected = 1.35425e-06, got "<<res[1]<<endl;
    
    cout<<"All Test Passed!!"<<endl;
    
}

