/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: housewife
 *
 * Created on March 22, 2018, 8:11 AM
 */

#include "cluster.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    try {
    unitTestHierarchyClustering();
    }catch(const char* msg) {
        std::cout << "The error is: " << msg << "\n";
        return 1;
    }
    return 0;
}

