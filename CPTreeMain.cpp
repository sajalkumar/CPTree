//
//  CPTreeMain.cpp
//  CPTree
//
//  Created by Sajal Kumar on 2/26/16.
//  Copyright © 2016 NMSUSongLab. All rights reserved.
//

#include "CPTreeMain.hpp"
using namespace std;

/*No loss matrix given, create one*/
CPTree::CPTree(const vecstr & y, int ncols)
{
    classlabels=retunique(y);
    int size=(int)classlabels.size()*(int)classlabels.size();
    vecstr temp;
    for(int i=0;i<size;i++)
    {
        if(i%(classlabels.size()+1)==0)
            loss.push_back(1);
        else
            loss.push_back(0);
    }
    
    for(int i=0;i<=ncols;i++)
    {
        if(i<ncols)
            columnnames.push_back("Attr"+to_string(i+1));
        else
            columnnames.push_back("ClassLabels");
    }
    temp.push_back("TYPE_OF_NODE");
    temp.push_back("PARENT");
    temp.push_back("UNIQUE_ID(PARENT_NAME::HEIGHT::EXPANSION_ORDER::ATTRIBUTE_CHOSEN");
    temp.push_back("SUBSET");
    temp.push_back("ATTRIBUTE_NAME");
    temp.push_back("HEIGHT");
    temp.push_back("MOST_PROBABLE_LABEL");
    temp.push_back("DATA_SIZE_NROWS");
    temp.push_back("PRIOR_INFO");
    temp.push_back("PVALUE");
    treestruct.clear();
    treestruct.push_back(temp);
    temp.clear();
    currentiterator.clear();
}

/*Loss matrix given*/
CPTree::CPTree(const vecstr & y, int  ncols, const vecint & loss)
{
    classlabels=retunique(y);
    this->loss=loss;
    vecstr temp;
    for(int i=0;i<=ncols;i++)
    {
        if(i<ncols)
            columnnames.push_back("Attr"+to_string(i+1));
        else
            columnnames.push_back("ClassLabels");
    }
    temp.push_back("TYPE_OF_NODE");
    temp.push_back("PARENT");
    temp.push_back("UNIQUE_ID(PARENT_NAME::HEIGHT::EXPANSION_ORDER::ATTRIBUTE_CHOSEN");
    temp.push_back("SUBSET");
    temp.push_back("ATTRIBUTE_NAME");
    temp.push_back("HEIGHT");
    temp.push_back("MOST_PROBABLE_LABEL");
    temp.push_back("DATA_SIZE_NROWS");
    temp.push_back("PRIOR_INFO");
    temp.push_back("PVALUE");
    treestruct.clear();
    treestruct.push_back(temp);
    temp.clear();
    currentiterator.clear();
}


vecstr CPTree::getClassLabels()
{
    return classlabels;
}


vecint CPTree::getLossMatrix()
{
    return loss;
}


vecstr CPTree::getColumnNames()
{
    return columnnames;
}


framestr CPTree::getTreeStruct()
{
    return treestruct;
}

