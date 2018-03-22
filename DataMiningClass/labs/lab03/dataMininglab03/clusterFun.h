/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   clusterFun.h
 * Author: housewife
 *
 * Created on February 28, 2018, 3:58 AM
 */

#ifndef CLUSTERFUN_H
#define CLUSTERFUN_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <cmath>
#include <iterator>
#include <sstream>
#include <ctime>

using namespace std;

//Classes
class cluster {
private:
    string path;
    vector<double> centroid;
    vector<vector<double>> data;
    
public:
    vector<vector<double>> features;
    vector<double> labels;
    
    cluster(string val = "kmeansData.txt") {
        path = val;
        storeFeatures();
        Normalize();
    }
    cluster(vector<vector<double>> feats) {
        features = feats;
        calcCentroid();
    }
    vector<double> getCentroid() {
        return centroid;
    }
    void calcCentroid() {
        int inner = features.size();
        int outer = features[0].size();
        for (int i = 0; i < outer; i++) {
            double temp = 0;
            for (int j = 0; j < inner; j++) {
                temp += features[j][i];
            }
            temp /= inner;
            centroid.push_back(temp);
        }
    }
    
    void storeFeatures() {
        ifstream inFile;
        inFile.open(path);
        
        if(inFile.bad()) {
            throw "Error opening file";
        }
        string title;
        getline(inFile,title);
        string line;
        while(getline(inFile,line)) { //Delimit by /n
            string value;
            vector<double> temp;
            istringstream ssline(line);
            //while(getline(ssline, value, ' ')) { //Delimit by ,
            while(ssline >> value) { //Delimit by ,
               double double_var;
               istringstream issval(value);
               issval >> double_var;
               temp.emplace_back(double_var);
            }
            features.emplace_back(move(temp));
        }
        inFile.close();
        //cout << "Leaving store data" << endl;
    }
    void printData() {
        int outer = features.size();
        int inner = features[0].size();
        cout << "Size 1 is: " << outer << endl;
        cout << "Size 2 is: " << inner << endl;
        
        for (int i = 0; i < outer; i++) {
            for (int j = 0; j < inner; j++) {
                cout << features[i][j] << " ";
            }
            cout << endl;
        }
    }
    
    void printLabels() {
        //cout << "Printing Labels for this cluster::" << endl;
        int size = labels.size();
        for (int i = 0; i < size; i++) {
            cout << labels[i];
        }
        cout << endl;
    }
    
    void Normalize() {
        int outer = features[0].size();
        //cout << "Outer size is: " << outer << endl;
        int inner = features.size();
        //cout << "Inner size is: " << inner << endl;
        vector<double> min;
        vector<double> range = findRange(outer, inner, min);
        for (int i = 0; i < outer; i++) {
            //vector<double> push;
            for (int j = 0; j < inner; j++) {
                double temp = calcNormal(range[i], features[j][i], min[i]);
                //push.push_back(features[j][i]);
                features[j][i] = temp;
            }
            //data.push_back(push);
        }
    }
    
    double calcNormal(double range, double x, double min) {
        return (x - min)/range;
    }
    
    vector<double> findRange(int outer, int inner, vector<double> & low) {
        
        vector<double> max;
        vector<double> range;
        //Find Max and Min for Each Attribute, Create Range vector
        for (int i = 0; i < outer; i++) {
            double max = features[0][i];
            double min = features[0][i];
            
            for (int j = 0; j < inner; j++) {
                double temp = features[j][i];
                if (temp > max) {
                    max = temp;
                }
                if (temp < min) {
                    min = temp;
                }
            }
            low.push_back(min);
            double tempRange = max-min;
            range.push_back(tempRange);
        }
        return range;
    }
    
};



//Function Declarations
void unitTestKMeans(int k);
void initialPartition(int k, cluster & original);
double distance(vector<double> x, vector<double> y);
void classify(vector<vector<double>> centroid, cluster & unLabeled);
void kmeans(cluster & group0, cluster & group1, int & iterations, bool flag);


