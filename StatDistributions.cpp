//
//  StatDistributions.cpp
//  gln
//
//  Created by Joe Song on 11/2/11.
//  Copyright (c) 2011 New Mexico State University. All rights reserved.
//

#include "StatDistributions.h"

//Hua modified, replace all distribution computation into boost functions. //Hua modified Feb 6, 2015

double FPvalue(double Fstat, int df1, int df2)
{
    //Hua modified Feb 6, 2015
    fisher_f F(df1, df2);
    double pval = cdf(F, Fstat);
    return pval;
    ////
}

double ChisqPvalue(double x, size_t df)
{
    // Compute the quantity int_x^+infty [chisq(df, x)], which 
    // can be used as the p-value in a chisquare test 
    // assert(df >= 0 && x >= 0);
    // modified by Yang Zhang 11.2.2010 x may be a slightly smaller than zero due to numerical issues
    
    //Hua modified Feb 6, 2015
    assert(df >= 0);
    if(x <= 0)
        return 1;
    else
        return gamma_q(df/2.0, x/2.0);
    ////
}

double GammaPvalue(double x, double shape, double scale)
{
    //Hua modified Feb 6, 2015
    gamma_distribution<> G(shape, 1/scale);
    double pval = 1 - cdf(G, x);
    return pval;
    ////
}

double NormalPvalue(double x, double mu, double stdev, bool two_sided)
{
    //Hua modified Feb 6, 2015
    normal  N(mu, stdev);
    long double pval;
    if(two_sided) {
        if (x >= mu) {
            pval = 2.0 * (1.0 - cdf(N, x));
        } else {
            pval = 2.0 * cdf(N, x);
        }
    } else {
        pval = 1.0 - cdf(N, x);
    }
    return pval;
    ////
}

/* Using older version of Numerical Recipes
 
 extern "C" double gammq(double a, double x);
 extern "C" double gammp(double a, double x);
 
 double pchisq(int df, double x) 
 {
 // Compute the quantity int_-\infty^_x chisq(df, x), which 
 // can be used as the 1 - (p-value) in a chisquare test 
 //assert(df >= 0 && x >= 0);
 //modified by Yang Zhang 11.2.2010 x may be a slightly smaller than zero due to numerical issues
 assert(df >= 0);
 if(x <= 0)
 return 0;
 else
 return gammp(df/2.0, x/2.0);
 }
 
 double qchisq(int df, double x) 
 {
 // Compute the quantity int_-\infty^_x chisq(df, x), which 
 // can be used as the 1 - (p-value) in a chisquare test 
 //assert(df >= 0 && x >= 0);
 //modified by Yang Zhang 11.2.2010 x may be a slightly smaller than zero due to numerical issues
 assert(df >= 0);
 if(x <= 0)
 return 1;
 else
 return gammq(df/2.0, x/2.0);
 }
 */