//Iterative Version
void CPTree::CPTreeMainIterative(framestr dataframe, string methodname, int arity, double alpha)
{
    stack<vecstr> nodecollector;
    stack<frameint> indextracker;
    vecdouble tempres;
    double bestpval, beststat;
    vecstr currentnode, newnode, columnnames=getColumnNames(),temp2,info;
    frameint currentindex, newindex;
    vecint freq=getFreq(dataframe[dataframe.size()-1], getClassLabels()),temp;
    vecdouble allstatcollector;
    framedouble allstats;
    int n_size=10;
    string tempvar="";
    int size_of_node=10, iindex=0, jindex=0;
    info.reserve(10);
    
    //Add index to Dataframe
    dataframe.push_back(intTostring(populate(0, (int)Transposeframe(dataframe).size())));
    framestr tempframe,referencedata=dataframe;
    
    //Get the sequence initially
    vecstr arvalarray=intTostring(populate(0, (int)(dataframe.size()-2))),refarvalarray=arvalarray;
    
    //Node format : {type, parent, unique_id, subset, attribute_name, most_frequent_label, size, label_distribution}
    
    tempvar=tempvar+"Root"+"#"+"NILL"+"#"+to_string(0)+"#"+"NILL"+"#"+"NILL"+"#"+to_string(0)+"#"+selectOP(getClassLabels(),which_is_equal(freq, findmax(freq)))[0]+"#"+to_string(Transposeframe(dataframe).size())+"#"+getlabeldistribtuion(dataframe[dataframe.size()-2],getClassLabels())+"#"+"1";
    
    boost::split(info, tempvar, boost::is_any_of("#"));
    currentnode=create_node(info,size_of_node);
    
    //push the root
    nodecollector.push(currentnode);
    currentnode.clear();

    
    //Push the rows to consider
    currentindex.push_back(stringToint(dataframe[dataframe.size()-1]));
    
    //Push the columns to delete
    temp.push_back(-1);
    currentindex.push_back(temp);
    temp.clear();
    
    //Push the index status for root
    indextracker.push(currentindex);
    currentindex.clear();
    
    
    while(!nodecollector.empty())
    {
        currentindex=indextracker.top();
        
        //Get the data ready to process
        dataframe=referencedata;
        columnnames=getColumnNames();
        arvalarray=refarvalarray;
        
        //Choosing the respected rows
        dataframe=selectOP(dataframe,currentindex[0]);
        if(currentindex[1][0]!=-1)
            arvalarray=deleteOPM(arvalarray, currentindex[1]);
        
        if(arvalarray.empty())//||stoi(nodecollector.top()[5])>=1)
        {
            currentnode=nodecollector.top();
            currentindex=indextracker.top();
            if(currentnode[0]!="Root")
            {
                currentnode.at(0)="Leaf";
            }
            currentnode.at(9)=1;
            nodecollector.pop();
            indextracker.pop();
            treestruct.push_back(currentnode);
            currentiterator.push_back(currentindex);
        }
        else
        {
            
            //allstatcollector=getallvariableStatistics(dataframe[dataframe.size()-2],methodname,1,getClassLabels(),arvalarray,dataframe);
            allstats=getAllVariableStats1D(dataframe[dataframe.size()-2], methodname, getClassLabels(), arvalarray, dataframe);
            
            if(arvalarray.size()!=1)
            {
                if(methodname!="entropy" && methodname!="gini")
                {
                    allstats=sortFrame(allstats, 0, "descending");
                } else {
                    allstats=sortFrame(allstats, 0, "ascending");
                }
            }
            
            //allstats=Transposeframe(allstats);
            
            for(int i=0;i<allstats[allstats.size()-1].size();i++)
            {
                allstatcollector.push_back(allstats[allstats.size()-1][i]);
            }
            
            bestpval=allstatcollector[0];
            beststat=allstatcollector[1];
            iindex=allstatcollector[2];
            jindex=allstatcollector[2];
            
            if(arity!=1)
            {
                allstats=Transposeframe(allstats);
                if(methodname=="funchisqfast")
                {
                    
                }
                
                
                
                
                
//                vecint diffindex=getDifferentialVariables(dataframe, iindex, arvalarray);
//                
//                diffindex.push_back(iindex);
//                
//                allstatcollector=getallvariableStatisticsFast(dataframe[dataframe.size()-2],methodname,arity,getClassLabels(),diffindex,dataframe);
                
                
                vecint diffindex;
                if(allstats.size()>1)
                    diffindex=getNIndex(allstats[2], n_size);
                else
                    diffindex.push_back(stoi(arvalarray[0]));

//                if(arvalarray.size()<n_size)
//                    n_size=(int)arvalarray.size();
//                
//                for(int i=0;i<n_size;i++)
//                {
//                    diffindex.push_back(stoi(arvalarray[i]));
//                }
                
                allstatcollector=getAllVariableStatsLinear(dataframe[dataframe.size()-2], methodname, getClassLabels(), arity, diffindex, arvalarray, dataframe);
                
                
                if(methodname!="entropy" && methodname!="gini")
                {
                    if(bestpval>=allstatcollector[0])
                    {
                        if(bestpval>allstatcollector[0])
                        {
                            bestpval=allstatcollector[0];
                            beststat=allstatcollector[1];
                            iindex=(int)allstatcollector[2];
                            jindex=(int)allstatcollector[3];
                        } else
                        {
                            if(beststat<allstatcollector[1])
                            {
                                bestpval=allstatcollector[0];
                                beststat=allstatcollector[1];
                                iindex=(int)allstatcollector[2];
                                jindex=(int)allstatcollector[3];
                            }
                        }
                        
                    }
                } else {
                    
                    if(beststat<allstatcollector[1])
                    {
                        bestpval=allstatcollector[0];
                        beststat=allstatcollector[1];
                        iindex=(int)allstatcollector[2];
                        jindex=(int)allstatcollector[3];
                    }
                }
                
            }
            
            
            //cleaning
            allstatcollector.clear();
            allstats.clear();
           
            vecstr best_attribute_column;
            string column;
            
            if(iindex==jindex)
            {
                column=columnnames[iindex];
                best_attribute_column=dataframe[iindex];
            }
            else
            {
                column=columnnames[iindex]+"~"+columnnames[jindex];
                best_attribute_column=mergetwo(dataframe[iindex], dataframe[jindex], ",");
            }
            
            //cout<<column<<endl;
            double pvalue=1;
            if(methodname == "chisq"||methodname=="funchisqall"||methodname=="gini"||methodname=="entropy")
                pvalue=getSignificance(best_attribute_column,dataframe[dataframe.size()-2],getClassLabels(),"chisq");
            else
                pvalue=getSignificance(best_attribute_column,dataframe[dataframe.size()-2],getClassLabels(),"funchisq");
            
            //Pruning: Don't split insignificant nodes, if the node is signifcant we would go for the split
            if(pvalue<=alpha)
            {
                //Pop the top node, update it and push it back
                currentnode=nodecollector.top();
                
                //Concatenate the name
                currentnode.at(2) += "::"+column;
                currentnode.at(4)=column;
                currentnode.at(9)=to_string(pvalue);
                
                nodecollector.pop();
                nodecollector.push(currentnode);
                
                vecstr unval=retunique(best_attribute_column);
                currentnode=nodecollector.top();
                currentindex=indextracker.top();
                
                //This node is now done
                nodecollector.pop();
                indextracker.pop();
                
                treestruct.push_back(currentnode);
                currentiterator.push_back(currentindex);
                for(int i=0;i<unval.size();i++)
                {
                    vecint ind=which_is_equal(best_attribute_column, unval[i]);
                    framestr neoframe=selectOP(dataframe, ind);
                    
                    //New node created
                    newnode.clear();
                        
                    //New index node
                    newindex.clear();
                        
                    freq=getFreq(neoframe[neoframe.size()-2], getClassLabels());
                        
                    tempvar="";
                    tempvar=tempvar+"Internal"+"#"+currentnode[2]+"#"+currentnode[2]+"::"+to_string(stoi(currentnode[5])+1)+"::"+to_string(i)+"#"+unval[i]+"#"+"NILL"+"#"+to_string(stoi(currentnode[5])+1)+"#"+selectOP(getClassLabels(),which_is_equal(freq, findmax(freq)))[0]+"#"+to_string(Transposeframe(neoframe).size())+"#"+getlabeldistribtuion(neoframe[neoframe.size()-2], getClassLabels())+"#"+"1";
                    info.clear();
                    boost::split(info, tempvar, boost::is_any_of("#"));
                        
                    newnode=create_node(info, size_of_node);
                        
                    //push the node
                    nodecollector.push(newnode);
                        
                    //Push the rows to consider
                    newindex.push_back(stringToint(neoframe[neoframe.size()-1]));
                    
                    //Push the columns to delete
                    if(currentindex[1][0]==-1)
                    {
                        temp.clear();
                        temp.push_back(iindex);
                        if(iindex!=jindex)
                            temp.push_back(jindex);
                        newindex.push_back(temp);
                    }
                    
                    else
                    {
                        newindex.push_back(currentindex[1]);
                        newindex[1].push_back(iindex);
                        if(iindex!=jindex)
                            newindex[1].push_back(jindex);
                    }
                        
                    //Push the index status for this node
                    indextracker.push(newindex);
                }
                
            }
            else //The node was insignificant, make it a leaf node
            {
                currentnode=nodecollector.top();
                currentindex=indextracker.top();
                if(currentnode[0]!="Root")
                {
                    currentnode.at(0)="Leaf";
                }
                currentnode.at(9)=to_string(pvalue);
                nodecollector.pop();
                indextracker.pop();
                treestruct.push_back(currentnode);
                currentiterator.push_back(currentindex);
            }
        }
    }
}