void kmeans(cluster & group0, cluster & group1, int & iterations, bool flag) {
    iterations++;
    cout << "Iteration #" << iterations << endl;
    flag = true;
    vector<vector<double>> centroids;
    centroids.push_back(group0.getCentroid());
    centroids.push_back(group1.getCentroid());
    
    classify(centroids, group0);
    classify(centroids, group1);
    
    vector<vector<double>> dataSet1;
    vector<vector<double>> dataSet2;
    int outer = group0.features.size();
    int inner = group0.features[0].size();
    for (int i = 0; i < outer; i++) {
        vector<double> temp;
        for (int j = 0; j < inner; j++) {
            double val = group0.features[i][j];
            temp.push_back(val);
        }
        //Change this section to cluster array, hardcoded for now
        if (group0.labels[i] < 1) {
            dataSet1.push_back(temp);
        }  else {
            dataSet2.push_back(temp);
            flag = false;
        }
    }
    outer = group1.features.size();
    inner = group1.features[0].size();
    for (int i = 0; i < outer; i++) {
        vector<double> temp;
        for (int j = 0; j < inner; j++) {
            double val = group1.features[i][j];
            temp.push_back(val);
        }
        //Change this section to cluster array, hardcoded for now
        if (group1.labels[i] < 1) {
            dataSet1.push_back(temp);
            flag = false;
        }  else {
            dataSet2.push_back(temp);
        }
    }
    cluster next1(dataSet1);
    cluster next2(dataSet2);
    if (flag == false) {
        kmeans(next1, next2, iterations, flag);
    }
    cout << "Labels for this Iterations:" << endl;
    cout << "Cluster 0: ";
    group0.printLabels();
    cout << "Cluster 1: ";
    group1.printLabels();
    cout << endl;
}

void unitTestKMeans(int k) {
    cout << "Starting K-Means Unit Test!" << endl;
    cluster original;
    //cluster kClusters = 
    initialPartition(k, original);
    
    vector<vector<double>> dataSet1;
    vector<vector<double>> dataSet2;
    int outer = original.features.size();
    int inner = original.features[0].size();
    for (int i = 0; i < outer; i++) {
        vector<double> temp;
        for (int j = 0; j < inner; j++) {
            double val = original.features[i][j];
            temp.push_back(val);
        }
        //Change this section to cluster array, hardcoded for now
        if (original.labels[i] < 1) {
            dataSet1.push_back(temp);
        }  else {
            dataSet2.push_back(temp);
        }
    }
    
            
    cluster group1(dataSet1);
    cluster group2(dataSet2);
    int iterations = 0;
    cout << "Beginning K-Means!" << endl;
    kmeans(group1, group2, iterations, false);
    cout << "Iteration total for unchanging cluster sets: " << iterations << endl;
}

void initialPartition(int k, cluster & original) {
    cout << "Initializing first datasets" << endl;
    vector<vector<double>> centroids;
    int featAmt = original.features[0].size();
    for (int i = 0; i < k; i++) {
        vector<double> temp;
        for (int j = 0; j < featAmt; j++) {
            //Initialize K centroids to the first K values in data set
            temp.push_back(original.features[i][j]);
        }
        centroids.push_back(temp);
    }
    classify(centroids, original);
    
    //cout << "size of features in centroid: " << centroids[0].size() << endl;
    
}

double distanceFunc(vector<double> x, vector<double> y) {
    double val = 0;
    int sizeX = x.size();
    int sizeY = y.size();
    if (sizeX != sizeY) {
        throw "Invalid sizes! :: Sizes are Unequal";
    }
    for (int i = 0; i < sizeX; i++) {
        double sq = x[i]-y[i];
        val += sq*sq;
    }
    
    return sqrt(val);
}

void classify(vector<vector<double>> centroid, cluster & unLabeled) {
    int amountOfLabels = unLabeled.features.size();
    int amountOfCentroids = centroid.size();
    double clusterNum = 0;
    //For each label, calculate the distance to each centroid and store the minimum
    for (int i = 0; i < amountOfLabels; i++) {
        double minDistance = distanceFunc(centroid[0], unLabeled.features[i]);
        clusterNum = 0;
        for (int j = 0; j < amountOfCentroids; j++) {
            double distance = distanceFunc(centroid[j], unLabeled.features[i]);
            if (distance < minDistance) {
                minDistance = distance;
                clusterNum = j;
            }
        }
        unLabeled.labels.push_back(clusterNum);
    }
}

#endif /* CLUSTERFUN_H */

