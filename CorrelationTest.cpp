//
//  CorrelationTest.cpp
//  CPTree
//
//  Created by Sajal Kumar on 5/16/16.
//  Copyright © 2016 NMSUSongLab. All rights reserved.
//

#include "CorrelationTest.hpp"

void corTest(const framedouble & tab, int beg, int end, vecint & res)
{
    double corval;
    for(int i=beg;i<=end;i++)
    {
        for(int j=i+1;j<tab.size();j++)
        {
            double * work=new double[2*tab[1].size()];
            
            corval=gsl_stats_spearman(&tab[i][0], 1, &tab[j][0], 1, tab[i].size(), work);
            delete[] work;
            if(corval>=0.8||corval<=-0.8)
            {
                res.push_back(i);
                break;
            }
        }
    }
}

vecint corTestMain(const framestr & tab)
{
    
    framedouble neotab=stringftodoublef(tab);
    int numthreads=boost::thread::hardware_concurrency()-1;
    
    vecint res;
    
    //the number of permutations would be (n*(n+1)/2 - selfcomparisons)
    long perm_size=((long)(tab.size())*(tab.size()+1)/2)-neotab.size();
    
    long currentmax=(neotab.size()-1),eqval=(long)perm_size/numthreads, currentsum=0, currentbeg=0;
    
    if(perm_size<numthreads)
        numthreads=(int)perm_size;
    
    vecint beg(numthreads), end1(numthreads);
    
    frameint table(numthreads);
    
    boost::thread_group threads;
    
    for(int i=0;i<numthreads;i++)
    {
        beg[i]=(int)currentbeg;
        
        currentsum=currentmax;
        
        while(currentsum<=eqval&&currentmax>0)
        {
            currentmax--;
            currentbeg++;
            currentsum=currentsum+currentmax;
        }
    
        end1[i]=(int)currentbeg;
        
        currentmax--;
        currentbeg++;
        
        threads.create_thread(boost::bind(&corTest,boost::cref(neotab),beg[i],end1[i],boost::ref(table[i])));
    }
    
    
    
    threads.join_all();
    
    res=combine<int>(table);
    
    return res;
}



