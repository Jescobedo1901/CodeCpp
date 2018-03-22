/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: housewife
 *
 * Created on February 28, 2018, 3:54 AM
 */

#include "clusterFun.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    //Path kmeansData.txt
    //Determine k clusters
    cout << "For this dataset we assume there to be 2 clusters, k = 2" << endl;
    cout << "In future test cases it might be unknown how many clusters to look for" << endl;
    int k = 2;
    
    
    unitTestKMeans(k);
    
    cout << "The First iteration is the last one to be printed, " << endl;
    cout << "The Final iteration is the first one to be printed :: due to recursion" << endl;
    return 0;
}