//
//  utility.cpp
//  CPTree
//
//  Created by Sajal Kumar on 2/25/16.
//  Copyright © 2016 NMSUSongLab. All rights reserved.
//

#include "utility.hpp"
using namespace std;


/*Get prior probabilities*/
vecdouble getPrior(const vecstr & Y, const vecstr & classlabels)
{
    vecint freq=getFreq(Y, classlabels);
    vecdouble prior;
    for(int i=0;i<freq.size();i++)
    {
        prior.push_back((double)freq[i]/Y.size());
    }
    return prior;
}


/*Generates cost, given the current distribution of class labels: Helps in pruning*/
double costGen(const vecstr & y, const vecint & loss, const vecstr & classlabels)
{
    int numclass=(int)classlabels.size();
    vecint freq;
    double cost=0.0,temp=0.0;
    freq=getFreq(y,classlabels);
    for(int i=0;i<numclass;i++)
    {
        temp=0.0;
        for(int j=0;j<numclass;j++)
        {
            temp=temp+freq[j]*loss[i*numclass+j];
        }
        if(i==0||temp<cost)
            cost=temp;
    }
    return cost;
}

/* This function takes a double array and an item and returns an array of indexes
 whose value were less than the item */
vecint which_is_less(const vecdouble & arr, double item)
{
    vecint index;
    for(int i=0;i<arr.size();i++)
    {
        if(arr[i]<item)
        {
            index.push_back(i);
        }
    }
    return index;
}

/* This function takes a double array and an item and returns an array of indexes
 whose value were greater than the item */
vecint which_is_greater(const vecdouble & arr, double item)
{
    vecint index;
    for(int i=0;i<arr.size();i++)
    {
        if(arr[i]>item)
        {
            index.push_back(i);
        }
    }
    return index;
}



/*This function returns the unique elements in a given vector*/
vecstr retunique(const vecstr & vect)
{
    vecstr uni_vect;
    for(int i=0;i<vect.size();i++)
    {
       if(find(uni_vect.begin(), uni_vect.end(), vect[i])==uni_vect.end())
           uni_vect.push_back(vect[i]);
    }
    return uni_vect;
}

/*Converts valid string vector to double vector*/
vecdouble stringTodouble(const vecstr & vec)
{
    vecdouble newdata;
    for(int i=0;i<vec.size();i++)
    {
        newdata.push_back(stof(vec[i]));
    }
    return newdata;
}

/*converts a string frame to double frame*/
framedouble stringftodoublef(const framestr & tab)
{
    framedouble neodata;
    for(int i=0;i<tab.size();i++)
    {
        neodata.push_back(stringTodouble(tab[i]));
    }
    return neodata;
}

/*This function returns the relevant dataframe as guided by index*/
framestr selectOP(const framestr & dataframe, const vecint & index)
{
    framestr newdata;
    framestr revdata=Transposeframe(dataframe);
    for(int i=0;i<index.size();i++)
    {
        newdata.push_back(revdata[index[i]]);
    }
    revdata.clear();
    return Transposeframe(newdata);
}


/*This function returns the relevant vector as guided by index*/
vecdouble selectOP(const vecdouble & vec, const vecint & index)
{
    vecdouble newdata;
    for(int i=0;i<index.size();i++)
    {
        newdata.push_back(vec[index[i]]);
    }
    return newdata;
}

/*Given the the number of attributes and arity, it generates a sequence to access the dataframe*/
vecstr getGeneratedSequence(int size, int arity, string method)
{
    vecstr seq;
    if(arity==1)
    {
        for(int i=0;i<size;i++)
            seq.push_back(to_string(i)+","+to_string(i));
    }
    else
    {
        for(int i=0;i<size;i++)
            for(int j=i;j<size;j++)
                seq.push_back(to_string(i)+","+to_string(j));
    }
    return seq;
}

/*This function returns the relevant vector as guided by index*/
vecstr selectOP(const vecstr & vec, const vecint & index)
{
    vecstr newdata;
    for(int i=0;i<index.size();i++)
    {
        newdata.push_back(vec[index[i]]);
    }
    return newdata;
}


/*This function computes the frequency of given labels in a vector*/
vecint getFreq(const vecstr & y, const vecstr & labels)
{
    vecint freq;
    for(int i=0;i<labels.size();i++)
    {
        freq.push_back((int)count(y.begin(), y.end(), labels[i]));
    }
    return freq;
}

/* Merge two vectors (concatenate) completely*/
vecstr mergetwo(const vecstr & x1, const vecstr & x2,string sep)
{
    vecstr neodata;
    for(int i=0;i<x1.size();i++)
    {
        neodata.push_back(x1[i]+sep+x2[i]);
    }
    return neodata;
}

/* Split one vector that was merged previously*/
framestr Splitone(const vecstr & x1)
{
    framestr neodata;
    vecstr temp,temp1,temp2;
    for(int i=0;i<x1.size();i++)
    {
        boost::split(temp, x1[i], boost::is_any_of(","));
        temp1.push_back(temp[0]);
        temp2.push_back(temp[1]);
        temp.clear();
    }
    neodata.push_back(temp1);
    neodata.push_back(temp2);
    return neodata;
}

/*Form Combinatorial*/
framestr combinatorial(const framestr & dataframe)
{
    framestr neoframe;
    for(int i=0;i<dataframe.size()-1;i++)
    {
        for(int j=i;j<dataframe.size()-1;j++)
        {
            neoframe.push_back(mergetwo(dataframe[i], dataframe[j],","));
        }
    }
    neoframe.push_back(dataframe[dataframe.size()-1]);
    return neoframe;
}

/*Populates number between given range*/
vecint populate(int begin, int end)
{
    vecint res;
    for(int i=begin;i<end;i++)
    {
        res.push_back(i);
    }
    return res;
}

/*Converts valid int vector to string vector*/
vecstr intTostring(const vecint & vec)
{
    vecstr newdata;
    for(int i=0;i<vec.size();i++)
    {
        newdata.push_back(to_string(vec[i]));
    }
    return newdata;
}


/*Converts valid string vector to int vector*/
vecint stringToint(const vecstr & vec)
{
    vecint newdata;
    for(int i=0;i<vec.size();i++)
    {
        newdata.push_back(stoi(vec[i]));
    }
    return newdata;
}

/*return class labels along with their prior probabilities*/
string getlabeldistribtuion(const vecstr & y, const vecstr & classlabels)
{
    vecint freq=getFreq(y,classlabels);
    string str="(";
    for(int i=0;i<classlabels.size();i++)
    {
        if(i<classlabels.size()-1)
            str=str+"class:"+classlabels[i]+"_prior:"+to_string((float)freq[i]/y.size()).substr(0,5)+",";
        else
            str=str+"class:"+classlabels[i]+"_prior:"+to_string((float)freq[i]/y.size()).substr(0,5)+")";
    }
    return str;
}
