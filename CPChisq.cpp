//
//  CPChisq.cpp
//  CPChisq
//
//  Created by Sajal Kumar on 3/3/16.
//  Copyright © 2016 NMSUSongLab. All rights reserved.
//

#include "CPChisq.h"

/*Returns the Comparative Chisq and the respective pvalue for a list of contigency tables*/
vector<double>  cpx2(const vector<vector<vector< double> > > & tables)
{
    double heterochisq=0.0,poolchisq=0.0,totalchisq=0.0,pval=1.0;
    vector<double>  res;
    vector<vector< double> >  pooled=getpooled(tables[0], tables[1]);
    double pooledsum=0;
    size_t df=0;
    vector<double>  columnsum,rowsum;
    
    for(int i=2;i<tables.size();i++)
    {
        pooled=getpooled(pooled, tables[i]);
    }
    
    vector<vector<double> >  pooledexpected=getExpected(pooled);
    poolchisq=chisqst(pooled, pooledexpected);
    pooledsum=getSum(pooled);
    
    columnsum=getColumnSum(pooled);
    columnsum=trim(columnsum);
    
    rowsum=getRowSum(pooled);
    rowsum=trim(rowsum);
    
    if(pooledsum>  0)
    {
        vector<vector<double>  >   expected;
        for(int i=0;i<tables.size();i++)
        {
            expected=getExpectedRef(tables[i],pooledexpected,pooledsum);
            totalchisq=totalchisq+chisqst(tables[i], expected);
            expected.clear();
        }
        if(poolchisq==0)
        {
            heterochisq=totalchisq;
            if(tables.size()>=2&&columnsum.size()>=2)
            {
                df=(tables.size()-1)*(columnsum.size()-1);
                pval=ChisqPvalue(heterochisq, df);
            }
        }
        else
        {
            heterochisq=totalchisq-poolchisq;
            if(tables.size()>=2 && columnsum.size()>=2 && rowsum.size()>=2)
            {
                df=(tables.size()-1)*(columnsum.size()-1)*(rowsum.size()-1);
                pval=ChisqPvalue(heterochisq, df);
            }
        }
    }
    res.push_back(heterochisq);
    res.push_back(pval);
    return res;
}


/*Constructs the pooled table, given two tables of with similar dimensions*/
vector<vector<double> >  getpooled(const vector<vector<double> > & t1,const vector<vector<double> > & t2)
{
    vector<vector<double> >  pooled;
    vector<double>  temp; //A temporary variable to store intermediary results
    for(int i=0;i<t1.size();i++)
    {
        for(int j=0;j<t1[i].size();j++)
        {
            temp.push_back(t1[i][j]+t2[i][j]);
        }
        pooled.push_back(temp);
        temp.clear();
    }
    return pooled;
}


/*Returns the chisq statistic*/
double chisqst(const vector<vector<double> > & obs, const vector<vector<double> > & expected)
{
    
    double chisqval=0.0;
    for(int i=0;i<obs.size();i++)
    {
        for(int j=0;j<obs[i].size();j++)
        {
            if(expected[i][j]!=0)
                chisqval=chisqval+(pow(obs[i][j]-expected[i][j],2)/expected[i][j]);
        }
    }
    return chisqval;
}

/*Returns the expected contigency table*/
vector<vector<double> >  getExpected(const vector<vector<double> > & table)
{
    vector<vector<double> >  expected;
    vector<double>  row_sum=getRowSum(table);
    vector<double>  column_sum=getColumnSum(table);
    vector<double>  temp; //A temporary variable to store intermediary results
    
    double sum=0;
    for(int i=0;i<row_sum.size();i++)
    {
        sum=sum+row_sum[i];
    }
    
    for(int i=0;i<row_sum.size();i++)
    {
        for(int j=0;j<column_sum.size();j++)
        {
            temp.push_back((double)(row_sum[i]*column_sum[j])/sum);
        }
        expected.push_back(temp);
        temp.clear();
    }
    return expected;
}

/* Returns the row sum of the contigency table*/
vector<double>  getRowSum(const vector<vector<double> > & table)
{
    vector<double>  rowsum;
    double sum;
    for(int i=0;i<table.size();i++)
    {
        sum=0;
        for(int j=0;j<table[i].size();j++)
        {
            sum=sum+table[i][j];
        }
        rowsum.push_back(sum);
    }
    return rowsum;
}


/*Returns the column sum of the contigency table*/
vector<double>  getColumnSum(const vector<vector<double> > & table)
{
    vector<double>  columnsum;
    double sum;
    for(int i=0;i<table[0].size();i++)
    {
        sum=0;
        for(int j=0;j<table.size();j++)
        {
            sum=sum+table[j][i];
        }
        columnsum.push_back(sum);
    }
    return columnsum;
}


/*Returns the overall sum of a contigency table*/
double getSum(const vector<vector<double> > & table)
{
    double sum=0;
    vector<double>  rowsum=getRowSum(table);
    for(int i=0;i<rowsum.size();i++)
    {
        sum=sum+rowsum[i];
    }
    return sum;
}

/*Returns an expected contigency table based on pooled table*/
vector<vector<double> >  getExpectedRef(const vector<vector<double> > & table, const vector<vector<double> > & pooledexpected,double pooledsum)
{
    vector<vector<double> >  expected;
    vector<double>  row_sum=getRowSum(table);
    vector<double>  column_sum=getColumnSum(table);
    vector<double>  temp; //A temporary variable to store intermediary results
    double sum=0;
    
    for(int i=0;i<row_sum.size();i++)
    {
        sum=sum+row_sum[i];
    }
    
    for(int i=0;i<row_sum.size();i++)
    {
        for(int j=0;j<column_sum.size();j++)
        {
            temp.push_back((double)(pooledexpected[i][j]*sum/pooledsum));
        }
        expected.push_back(temp);
        temp.clear();
    }
    return expected;
}




