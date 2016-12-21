//
//  main.cpp
//  CPTree
//
//  Created by Sajal Kumar on 2/24/16.
//  Copyright © 2016 NMSUSongLab. All rights reserved.
//

/****************************************************
*               PARAMETERS FOR CPTREE               *
*   -k "Name of the dataset"                        *
*   -i "Arity"                                      *
*   -m "Method"                                     *
*   -a "Alpha value"                                *
*   -c "Correlation Test"                           *
*   -f "fast enabled"                               *
*   -h "Help"                                       *
*****************************************************/



#include <iostream>
#include <string>
#include "CPTreeMain.hpp"
#include "CPChisq.h"
#include "method.hpp"
#include "CorrelationTest.hpp"
#include <fstream>
using namespace std;

int main(int argc, char* argv[]) {
    
    string root="/Users/sajalkumar/Dropbox/";
    string k="",method="",param, mode="classification";
    int arity=0;
    double alpha=0.00;
    if(argc==1)
    {
        cout<<"No parameters : Running the default dataset XOR, with cpx2 method, alpha = 0.05 and arity=2"<<endl;
        k="XOR";
        method="funchisq";
        arity=2;
        alpha=0.5;
    } else if(argc==2)
    {
        param=argv[1];
        if(param.substr(0,2)=="-h"){
            
            cout<<"Help Instructions"<<endl;
            cout<<"-k Name_of_dataset"<<endl;
            cout<<"-i Arity (1 or 2)"<<endl;
            cout<<"-m Method (gini, cpx2, chisq, entropy, funchisqnorm or funchisq)"<<endl;
            cout<<"-a Alpha value (pvalue cut off)"<<endl;
            cout<<"-c Correlation Test (For dimensionality reduction, to be used singularly"<<endl;
            cout<<"-f Fast enabled, a faster implementation"<<endl;
            cout<<"Example .CPtree -kXOR -i2 -mcpx2"<<endl;
            return 0;
            
        } else
        {
            cout<<"Insufficient parameters : Running the default dataset XOR, with cpx2 method, alpha = 0.05 and arity=2"<<endl;
            k="XOR";
            method="cpx2";
            arity=2;
            alpha=0.05;
            
        }
        
    } else if(argc==3) {
        
        param=argv[1];
        if(param.substr(0,2)=="-c"){
            mode="correlation";
            param=argv[2];
            k=param.substr(2);
        } else {
            cout<<"Insufficient parameters : Running the default dataset XOR, with cpx2 method, alpha = 0.05 and arity=2"<<endl;
            k="XOR";
            method="cpx2";
            arity=2;
            alpha=0.05;
        }
    }
    
    else if(argc==5){
        for(int i=1;i<argc;i++)
        {
            param=argv[i];
            if(param.substr(0,2)=="-k")
                k=param.substr(2);
            if(param.substr(0,2)=="-i")
                arity=stoi(param.substr(2));
            if(param.substr(0,2)=="-m")
                method=param.substr(2);
            if(param.substr(0,2)=="-a")
                alpha=stod(param.substr(2));
        }
    } else
    {
        cout<<"Invalid number of parameters : Running the default dataset XOR, with cpx2 method, alpha = 0.05 and arity=2"<<endl;
        k="XOR";
        method="cpx2";
        arity=2;
        alpha=0.05;
    }
    

    if(mode=="correlation")
    {
        string path=root+"CPTree/Data/NaturalData/"+k+"_natural.txt";
        vecstr all=readall(path);
        framestr tab=readTable(all,',');
        tab=Transposeframe(tab);
        tab=deleteOP<vector<string>>(tab, (int)(tab.size()-1));
        vecint res=corTestMain(tab);
        
        ofstream indexfile;
        indexfile.open (root+"CPTree/Data/CorrelationIndex/"+k+"_CDeleteindex.txt");
        
        if(res.size()==0)
            indexfile<<"NILL";
        else
        {
            for(int i=0;i<res.size();i++)
                indexfile<<to_string(res[i])+"\t";
        }
        indexfile<<"\n";
        indexfile.close();
        cout<<"Correlation Test Done!!"<<endl<<"Results in "<<root<<"Data/CorrelationIndex/"<<endl;
        return 0;
    }
    
//    vecdouble x,y,z;
//    for(int i=0;i<10;i++)
//    {
//        x.push_back(30-i);
//        y.push_back(50-i);
//        z.push_back(100-i);
//    }
//    framedouble all;
//    all.push_back(x);
//    all.push_back(y);
//    all.push_back(z);
//    
//    printframe(all);
//    
//    framedouble res=sortFrame(all, 1,"ascending");
//    
//    printframe(res);
    
    
    
    string path=root+"CPTree/Data/ReadData/"+k+"_Categorized.txt";
    vecstr all=readall(path);
    framestr tab=readTable(all,',');
    tab=Transposeframe(tab);
    
    CPTree cp(tab[tab.size()-1],((int)tab.size()-1));
    cp.CPTreeMainIterative(tab,method,arity,alpha);
    
    framestr treestruct=cp.getTreeStruct();
    
    ofstream myfile;
    if(method=="gini"){
        while(!myfile.is_open())
            myfile.open (root+"CPTree/Data/TreesGini/"+k+"_Tree.txt");
    } else if(method=="cpx2"){
        while(!myfile.is_open())
            myfile.open (root+"CPTree/Data/TreesCPX2/"+k+"_Tree.txt");
    } else if(method=="funchisq"){
        while(!myfile.is_open())
            myfile.open (root+"CPTree/Data/TreesFunChisq/"+k+"_Tree.txt");
    } else if(method=="fastfunchisq"){
        while(!myfile.is_open())
            myfile.open (root+"CPTree/Data/TreesFunChisqFast/"+k+"_Tree.txt");
    } else if(method=="chisq") {
        while(!myfile.is_open())
            myfile.open (root+"CPTree/Data/TreesChisq/"+k+"_Tree.txt");
    } else if(method=="entropy") {
        while(!myfile.is_open())
            myfile.open (root+"CPTree/Data/TreesEntropy/"+k+"_Tree.txt");
    }
    
    for(int i=0;i<treestruct.size();i++)
    {
        for(int j=0;j<treestruct[i].size();j++)
        {
            if(j<treestruct[i].size()-1)
                myfile <<treestruct[i][j]+"\t";
            else
                myfile <<treestruct[i][j];
        }
        myfile<<"\n";
    }
    myfile.close();
    
    vecstr colnm=cp.getColumnNames();
    
    ofstream myfile2;
    while(!myfile2.is_open())
        myfile2.open (root+"CPTree/Data/Column-names/"+k+"_colnames.txt");
    
    for(int i=0;i<colnm.size();i++)
    {
        if(i<colnm.size()-1)
            myfile2<<colnm[i]+",";
        else
            myfile2<<colnm[i]+"\n";
    }
    myfile2.close();
    
    cout<<"Done"<<endl<<"Results in "<<root<<"CPTree/Data/"<<endl;
    
    return 0;
}