/*This function is a non-parallel statistics collector. It strictly requires the arity to be 1*/
framedouble getAllVariableStats1D(const vecstr & y, string methodname, const vecstr & classlabels, const vecstr arvalarray, const framestr & dataframe)
{
    framestr tempframe;
    vecdouble tempres;
    vecdouble statcollect1D;
    vecdouble pvalcollect1D;
    vecdouble indexcollect1D;
    framedouble allstatcollect1D;
    for(int i=0;i<arvalarray.size();i++)
    {
        tempframe.clear();
        tempres.clear();
        tempframe.push_back(dataframe[stoi(arvalarray[i])]);
        tempframe.push_back(dataframe[stoi(arvalarray[i])]);
        tempres=method(tempframe, y, classlabels, methodname, 1, 1);
        statcollect1D.push_back(tempres[0]);
        pvalcollect1D.push_back(tempres[1]);
        indexcollect1D.push_back(stod(arvalarray[i]));
    }
    allstatcollect1D.push_back(pvalcollect1D);
    pvalcollect1D.clear();
    allstatcollect1D.push_back(statcollect1D);
    statcollect1D.clear();
    allstatcollect1D.push_back(indexcollect1D);
    indexcollect1D.clear();
    return allstatcollect1D;
}

/*This function is a non-parallel statistics collector.*/
vecdouble getAllVariableStatsLinear(const vecstr & y, string methodname, const vecstr & classlabels, int arity, const vecint & chosenindex, const vecstr arvalarray, const framestr & dataframe)
{
    framestr tempframe;
    vecdouble tempres;
    vecdouble allstatcollector;
    int vi,vj,iindex=0,jindex=0;
    double beststat=0,bestpval;
    if(methodname!="entropy" && methodname!="gini")
        bestpval=1;
    else
        bestpval=0;
    for(int i=0;i<chosenindex.size();i++)
    {
        for(int j=0;j<arvalarray.size();j++)
        {
            tempframe.clear();
            tempres.clear();
            vi=chosenindex[i];
            vj=stoi(arvalarray[j]);
            tempframe.push_back(dataframe[vi]);
            tempframe.push_back(dataframe[vj]);
            if(vi==vj)
                tempres=method(tempframe, y, classlabels, methodname, arity, 1);
            else
                tempres=method(tempframe, y, classlabels, methodname, arity, 2);
            
            if(methodname!="entropy" && methodname!="gini")
            {
                if(bestpval>tempres[1])
                {
                    bestpval=tempres[1];
                    beststat=tempres[0];
                    iindex=vi;
                    jindex=vj;
                }
                
                if(bestpval == tempres[1])
                {
                    if(beststat<tempres[0])
                    {
                        bestpval=tempres[1];
                        beststat=tempres[0];
                        iindex=vi;
                        jindex=vj;
                    }
                }
            } else {
                
                if(bestpval<tempres[1])
                {
                    bestpval=tempres[1];
                    beststat=tempres[0];
                    iindex=vi;
                    jindex=vj;
                }
            }
            
        }
    }
    
    allstatcollector.push_back(bestpval);
    allstatcollector.push_back(beststat);
    allstatcollector.push_back(iindex);
    allstatcollector.push_back(jindex);
    return allstatcollector;
}

