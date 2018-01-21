#include<vector>
#include<map>
#include<string>
#include<functional>
#include<fstream>
#include<cstdlib>

#include<iostream>

using namespace std;

class MinHash_Signature {

private:

    int N;

    vector<vector <bool> > CM;
    vector<vector<int> > SM;

    vector<int> coefs;  //ith position stores Coeficient  of ith hash function.
    vector<int> tInd;   //ith position stores Independent of ith hash function.



void fullRandoms();

int hv(int i, int key);

int min (int a, int b);

void computeSM();


public:

MinHash_Signature(vector<vector<bool> >CM, int N);

vector<vector<int> > getSM();

};
