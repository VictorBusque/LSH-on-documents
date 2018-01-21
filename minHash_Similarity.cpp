#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include"characteristic_matrix.h"
#include"minhash_signature.h"
using namespace std;


int k = 5;
int N = 500; //number of hash functions

int ndocs;

vector<vector<char> > docs;

vector<vector <bool> > CM;
vector<vector<int> > SM;

vector<int> coefs;  //ith position stores Coeficient  of ith hash function.
vector<int> tInd;   //ith position stores Independent of ith hash function.

void iniParams(int argc){
    //Inicialitzar el Parametres
    ndocs = argc-1;
    cout << "Que K vols utilitzar? (0: usar K per defecte = " << k <<")" << endl;
    int auxK;
    cin >> auxK;
    if (auxK>0) k=auxK;
    cout << "Quantes funcions de hash vols utilitzar? (0: usar N per defecte = " << N <<")" << endl;
    int auxN;
    cin >> auxN;
    if (auxN>0) N=auxN;
}

void readDocuments(char *argv[]) {
    //Llegir el dos documents
    ifstream fileReader;
    string out;//aproximation
    for (int index=1; index<=ndocs; index++) {
        const char *filename = argv[index];
        fileReader.open(filename);
        vector<char> document;
        while (!fileReader.eof()) {
            fileReader >> out;
            for (int i = 0; i < out.size(); i++) document.push_back(out[i]);
            document.push_back(' '); //in case we must include ' ' as shingle.
        }
        docs.push_back(document);
        fileReader.close();
    }
}

void writeSimilarity(char *argv[]) {
    //Escriu per pantalla la Similitud de totes les parelles de documents
    for (int i = 0; i < ndocs; i++) {
        for (int j = i+1; j < ndocs; j++) {
            double value = 0;
            for (int k = 0; k < N; k++) {
                if (SM[k][i] == SM[k][j]) value++;
            }
            value = value / N;
            cout << "Similitud(" << argv[i+1] << ", " << argv[j+1] << ") = " << value << endl;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3){ cout << "Usage: parámetros deben ser 2 o más nombres de archivos de texto del mismo directorio a comparar" << endl; return 0;}
    iniParams(argc);
    readDocuments(argv);
    Characteristic_Matrix cm(k,docs);
    CM = cm.getCM();
    MinHash_Signature sm(CM,N);
    SM = sm.getSM();
    writeSimilarity(argv);
}
