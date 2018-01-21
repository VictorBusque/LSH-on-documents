#ifndef CHARACTERISTIC_MATRIX_H
#define CHARACTERISTIC_MATRIX_H

 // CHARACTERISTIC_MATRIX_H


#include<vector>
#include<map>
#include<string>
#include<functional>
#include<fstream>
#include<cstdlib>

#include<iostream>

using namespace std;

class Characteristic_Matrix {


private:
    int k;
    int ndocs;
    vector<vector<char> > docs;
    vector< vector<string> >kshings;
    vector <map<int, int> >buckets;
    map<int, int> universal_kshingles;
    vector<vector <bool> > CM;

    void generateKShingles();

    void hashShingles();

    void generateUniversal();

    void computeCM();



public:

    Characteristic_Matrix(int k, vector<vector<char> > docs);

    vector<vector<bool> > getCM();

};
#endif
