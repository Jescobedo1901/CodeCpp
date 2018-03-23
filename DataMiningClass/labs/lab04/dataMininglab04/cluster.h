/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cluster.h
 * Author: housewife
 *
 * Created on March 22, 2018, 8:14 AM
 */

#ifndef CLUSTER_H
#define CLUSTER_H


#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <cmath>
#include <iterator>
#include <sstream>
#include <utility>
#include <ctime>
#include <algorithm>

using namespace std;

//Classes

class cluster {
private:
    string path;
    vector<double> centroid;
    //vector<vector<double>> data;
   
    
public:
    static int cluster_counter;
    int cluster_sequence = cluster_counter++;
    vector<vector<double>> features;
    //vector<double> labels;
    
    cluster(bool readInData = true) {
        
        if(readInData) {
            path = "hclusterData.txt";
            storeFeatures();
            Normalize();
            if(features.empty()) {
                throw "Failed to read in features";
            }
        }
    }
    cluster(vector<vector<double>> feats) {
        features = feats;
        calcCentroid();
    }
    vector<double>& getCentroid() {
        if(centroid.empty()) {
            throw "Centroid has not been initialized";
        }
        return centroid;
    }
    
    void calcCentroid() {
        int feature_count = features.size();     
        if(feature_count == 0) {
            throw "There are no features to calculate centroid for\n";
        }
        int attr_count = features[0].size();
        if(!attr_count) {
            throw "Automatic dimension detection failed, first element of feature vector is of length zero";
        }
        centroid.clear();
        for (int i = 0; i < attr_count; i++) {
            double temp = 0;
           
            for (int j = 0; j < feature_count; j++) {
                 if(features[j].size() != attr_count) {
                     //std::cerr << "Feature[" << j << "].size = " << features[j].size() << "\n";
                    throw "Attribute size does not match first vector";
                }
                temp += features[j][i];
            }
            temp /= feature_count;
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
        int firstSize = -1;
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
            if(firstSize < 0) {
                firstSize = temp.size();
            } else if(firstSize != temp.size()) {
                throw "Number of elements on the line does not match first row\n";
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
    
    /*void printLabels() {
        //cout << "Printing Labels for this cluster::" << endl;
        int size = labels.size();
        for (int i = 0; i < size; i++) {
            cout << labels[i];
        }
        cout << endl;
    }*/
    
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

int cluster::cluster_counter = 0;

//Declarations

void unitTestHierarchyClustering();

template<typename ClosestFinder>
void hierachical_clustering_apply(ClosestFinder finder, vector<vector<int>> &points);

double distance(vector<double>& x, vector<double>& y);
void closestCentroid(vector<cluster> & group, int & indx1, int & indx2);
double findMax(cluster & x, cluster & y);
double findMin(cluster & x, cluster & y);
double findAvg(cluster & x, cluster & y);
void closestMax(vector<cluster> & group, int & indx1, int & indx2);
void closestMin(vector<cluster> & group, int & indx1, int & indx2);
void closestMean(vector<cluster> & group, int & indx1, int & indx2);
void unitTestCentroid(vector<vector<int>> &points);
void unitTestMax(vector<vector<int>> &points);
void unitTestMin(vector<vector<int>> &points);
void unitTestAvg(vector<vector<int>> &points);

void unitTestHierarchyClustering() {
    cout << "Beginning Hierarchy Clustering!" << endl;
    vector<vector<int>> centroidOrder;
    vector<vector<int>> maxOrder;
    vector<vector<int>> minOrder;
    vector<vector<int>> avgOrder;
    cluster::cluster_counter = 0;
    //unitTestCentroid(centroidOrder);
    cluster::cluster_counter = 0;
    //unitTestMax(maxOrder);
    cluster::cluster_counter = 0;
    //unitTestMin(minOrder);
    cluster::cluster_counter = 0;
    unitTestAvg(avgOrder);
}

void closestCentroid(vector<cluster> & group, int & indx1, int & indx2) {
    int size = group.size();   
    double minDistance = distance(group[0].getCentroid(), group[1].getCentroid());
    for (int i = 0; i < size-1; i++) {
        for (int j = i+1; j < size; j++) {
            double temp = distance(group[i].getCentroid(), group[j].getCentroid());
            if (temp < minDistance) {
                minDistance = temp;
                indx1 = i;
                indx2 = j;
            }
        }
    }
    //std::cout << "closeness: " << minDistance << "\n";
}

double findMax(cluster & x, cluster & y) {
    int outer = x.features.size();
    int inner = y.features.size();
    double maxDistance = distance(x.features[0], y.features[0]);
    for (int i = 0; i < outer; i++) {
        for (int j = 0; j < inner; j++) {
            double temp = distance(x.features[i], y.features[j]);
            if (temp > maxDistance) {
                maxDistance = temp;
            }
        }
    }
    
    return maxDistance;
}

double findMin(cluster & x, cluster & y) {
    int outer = x.features.size();
    int inner = y.features.size();
    double minDistance = distance(x.features[0], y.features[0]);
    for (int i = 0; i < outer; i++) {
        for (int j = 0; j < inner; j++) {
            double temp = distance(x.features[i], y.features[j]);
            if (temp < minDistance) {
                minDistance = temp;
            }
        }
    }
    
    return minDistance;
}

double findAvg(cluster & x, cluster & y) {
    double outer = x.features.size();
    double inner = y.features.size();
    double avgDistance = 0;
    for (int i = 0; i < outer; i++) {
        for (int j = 0; j < inner; j++) {
            double temp = distance(x.features[i], y.features[j]);
            avgDistance += temp;
        }
    }
    avgDistance /= outer*inner;
    
    return avgDistance;
}

void closestMax(vector<cluster> & group, int & indx1, int & indx2) {
    int size = group.size();
    double minDistance = findMax(group[0], group[1]);
    for (int i = 0; i < size-1; i++) {
        for (int j = i+1; i < size; j++) {
            double temp = findMax(group[i], group[j]);
            if (temp < minDistance) {
                minDistance = temp;
                indx1 = i;
                indx2 = j;
            }
        }
    }
}
    
void closestMin(vector<cluster> & group, int & indx1, int & indx2) {
    int size = group.size();
    double minDistance = findMin(group[0], group[1]);
    for (int i = 0; i < size-1; i++) {
        for (int j = i+1; i < size; j++) {
            double temp = findMin(group[i], group[j]);
            if (temp < minDistance) {
                minDistance = temp;
                indx1 = i;
                indx2 = j;
            }
        }
    }
}

void closestMean(vector<cluster> & group, int & indx1, int & indx2) {
    int size = group.size();
    double minDistance = findAvg(group[0], group[1]);
    for (int i = 0; i < size-1; i++) {
        for (int j = i+1; i < size; j++) {
            double temp = findAvg(group[i], group[j]);
            if (temp < minDistance) {
                minDistance = temp;
                indx1 = i;
                indx2 = j;
            }
        }
    }
}

double distance(vector<double>& x, vector<double>& y) {
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

template<typename ClosestFinder>
void hierachical_clustering_apply(ClosestFinder finder, vector<vector<int>> &points) {
    cluster original;
    int size = original.features.size();
    cout << "Size is: " << size << endl;
    
    vector<cluster> nodes;
    for (int i = 0; i < size; i++) {
        vector<vector<double>> tempFeat;
        tempFeat.emplace_back(original.features[i]);
        cluster tempNode(tempFeat);
        tempNode.calcCentroid();
        //std::cout << "The centroid (" << i << ") is: " << tempNode.getCentroid().size() << "\n";
        nodes.emplace_back(std::move(tempNode));
    }

    std::cout << "Number of nodes " << nodes.size() << "\n";
    while (nodes.size() > 1) {
        
        int idx1(0), idx2(1);
        
        finder(nodes, idx1, idx2);
       
        cluster new_cluster(false);
        
        new_cluster.features.reserve(nodes[idx1].features.size() +  nodes[idx1].features.size());
        
        for(auto& f1 : nodes[idx1].features) {
            new_cluster.features.push_back(std::move(f1));
        }
        for(auto& f2 : nodes[idx2].features) {
            new_cluster.features.push_back(std::move(f2));
        }
        
        new_cluster.calcCentroid();
        
        nodes.emplace_back(std::move(new_cluster));
        
        std::cout << "New cluster " << new_cluster.cluster_sequence << " from " << nodes[idx1].cluster_sequence << " and " << nodes[idx2].cluster_sequence << "\n";
        nodes.erase(
            std::remove_if(
                nodes.begin(),
                nodes.end(), 
                [&](auto & val) {
                    return &val == &nodes[idx1] || &val == &nodes[idx2];
                }
            ), 
            nodes.end()
        );
            
       // std::cout << "Size after removing: " << nodes.size() << "\n";
        //std::cout << "Number of nodes " << nodes.size() << "\n";
    }
    
    std::cout << "Number of nodes " << nodes.size() << "\n";
    
    //Print Function 
}





void unitTestCentroid(vector<vector<int>> &points) {
    hierachical_clustering_apply(closestCentroid, points);
}

void unitTestMax(vector<vector<int>> &points) {
    hierachical_clustering_apply(closestCentroid, points);
}

void unitTestMin(vector<vector<int>> &points) {
    hierachical_clustering_apply(closestCentroid, points);
}

void unitTestAvg(vector<vector<int>> &points) {
    hierachical_clustering_apply(closestCentroid, points);
}


#endif /* CLUSTER_H */