/*This function extracts the first n indexes from the supplied vector of indexes*/
vecint getNIndex(const vecdouble & vec, int n)
{
    vecint index;
    if(n>vec.size())
        n=(int)vec.size();
    for(int i=0;i<n;i++)
    {
        index.push_back((int)vec[i]);
    }
    return index;
}








/*This function collects the best pvalue, statvalue and respective i and j index, guided by the differential variables-Generates Thread*/
vecdouble getallvariableStatisticsFast(const vecstr & y, string methodname, int arity, const vecstr & classlabels, const vecint & diffindex, const framestr & dataframe)
{
    int numthreads=boost::thread::hardware_concurrency()-1, bestindex=0;
    
    double pval,st;
    
    
    //    if(arvalarray.size()==1)
    //    {
    //        vecstr res;
    //        getallvariableStatisticsT(y, methodname, arity, classlabels, arvalarray, dataframe, 0, 0, res);
    //        return res;
    //    }
    
    //the number of permutations would be (n*(n+1)/2)
    long perm_size=((long)(diffindex.size())*(diffindex.size()+1)/2);
    
    long currentmax=(diffindex.size()-1),eqval=(long)perm_size/numthreads, currentsum=0, currentbeg=0;
    
    if(perm_size<numthreads)
        numthreads=(int)perm_size;
    
    vecint beg(numthreads), end1(numthreads);
    
    framedouble table(numthreads);
    
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
        
        threads.create_thread(boost::bind(&getallvariableStatisticsFastThread,boost::cref(y),methodname,arity,boost::cref(classlabels),
                                          boost::cref(diffindex),boost::cref(dataframe),beg[i],end1[i],boost::ref(table[i])));
    }
    
    threads.join_all();
    
    pval=table[0][0];
    st=table[0][1];
    
    for(int i=1;i<table.size();i++)
    {
        if(methodname!="entropy" && methodname!="gini")
        {
            if(pval>=table[i][0])
            {
                if(pval>table[i][0])
                {
                    pval=table[i][0];
                    st=table[i][1];
                    bestindex=i;
                } else
                {
                    if(st<table[i][1])
                    {
                        pval=table[i][0];
                        st=table[i][1];
                        bestindex=i;
                    }
                }
                
            }
        } else {
            if(pval<table[i][0])
            {
                pval=table[i][0];
                st=table[i][1];
                bestindex=i;
            }
        }
    }
    
    vecdouble entry;
    for(int i=0;i<table[bestindex].size();i++)
    {
        entry.push_back(table[bestindex][i]);
    }
    
    return entry;
}

