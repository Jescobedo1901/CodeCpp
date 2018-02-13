/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: housewife
 *
 * Created on February 6, 2018, 1:38 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cmath>

using namespace std;

//Functions
double convertLabelToDouble(string label);
double entropyCalc(double ratio);

/*
 * 
 */
int main(int argc, char** argv) {
    
    
    //Data Importation ---- (Currently manually done, function to come later)
    
    //Training Data Set
double matrixTrain[80][3] = {
    {3.2, 4.7, convertLabelToDouble("I. versicolor")},
    {3.2, 4.5, convertLabelToDouble("I. versicolor")},
    {3.1, 4.9, convertLabelToDouble("I. versicolor")},
    {2.3, 4, convertLabelToDouble("I. versicolor")},
    {2.8, 4.6, convertLabelToDouble("I. versicolor")},
    {2.8, 4.5, convertLabelToDouble("I. versicolor")},
    {3.3, 4.7, convertLabelToDouble("I. versicolor")},
    {2.4, 3.3, convertLabelToDouble("I. versicolor")},
    {2.9, 4.6, convertLabelToDouble("I. versicolor")},
    {2.7, 3.9, convertLabelToDouble("I. versicolor")},
    {2, 3.5, convertLabelToDouble("I. versicolor")},
    {3, 4.2, convertLabelToDouble("I. versicolor")},
    {2.2, 4, convertLabelToDouble("I. versicolor")},
    {2.9, 4.7, convertLabelToDouble("I. versicolor")},
    {2.9, 3.6, convertLabelToDouble("I. versicolor")},
    {3.1, 4.4, convertLabelToDouble("I. versicolor")},
    {3, 4.5, convertLabelToDouble("I. versicolor")},
    {2.7, 4.1, convertLabelToDouble("I. versicolor")},
    {2.2, 4.5, convertLabelToDouble("I. versicolor")},
    {2.5, 3.9, convertLabelToDouble("I. versicolor")},
    {3.2, 4.8, convertLabelToDouble("I. versicolor")},
    {2.8, 4, convertLabelToDouble("I. versicolor")},
    {2.5, 4.9, convertLabelToDouble("I. versicolor")},
    {2.8, 4.7, convertLabelToDouble("I. versicolor")},
    {2.9, 4.3, convertLabelToDouble("I. versicolor")},
    {3, 4.4, convertLabelToDouble("I. versicolor")},
    {2.8, 4.8, convertLabelToDouble("I. versicolor")},
    {3, 5, convertLabelToDouble("I. versicolor")},
    {2.9, 4.5, convertLabelToDouble("I. versicolor")},
    {2.6, 3.5, convertLabelToDouble("I. versicolor")},
    {2.4, 3.8, convertLabelToDouble("I. versicolor")},
    {2.4, 3.7, convertLabelToDouble("I. versicolor")},
    {2.7, 3.9, convertLabelToDouble("I. versicolor")},
    {2.7, 5.1, convertLabelToDouble("I. versicolor")},
    {3, 4.5, convertLabelToDouble("I. versicolor")},
    {3.4, 4.5, convertLabelToDouble("I. versicolor")},
    {3.1, 4.7, convertLabelToDouble("I. versicolor")},
    {2.3, 4.4, convertLabelToDouble("I. versicolor")},
    {3, 4.1, convertLabelToDouble("I. versicolor")},
    {2.5, 4, convertLabelToDouble("I. versicolor")},
    {3.2, 5.1, convertLabelToDouble("I. virginica")},
    {2.7, 5.3, convertLabelToDouble("I. virginica")},
    {3, 5.5, convertLabelToDouble("I. virginica")},
    {2.5, 5, convertLabelToDouble("I. virginica")},
    {2.8, 5.1, convertLabelToDouble("I. virginica")},
    {3.2, 5.3, convertLabelToDouble("I. virginica")},
    {3, 5.5, convertLabelToDouble("I. virginica")},
    {3.8, 6.7, convertLabelToDouble("I. virginica")},
    {2.6, 6.9, convertLabelToDouble("I. virginica")},
    {2.2, 5, convertLabelToDouble("I. virginica")},
    {3.2, 5.7, convertLabelToDouble("I. virginica")},
    {2.8, 4.9, convertLabelToDouble("I. virginica")},
    {2.8, 6.7, convertLabelToDouble("I. virginica")},
    {2.7, 4.9, convertLabelToDouble("I. virginica")},
    {3.3, 5.7, convertLabelToDouble("I. virginica")},
    {3.2, 6, convertLabelToDouble("I. virginica")},
    {2.8, 4.8, convertLabelToDouble("I. virginica")},
    {3, 4.9, convertLabelToDouble("I. virginica")},
    {2.8, 5.6, convertLabelToDouble("I. virginica")},
    {3, 5.8, convertLabelToDouble("I. virginica")},
    {2.8, 6.1, convertLabelToDouble("I. virginica")},
    {3.8, 6.4, convertLabelToDouble("I. virginica")},
    {2.8, 5.6, convertLabelToDouble("I. virginica")},
    {2.8, 5.1, convertLabelToDouble("I. virginica")},
    {2.6, 5.6, convertLabelToDouble("I. virginica")},
    {3, 6.1, convertLabelToDouble("I. virginica")},
    {3.4, 5.6, convertLabelToDouble("I. virginica")},
    {3.1, 5.5, convertLabelToDouble("I. virginica")},
    {3, 4.8, convertLabelToDouble("I. virginica")},
    {3.1, 5.4, convertLabelToDouble("I. virginica")},
    {3.1, 5.6, convertLabelToDouble("I. virginica")},
    {3.1, 5.1, convertLabelToDouble("I. virginica")},
    {2.7, 5.1, convertLabelToDouble("I. virginica")},
    {3.2, 5.9, convertLabelToDouble("I. virginica")},
    {3.3, 5.7, convertLabelToDouble("I. virginica")},
    {3, 5.2, convertLabelToDouble("I. virginica")},
    {2.5, 5, convertLabelToDouble("I. virginica")},
    {3, 5.2, convertLabelToDouble("I. virginica")},
    {3.4, 5.4, convertLabelToDouble("I. virginica")},
    {3, 5.1, convertLabelToDouble("I. virginica")} };
    
    
    
    //Test Data Set
    
double matrixTest[20][3] = {    
    {2.6, 4.4, convertLabelToDouble("I. versicolor")},
    {3, 4.6, convertLabelToDouble("I. versicolor")},
    {2.6, 4, convertLabelToDouble("I. versicolor")},
    {2.3, 3.3, convertLabelToDouble("I. versicolor")},
    {2.7, 4.2, convertLabelToDouble("I. versicolor")},
    {3, 4.2, convertLabelToDouble("I. versicolor")},
    {2.9, 4.2, convertLabelToDouble("I. versicolor")},
    {2.9, 4.3, convertLabelToDouble("I. versicolor")},
    {2.5, 3, convertLabelToDouble("I. versicolor")},
    {2.8, 4.1, convertLabelToDouble("I. versicolor")},
    {3.3, 6, convertLabelToDouble("I. virginica")},
    {2.7, 5.1, convertLabelToDouble("I. virginica")},
    {3, 5.9, convertLabelToDouble("I. virginica")},
    {2.9, 5.6, convertLabelToDouble("I. virginica")},
    {3, 5.8, convertLabelToDouble("I. virginica")},
    {3, 6.6, convertLabelToDouble("I. virginica")},
    {2.5, 4.5, convertLabelToDouble("I. virginica")},
    {2.9, 6.3, convertLabelToDouble("I. virginica")},
    {2.5, 5.8, convertLabelToDouble("I. virginica")},
    {3.6, 6.1, convertLabelToDouble("I. virginica")} };

    //Variables
    //All Matrices have 3 columns
    //Current size of training set is 80 rows
int trainingsize = 80;
int testsize = 20;
int sepalW = 3.0; // Sepal Width
int pedalL = 5.0; // Pedal Length
    
    //Entropy Things (if You'd like)

    //Previous Entropy
    /*  Count how many Versicolors vs Virginica's there are
        In our case Versicolor = 1, and Virginica = 0   */
int versicolorCount = 0;
int virginicaCount = 0;
for (int i = 0; i < trainingsize; i++) {
    if (matrixTrain[i][2] == 1) {
        versicolorCount++;
    }
    if (matrixTrain[i][2] == 0) {
        virginicaCount++;
    }
}

    /* Entroy equation we will use is as follows:
     E = (P/T)(logb2(P/T)) + (F/T)(logb2(F/T))  */
     
double ratioPass = (((double)versicolorCount)/((double)trainingsize));
double ratioFail = (((double)virginicaCount)/((double)trainingsize));
//double entropyPrev = ratioPass*log2(ratioPass) + ratioFail*log2(ratioFail);
double entropyPrev = entropyCalc(ratioPass) + entropyCalc(ratioFail);

cout << "Entropy previous of Training Data set: " << entropyPrev << endl;

    /*  Now that we have our Entropy of the Training Data Set, 
        We can find the Entropy of individual Attributes to figure out
        How much information we can gain from each attribute.   */


    /* Since the First and Second Attributes are both continuous variables
        We will use a brute force method to test a midpoint that we can divide 
        the variables into two sections     */

cout << "Find Informations gained for Attribute One" << endl;

double varMax = matrixTrain[0][0];
double varMin = matrixTrain[0][0];
double varIncr = .1;

//Find the max and min variables for the first attribute
for (int i = 0; i < trainingsize; i++) {
    if (matrixTrain[i][0] > varMax) { //Set the max attribute value
        varMax = matrixTrain[i][0];
    }
    if (matrixTrain[i][0] < varMin) { //Set the Minimum attribute value
        varMin = matrixTrain[i][0];
    }
    //Later add in a feature to automatically determine the increment value.
}
cout << "Var Min: " << varMin << endl;
cout << "Var Max: " << varMax << endl;
double attrStuff[6] = {0};
/*
double attrPass = .000000000000000001; attrStuff[0]
double attrFail = .000000000000000001; attrStuff[1]
double attrLabelP1 = .000000000000000001; attrStuff[2]
double attrLabelF1 = .000000000000000001; attrStuff[3]
double attrLabelP2 = .000000000000000001; attrStuff[4]
double attrLabelF2 = .000000000000000001; attrStuff[5] */


double entropyAttr1 = .00000000000001;
double attr1Best = varMin;
double currEntropy = entropyPrev;
//Now that we have our min and max values we find the best value for most info.
//Use the Entropy Equation from before, but for this attribute.
for (double i = varMin; i < varMax; i += varIncr) {
    for (int k = 0; k < 6; k++) {
        attrStuff[k] = 0;
    }
    for (int j = 0; j < trainingsize; j++) {
        if (matrixTrain[j][0] > i) {
            attrStuff[0]++;
            if (matrixTrain[j][2] == 1) {
                attrStuff[2]++;
            } else {
                attrStuff[3]++;
            }
        } else {
            attrStuff[1]++;
            if (matrixTrain[j][2] == 1) {
                attrStuff[4]++;
            } else {
                attrStuff[5]++;
            }
        }
    }
    for (int k = 0; k < 6; k++) {
        if (attrStuff[k] == 0) {
            attrStuff[k] = .000000000000001;
        }
    }
    double attrPRatio = attrStuff[0]/((double)trainingsize);
    double attrFRatio = attrStuff[1]/((double)trainingsize);
    //double entrOfP = (attrStuff[2]/attrStuff[0])*log2((attrStuff[2]/attrStuff[0])) +
    //                (attrStuff[3]/attrStuff[0])*log2((attrStuff[3]/attrStuff[0]));
    double entrOfP =   entropyCalc(attrStuff[2]/attrStuff[0]) + 
            entropyCalc(attrStuff[3]/attrStuff[0]);
    double entrOfF = entropyCalc(attrStuff[4]/attrStuff[1]) +
                    entropyCalc(attrStuff[5]/attrStuff[1]);
    //double entrOfF = (attrStuff[4]/attrStuff[1])*log2((attrStuff[4]/attrStuff[1])) +
    //                (attrStuff[5]/attrStuff[1])*log2((attrStuff[5]/attrStuff[1]));
    
    entropyAttr1 = attrPRatio*entrOfP + attrFRatio*entrOfF;
    
    if (currEntropy < (entropyAttr1 - entropyPrev)) {
        currEntropy = (entropyAttr1 - entropyPrev);
        attr1Best = i;
    }
    //for (int j = )
    //entropyAttr = attrPass*log2(ratioPass) + ratioFail*log2(ratioFail);
    
}
cout << "Best value for attribute 1: " << attr1Best << endl;
cout << "Information gained for this value: " << currEntropy << endl;


cout << "Find Information gained for attribute Two: " << endl;

/*------------------------------------------------------------------ENDING BOB*/
double varMax1 = matrixTrain[0][1];
double varMin1 = matrixTrain[0][1];
//double varIncr = .1;

//Find the max and min variables for the second attribute
for (int i = 0; i < trainingsize; i++) {
    if (matrixTrain[i][1] > varMax1) { //Set the max attribute value
        varMax1 = matrixTrain[i][1];
    }
    if (matrixTrain[i][1] < varMin1) { //Set the Minimum attribute value
        varMin1 = matrixTrain[i][1];
    }
    //Later add in a feature to automatically determine the increment value.
}
cout << "Var Min: " << varMin1 << endl;
cout << "Var Max: " << varMax1 << endl;
double attrStuff1[6] = {0};
/*
double attrPass = .000000000000000001; attrStuff[0]
double attrFail = .000000000000000001; attrStuff[1]
double attrLabelP1 = .000000000000000001; attrStuff[2]
double attrLabelF1 = .000000000000000001; attrStuff[3]
double attrLabelP2 = .000000000000000001; attrStuff[4]
double attrLabelF2 = .000000000000000001; attrStuff[5] */


double entropyAttr2 = .00000000000001;
double attr2Best = varMin;
double currEntropy1 = entropyPrev;
//Now that we have our min and max values we find the best value for most info.
//Use the Entropy Equation from before, but for this attribute.
for (double i = varMin1; i < varMax1; i += varIncr) {
    for (int k = 0; k < 6; k++) {
        attrStuff1[k] = 0;
    }
    for (int j = 0; j < trainingsize; j++) {
        if (matrixTrain[j][1] > i) {
            attrStuff1[0]++;
            if (matrixTrain[j][2] == 1) {
                attrStuff1[2]++;
            } else {
                attrStuff1[3]++;
            }
        } else {
            attrStuff1[1]++;
            if (matrixTrain[j][2] == 1) {
                attrStuff1[4]++;
            } else {
                attrStuff1[5]++;
            }
        }
    }
    for (int k = 0; k < 6; k++) {
        if (attrStuff1[k] == 0) {
            attrStuff1[k] = .000000000000001;
        }
    }
    double attrPRatio1 = attrStuff1[0]/((double)trainingsize);
    double attrFRatio1 = attrStuff1[1]/((double)trainingsize);
    
    double entrOfP1 =   entropyCalc(attrStuff1[2]/attrStuff1[0]) + 
            entropyCalc(attrStuff1[3]/attrStuff1[0]);
    double entrOfF1 = entropyCalc(attrStuff1[4]/attrStuff1[1]) +
                    entropyCalc(attrStuff1[5]/attrStuff1[1]); 
    entropyAttr2 = attrPRatio1*entrOfP1 + attrFRatio1*entrOfF1;
    
    if (currEntropy1 < (entropyAttr2 - entropyPrev)) {
        currEntropy1 = (entropyAttr2 - entropyPrev);
        attr2Best = i;
    }
    //for (int j = )
    //entropyAttr = attrPass*log2(ratioPass) + ratioFail*log2(ratioFail);
    
}
cout << "Best value for attribute 2: " << attr2Best << endl;
cout << "Information gained for this value: " << currEntropy1 << endl;
/*------------------------------------------------------------------HI I"M BOB*/

    //Decision Tree making now that we have the best values for 
    //Turning the two continuous attributes into discrete cases
    
/*
 * We are done calculating entropy, we select which attribute gives us the most
 * information gained and start with that.
 */

//Here and below is hardcoded for now, can revist at a later date


//Most info gained is from attribute 2
cout << "We can see most info gained from attr 2 and we create a simple tree" << endl;
int pos(0), neg(0);
int truePositive = 0;
int falsePositive = 0;
int trueNegative = 0;
int falseNegative = 0;
for (int i = 0; i < testsize; i++) {
    if (matrixTest[i][1] <= attr2Best) {
        pos++;
        if (matrixTest[i][2] == 1) {
            truePositive++;
        } else {
            falsePositive++;
        }
    } else {
        neg++;
        if (matrixTest[i][2] == 0) {
            trueNegative++;
        } else {
            falseNegative++;
        }
    }
}

cout << "Based on our Decision Tree...." << endl;
cout << "Positives found: " << pos << endl;
cout << "Negatives found: " << neg << endl; 
cout << "True Positives: " << truePositive << endl;
cout << "False Positives: " << falsePositive << endl;
cout << "True Negatives: " << trueNegative << endl;
cout << "False Negatives: " << falseNegative << endl;

cout << endl;

/*cout << "We will add the True Positives + the True Negatives\n" 
        << "and then divide that number by the Total amount of test samples,\n"
        << "to get the accuracy for our decision tree" << endl;*/
double accuracy = ((double)truePositive + (double)trueNegative)/((double)testsize)*100;

cout << "\nResulting Accuracy: " << accuracy << "%" << endl;
    
    
    return 0;
}


double convertLabelToDouble(string label) {
    if (label == "I. versicolor") {
        return 1.0;
    } 
    
    return 0.0;
}

double entropyCalc(double ratio) {
    return ratio*log2(ratio);
}