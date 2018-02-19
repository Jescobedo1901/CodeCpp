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
        
        double setAttr(int attr, double val) {
            values[attr] = val;
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

double unitDistance(dataNode unit);
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

double testKValue(vector<dataNode> train, 
                    vector<dataNode> test, int k) {
    //cout << "Hello I'm inside the TestKValue function" << endl;
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
    double distanceOfUnit = unitDistance(unit);
    double distanceOfTrain = 0;
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
            distanceOfTrain = unitDistance(train[j]);
            tempDistance = abs(distanceOfTrain-distanceOfUnit);
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

double unitDistance(dataNode unit) {
    //cout << "Hello Distance function" << endl;
    double distance = sqrt((unit.getAttr(0)*unit.getAttr(0) +
                        unit.getAttr(1)*unit.getAttr(1)));
    //cout << "leaving distance" << endl;
    return distance;
}
#endif /* DATACLASS_H */