/*This function collects the best pvalue, statvalue and respective i and j index, guided by the differential variables-Each Thread*/
void getallvariableStatisticsFastThread(const vecstr & y, string methodname, int arity, const vecstr & classlabels, const vecint & diffindex, const framestr & dataframe, int beg, int end1, vecdouble & allstatcollector)
{
    framestr tempframe;
    vecstr temp;
    vecdouble tempres;
    
    double bestpval, beststat=0;
    int iindex=0, jindex=0, end=(int)diffindex.size()-1;
    
    if(methodname!="entropy" && methodname!="gini")
        bestpval=1;
    else
        bestpval=0;
    
    for(int i=beg;i<=end1;i++)
    {
        for(int j=i;j<=end;j++)
        {
            tempframe.clear();
            tempframe.push_back(dataframe[diffindex[i]]);
            tempframe.push_back(dataframe[diffindex[j]]);
            if(i==j)
                tempres=method(tempframe, y, classlabels, methodname, arity, 1);
            else
                tempres=method(tempframe, y, classlabels, methodname, arity, 2);
            
            if(methodname!="entropy" && methodname!="gini")
            {
                if(bestpval>tempres[1])
                {
                    bestpval=tempres[1];
                    beststat=tempres[0];
                    iindex=i;
                    jindex=j;
                }
                
                if(bestpval == tempres[1])
                {
                    if(beststat<tempres[0])
                    {
                        bestpval=tempres[1];
                        beststat=tempres[0];
                        iindex=i;
                        jindex=j;
                    }
                }
            } else {
                
                if(bestpval<tempres[1])
                {
                    bestpval=tempres[1];
                    beststat=tempres[0];
                    iindex=i;
                    jindex=j;
                }
            }
            
        }
    }
    
    allstatcollector.push_back(bestpval);
    allstatcollector.push_back(beststat);
    allstatcollector.push_back(iindex);
    allstatcollector.push_back(jindex);
}



/*This function collects the best pvalue, statvalue and respective i and j index, guided by the sequence arvalarray-Each Thread*/
void getallvariableStatisticsT(const vecstr & y, string methodname, int arity, const vecstr & classlabels, const vecstr & arvalarray, const framestr & dataframe, int beg, int end1, vecdouble & allstatcollector)
{
    framestr tempframe;
    vecstr temp;
    vecdouble tempres;
    
    double bestpval, beststat=0;
    int iindex=0, jindex=0, end=(int)arvalarray.size()-1;
    
    if(arity==1)
        end=0;
    
    if(methodname!="entropy" && methodname!="gini")
        bestpval=1;
    else
        bestpval=0;
    
    for(int i=beg;i<=end1;i++)
    {
        for(int j=i;j<=end;j++)
        {
            tempframe.clear();
            tempframe.push_back(dataframe[stoi(arvalarray[i])]);
            tempframe.push_back(dataframe[stoi(arvalarray[j])]);
            if(i==j)
                tempres=method(tempframe, y, classlabels, methodname, arity, 1);
            else
                tempres=method(tempframe, y, classlabels, methodname, arity, 2);
            
            if(methodname!="entropy" && methodname!="gini")
            {
                if(bestpval>tempres[1])
                {
                    bestpval=tempres[1];
                    beststat=tempres[0];
                    iindex=i;
                    jindex=j;
                }
                
                if(bestpval == tempres[1])
                {
                    if(beststat<tempres[0])
                    {
                        bestpval=tempres[1];
                        beststat=tempres[0];
                        iindex=i;
                        jindex=j;
                    }
                }
            } else {
                
                if(bestpval<tempres[1])
                {
                    bestpval=tempres[1];
                    beststat=tempres[0];
                    iindex=i;
                    jindex=j;
                }
            }
            
        }
    }
    
    allstatcollector.push_back(bestpval);
    allstatcollector.push_back(beststat);
    allstatcollector.push_back(iindex);
    allstatcollector.push_back(jindex);
}

