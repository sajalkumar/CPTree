//
//  utility.hpp
//  CPTree
//
//  Created by Sajal Kumar on 2/25/16.
//  Copyright © 2016 NMSUSongLab. All rights reserved.
//

#ifndef utility_hpp
#define utility_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <stack>

using namespace std;

typedef vector<string> vecstr;
typedef vector<vector<string>> framestr;

typedef vector<int> vecint;
typedef vector<vector<int>> frameint;

typedef vector<double> vecdouble;
typedef vector<vector<double>> framedouble;

/* This function formats the dataframe by columns so that accessing the attributes becomes easier*/
template <typename V>
vector<vector<V>> Transposeframe(const vector<vector<V>> & ref)
{
    vector<vector<V>> mod;
    vector<V> temp;
    for(int i=0;i<ref[0].size();i++)
    {
        for(int j=0;j<ref.size();j++)
        {
            temp.push_back(ref[j][i]);
        }
        mod.push_back(temp);
        temp.clear();
    }
    return mod;
}

/* This function accepts a frame of either integer or double along with an index that will be used for sorting. The entire frame is sorted
 according to one column of the frame*/
template <typename V>
vector<vector<V>> sortFrame(vector<vector<V>> & input, int index, string way)
{
    //This is really not the best way to do it.
    
    vector<V> indexpush;
    vector<vector<V>> output;
    for(int i=0;i<input[0].size();i++)
    {
        indexpush.push_back(index);
    }
    
    input.push_back(indexpush);
    indexpush.clear();
    
    input=Transposeframe(input);
    struct descending{
        bool operator()(vector<V> & a, vector<V> & b)
        {
            return (a[a[a.size()-1]] > b[b[b.size()-1]]);
        }
    }des;
    
    struct ascending{
        bool operator()(vector<V> & a, vector<V> & b)
        {
            return (a[a[a.size()-1]] < b[b[b.size()-1]]);
        }
    }as;
    
    if(way=="ascending")
    {
        std::sort(input.begin(), input.end(), as);
    } else {
        std::sort(input.begin(), input.end(), des);
    }
    //input=Transposeframe(input);
    
    for(int i=0;i<(input.size()-1);i++)
    {
        output.push_back(input[i]);
    }
    
    input.clear();
    
    return output;
    
}

/*This function combines all the vectors in a frame into one vector*/
template <typename V>
vector<V> combine(const vector<vector<V>> & tab)
{
    vector<V> res;
    for(int i=0;i<tab.size();i++)
    {
        for(int j=0;j<tab[i].size();j++)
        {
            res.push_back(tab[i][j]);
        }
    }
    return res;
}

vecdouble stringTodouble(const vecstr & vec);

framedouble stringftodoublef(const framestr & tab);

vecint which_is_less(const vecdouble &, double);

vecint which_is_greater(const vecdouble &, double);

vecstr retunique(const vecstr &);

vecstr getGeneratedSequence(int,int,string);

framestr selectOP(const framestr &, const vecint &);

vecdouble getPrior(const vecstr & Y, const vecstr & classlabels);

double costGen(const vecstr & y, const vecint & loss, const vecstr & classlabels);

vecdouble selectOP(const vecdouble &, const vecint &);

vecstr selectOP(const vecstr &, const vecint &);

/* This function takes any array and finds the minimum double inside it */
template <typename V>
V findmin(const vector<V> & arr)
{
    V min=INT16_MAX;
    for(size_t i=0;i<arr.size();i++)
    {
        if(arr[i]<=min)
            min=arr[i];
    }
    return min;
}

/*Trims a vector, removes 0 entries*/
template <typename V>
vector<V>  trim(const vector<V> & vec)
{
    vector<V>  result;
    for(int i=0;i<vec.size();i++)
    {
        if(vec[i]!=0)
            result.push_back(vec[i]);
    }
    return result;
}

/* This function takes any array and finds the maximum inside it */
template <typename V>
V findmax(const vector<V> & arr)
{
    V max=INT16_MIN;
    for(size_t i=0;i<arr.size();i++)
    {
        if(arr[i]>=max)
            max=arr[i];
    }
    return max;
}


/*This function deletes a entry from the given index of a dataframe*/
template <typename V>
vector<V> deleteOP(const vector<V> & dataframe, int index)
{
    vector<V> newframe;
    for(int i=0;i<dataframe.size();i++)
    {
        if(i!=index)
            newframe.push_back(dataframe[i]);
    }
    return newframe;
}

//This operator deletes a multiple columns from the given frame
template <typename V>
vector<V> deleteOPM(const vector<V> & dataframe, vecint index)
{
    if(index.size()==0)
        return dataframe;
    
    sort(index.begin(), index.end());
    vector<V> newframe;
    for(int i=0;i<dataframe.size();i++)
    {
        if(i!=index[0])
            newframe.push_back(dataframe[i]);
        else
            index.erase(index.begin());
    }
    return newframe;
}


vecint getFreq(const vecstr &, const vecstr &);

vecstr mergetwo(const vecstr &, const vecstr &,string);

framestr combinatorial(const framestr &);

string getlabeldistribtuion(const vecstr &, const vecstr &);

framestr Splitone(const vecstr &);

vecint populate(int,int);

vecstr intTostring(const vecint &);

vecint stringToint(const vecstr &);

/* This function takes a vector and an item and returns a vector of indexes
 whose value were equal to the item */
template <typename V>
vecint which_is_equal(const vector<V> & arr, V item)
{
    vecint index;
    for(int i=0;i<arr.size();i++)
    {
        if(arr[i]==item)
        {
            index.push_back(i);
        }
    }
    return index;
}


/*Prints a vector*/
template <typename V>
void printvector(const vector<V> & vec)
{
    for(int i=0;i<vec.size();i++)
    {
        cout<<vec[i]<<" ";
    }
    cout<<endl;
}

/*Prints a frame*/
template <typename F>
inline void printframe(const vector<vector<F>> & frame)
{
    for(int i=0;i<frame.size();i++)
    {
        for(int j=0;j<frame[i].size();j++)
        {
            cout<<frame[i][j]<<" ";
        }
        cout<<endl;
    }
}

#endif /* utility_hpp */
