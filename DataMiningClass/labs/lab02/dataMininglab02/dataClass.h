/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   dataClass.h
 * Author: housewife
 *
 * Created on February 17, 2018, 2:08 PM
 */

#ifndef DATACLASS_H
#define DATACLASS_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cmath>
#include <iterator>

using namespace std;



//Classes -----------

class dataNode {
    private:
        std::vector<double> values;
    public:
        
        dataNode(int size = 3)  : values(size) {  }        
        dataNode(dataNode&& other) : values(std::move(other.values)) {}
        
        dataNode(const dataNode& other) : values(other.values) {}
        
        dataNode& operator=(const dataNode& other) {
            if(&other == this) {
                return *this;
            }
            this->values = std::move(other.values);
        }
        
        dataNode& operator=(dataNode&& other) {
            //Move assign, steals data from other
            if(&other == this) {
                return *this;
            }
            this->values = std::move(other.values);
        }
        
        double getAttr(int attr) {
            return values[attr];
        }
        
        double getAttr(int attr) const {
            return values[attr];
        }
        
        double setAttr(int attr, double val) {
            values[attr] = val;
        }
        int valueSize() {
            return values.size();
        }
};

/*class dataNode {
    private:
        double * values;
        int attrAmt;
    public:
        dataNode(int size = 3) {
            attrAmt = size;
            values = new double[size];
            
        }
        virtual ~dataNode() {
            delete [] values;
        }
        //dataNode(const dataNode& source) {
         //   attrAmt = source.attrAmt;
        //    values = new double[source.attrAmt];
        //}
        dataNode(const dataNode& other) : attrAmt(other.attrAmt), values(new double[other.attrAmt]) {
            std::copy(other.values, other.values + other.attrAmt, values);
        }
        double getAttr(int attr) {
            return values[attr];
        }
        double setAttr(int attr, double val) {
            values[attr] = val;
        }
        dataNode& operator=(const dataNode& other) {
            this->attrAmt = other.attrAmt;
            this->values = new double[other.attrAmt];
            std::copy(other.values, other.values + attrAmt, values);
        }
};*/

//Declarations -----------

double unitDistance(const dataNode& unit1, const dataNode& unit2);
double nearestNeighbor(vector<dataNode> train, dataNode unit, int k);
double testKValue(vector<dataNode> train, vector<dataNode> test, int k);



double convertLabelToDouble(string label) {
    if (label == "I. versicolor") {
        return 1.0;
    } 
    
    return 0.0;
}

void createDataSets(vector<dataNode> & train, 
                    vector<dataNode> & test, 
                    vector<dataNode> original,
                    int trainingSize, int testSize){
    //cout << "Hello I'm creating Data sets!" << endl;
    srand(time(NULL));
    int rndNum = 0;
    int totalSize = trainingSize + testSize;
    for (int i = 0; i < trainingSize; i++) {
        rndNum = (rand() % (original.size()));
        train.push_back(original[rndNum]);
        original.erase(original.begin()+rndNum);
        //cout << "killing stuff: " << i << endl;
    }
    for (int i = 0; i < original.size(); i++) {
        test.push_back(original[i]);
    }
    //cout << "I've finished creating data Sets!" << endl;
}

void normalizeAttributes(double min0, double min1, double max0, double max1,
                        vector<dataNode> & set) {
    double range0 = max0-min0;
    double range1 = max1-min1;
    
    for (int i = 0; i < set.size(); i++) {
        double temp0 = (set[i].getAttr(0)-min0)/range0;
        double temp1 = (set[i].getAttr(1)-min1)/range1;
        set[i].setAttr(0, temp0); 
        set[i].setAttr(1, temp1);
    }
}

double testKValue(vector<dataNode> train, 
                    vector<dataNode> test, int k) {
    //cout << "Hello I'm inside the TestKValue function" << endl;
    int attramount = train[0].valueSize();
    //vector<double> minimums;
    //vector<double> maximums;
    
    //for (int i = 0; i<attramount; i++) {
        
    //}
    double min0 = train[0].getAttr(0);
    double min1 = train[0].getAttr(1);
    double max0 = train[0].getAttr(0);
    double max1 = train[0].getAttr(1);
    for (int i = 0; i < train.size(); i++) {
        double temp0 = train[i].getAttr(0);
        double temp1 = train[i].getAttr(1);
        if (min0 > temp0) {
            min0 = temp0;
        }
        if (min1 > temp1) {
            min1 = temp1;
        }
        if (max0 < temp0) {
            max0 = temp0;
        }
        if (max1 < temp1) {
            max1 = temp1;
        }
        
    }
    for (int i = 0; i < test.size(); i++) {
        double temp0 = test[i].getAttr(0);
        double temp1 = test[i].getAttr(1);
        if (min0 > temp0) {
            min0 = temp0;
        }
        if (min1 > temp1) {
            min1 = temp1;
        }
        if (max0 < temp0) {
            max0 = temp0;
        }
        if (max1 < temp1) {
            max1 = temp1;
        }
        
    }
    normalizeAttributes(min0, min1, max0, max1, train);
    normalizeAttributes(min0, min1, max0, max1, test);
    double accuracy = 0;
    int size = test.size();
    //Temp vector to hold supposed label values
    vector<double> temp;
    
    for (int i = 0; i < size; i++) {
        temp.push_back(nearestNeighbor(train, test[i], k));
    }
    
    for (int i = 0; i < size; i++) {
        if (temp[i] == test[i].getAttr(2)) {
            accuracy++;
        }
    }
    accuracy = accuracy/(double)size;
    return accuracy*100;
}

double nearestNeighbor(vector<dataNode> train, dataNode unit, int k) {
    //cout << "Hell I'm inside the NN function" << endl;
    double tempDistance = 0;
    double attrCheck = 0;
    double attr = 0;
    double mid = (double)k/2.0;
    int size = train.size();
    
    for (int i = 0; i < k; i++) {
        //cout << "doing this k business" << endl;
        double minDistanceVal = INTMAX_MAX;
        int minDistancePos = 0;
        for (int j = 0; j < train.size(); j++) {
            tempDistance = unitDistance(train[j], unit);
            if (tempDistance < minDistanceVal) {
                minDistanceVal = tempDistance;
                minDistancePos = j;
            }
            //cout << "j = " << j << endl;
        }
        attrCheck = train[minDistancePos].getAttr(2);
        if (attrCheck == 1) {
            attr++;
        }
        //cout << "erasing node" << endl;
        train.erase(train.begin()+minDistancePos);
        //cout << "finished erasing node" << endl;
    }
    if (attr > mid) {
        return 1;
    }
    return 0;
}

double unitDistance(const dataNode& left, const dataNode& right) {
    auto x1 = left.getAttr(0), x2 = right.getAttr(0), y1 = left.getAttr(1), y2 = right.getAttr(1);
    double distance = sqrt( (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 * y2));
    return distance;
}


void unitTest(vector<dataNode> originalSet, vector<dataNode> test, int k) {
    double accuracy = 0;
    int size = test.size();
    //Temp vector to hold supposed label values
    vector<double> temp;
    
    for (int i = 0; i < size; i++) {
        temp.push_back(nearestNeighbor(originalSet, test[i], k));
    }
    for (int i = 0; i < size; i++) {
        cout << "Test case 1, Label: " << temp[i] << endl;
    }
}
#endif /* DATACLASS_H */

