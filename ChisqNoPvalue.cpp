// ChisqNoPvalue.cpp -- Chisquare goodness of fit test without computing p-value
//
// Joe Song
//
// Created: April 7, 2014. Extracted from ChisqTests.cpp

#include <vector>
#include <cstdlib>
#include <iostream>

using namespace std;

void ChisquareTest1DNoPValue(const vector<int> & x_obs, 
                             const vector<double> & p_null, 
                             int K, double & chisq, 
                             size_t & df)
{
	int N = 0;

	chisq = 0;
    df = K-1;

	for(int k=0; k<K; k++) {
		N += x_obs[k];
	}
    
	if(N <= 0) {
		return;
	}
    
	for(int k=0; k<K; k++) {
		double x_exp = N * p_null[k];
		if(x_exp != 0) {
			chisq += (x_obs[k] - x_exp)*(x_obs[k] - x_exp)/ x_exp;
		} else if(x_obs[k] != 0) {
			cerr << "ERROR: expected is zero, but observed is not. Impossible!" << endl;
			exit(EXIT_FAILURE); 
		}
	}
    
	//legacy code
	//if(N % (int) pow(7.0, 3) == 0) {  // Quick hack to adjust for duplicated sample
	//	chisquare /= pow(7.0, 3);
	//	// cout << ".";
	//}
}