/*This function collects the best pvalue, statvalue and respective i and j index, guided by the sequence arvalarray-Generates Thread*/
vecdouble getallvariableStatistics(const vecstr & y, string methodname, int arity, const vecstr & classlabels, const vecstr & arvalarray, const framestr & dataframe)
{
    int numthreads=boost::thread::hardware_concurrency()-1, bestindex=0;
    
    double pval,st;
    
    
//    if(arvalarray.size()==1)
//    {
//        vecstr res;
//        getallvariableStatisticsT(y, methodname, arity, classlabels, arvalarray, dataframe, 0, 0, res);
//        return res;
//    }
    
    //the number of permutations would be (n*(n+1)/2)
    long perm_size=((long)(arvalarray.size())*(arvalarray.size()+1)/2);
    
    long currentmax=(arvalarray.size()-1),eqval=(long)perm_size/numthreads, currentsum=0, currentbeg=0;
    
    if(perm_size<numthreads)
        numthreads=(int)perm_size;
    
    vecint beg(numthreads), end1(numthreads);
    
    framedouble table(numthreads);
    
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
        
        threads.create_thread(boost::bind(&getallvariableStatisticsT,boost::cref(y),methodname,arity,boost::cref(classlabels),
                                          boost::cref(arvalarray),boost::cref(dataframe),beg[i],end1[i],boost::ref(table[i])));
    }
    
    threads.join_all();
    
    pval=table[0][0];
    st=table[0][1];
    
    for(int i=1;i<table.size();i++)
    {
        if(methodname!="entropy" && methodname!="gini")
        {
            if(pval>=table[i][0])
            {
                if(pval>table[i][0])
                {
                    pval=table[i][0];
                    st=table[i][1];
                    bestindex=i;
                } else
                {
                    if(st<table[i][1])
                    {
                        pval=table[i][0];
                        st=table[i][1];
                        bestindex=i;
                    }
                }
                
            }
        } else {
            if(pval<table[i][0])
            {
                pval=table[i][0];
                st=table[i][1];
                bestindex=i;
            }
        }
    }
    
    vecdouble entry;
    for(int i=0;i<table[bestindex].size();i++)
    {
        entry.push_back(table[bestindex][i]);
    }
    
    return entry;
}


/*Given the details, this function would create a node*/
vecstr create_node(const vecstr & info, int size)
{
    vecstr node;
    for(int i=0;i<size;i++)
    {
        node.push_back(info[i]);
    }
    return node;
}

/*Given the best variable this method finds all such variables that are statistically different than the best variable*/
vecint getDifferentialVariables(const framestr & dataframe, int index, const vecstr & arvalarray)
{
    vecint diffindex;
    vecdouble res;
    vecstr y= dataframe[dataframe.size()-2];
    vecstr uny=retunique(y);
    
    if(uny.size()==1)
        return diffindex;
    
    vector<framedouble> tb;
    size_t df;
    double chisq;
    framedouble pooled;
    double pval;
    for(int i=0;i<arvalarray.size();i++)
    {
        if(i!=index)
        {
            tb=contigencytables(dataframe[index], dataframe[stoi(arvalarray[i])], y, 2);
            pooled=getpooled(tb[0], tb[1]);
            for(int j=2;j<uny.size();j++)
            {
                pooled=getpooled(pooled, tb[j]);
            }
            chisq=chisqst(pooled, getExpected(pooled));
            if(pooled.size()<2 || pooled[0].size()<2)
                pval=1;
            else {
                df=(pooled.size()-1) * (pooled[0].size()-1);
                pval=ChisqPvalue(chisq, df);
            }
            if(pval>=0.05)
                diffindex.push_back(i);
        }
        
    }
    return diffindex;
}

/*This function returns a significance value for the given attribute and class labels*/
double getSignificance(const vecstr & bestattr, const vecstr & y, const vecstr & classlabels, string method)
{
    double pvalue=0,st=0;
    size_t df=0;
    vecstr x=retunique(bestattr);
    vecdouble temp;
    framedouble table,expected;
    frameint table2;
    vecint temp2;
    for(int i=0;i<classlabels.size();i++)
    {
        vecstr neox1=selectOP(bestattr, which_is_equal(y, classlabels[i]));
        for(int j=0;j<x.size();j++)
        {
            temp.push_back((double)which_is_equal(neox1, x[j]).size());
        }
        table.push_back(temp);
        temp.clear();
    }
    
    if(method=="chisq")
    {
        expected=getExpected(table);
//        table=Transposeframe(table);
//        expected=Transposeframe(expected);
//        printframe(table);
        st=chisqst(table, expected);
        
        vecdouble rowsum=getRowSum(table);
        vecdouble columnsum=getColumnSum(table);
        rowsum=trim(rowsum);
        columnsum=trim(columnsum);
        
        if(rowsum.size()>=2&&columnsum.size()>=2)
        {
            df=(rowsum.size()-1)*(columnsum.size()-1);
            pvalue=ChisqPvalue(st, df);
        }
        else {
            df=1;
            pvalue=1;
        }
        
    }
    
    if(method=="funchisqall"||method=="funchisq")
    {
        for(int i=0;i<table.size();i++)
        {
            for(int j=0;j<table[i].size();j++)
            {
                temp2.push_back((int)table[i][j]);
            }
            table2.push_back(temp2);
            temp2.clear();
        }
        //transpose the table before sending to the chisq test
        table2=Transposeframe(table2);
        //printframe(table2);
        if(method=="funchisqall"){
            pvalue = ChisqDirTest(table2, st, df, "","all");
        } else {
            pvalue = ChisqDirTest(table2, st, df, "","non-constant");
        }
        
    }
    //cout<<"pval "<<pvalue<<"st "<<st<<"df "<<df<<endl;
    return pvalue;
}


/*This function is a non-parallel statistics collector exclusive to Fast FunChisq.*/
vecdouble getBestVariableStatsFFchisq(const vecstr & y, const vecstr & classlabels, const vecstr arvalarray, const framestr & dataframe)
{
    framestr tempframe;
    vecdouble tempres;
    vecdouble allstatcollector;
    int vi,vj,iindex=0,jindex=0;
    double beststat=0,bestpval;
    if(methodname!="entropy" && methodname!="gini")
        bestpval=1;
    else
        bestpval=0;
    for(int i=0;i<chosenindex.size();i++)
    {
        for(int j=0;j<arvalarray.size();j++)
        {
            tempframe.clear();
            tempres.clear();
            vi=chosenindex[i];
            vj=stoi(arvalarray[j]);
            tempframe.push_back(dataframe[vi]);
            tempframe.push_back(dataframe[vj]);
            if(vi==vj)
                tempres=method(tempframe, y, classlabels, methodname, arity, 1);
            else
                tempres=method(tempframe, y, classlabels, methodname, arity, 2);
            
            if(methodname!="entropy" && methodname!="gini")
            {
                if(bestpval>tempres[1])
                {
                    bestpval=tempres[1];
                    beststat=tempres[0];
                    iindex=vi;
                    jindex=vj;
                }
                
                if(bestpval == tempres[1])
                {
                    if(beststat<tempres[0])
                    {
                        bestpval=tempres[1];
                        beststat=tempres[0];
                        iindex=vi;
                        jindex=vj;
                    }
                }
            } else {
                
                if(bestpval<tempres[1])
                {
                    bestpval=tempres[1];
                    beststat=tempres[0];
                    iindex=vi;
                    jindex=vj;
                }
            }
            
        }
    }
    
    allstatcollector.push_back(bestpval);
    allstatcollector.push_back(beststat);
    allstatcollector.push_back(iindex);
    allstatcollector.push_back(jindex);
    return allstatcollector;
}


