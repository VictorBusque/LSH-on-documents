#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include"characteristic_matrix.h"
using namespace std;


int k = 5;
int ndocs = 2;

vector<vector <bool> > CM;
vector<vector<char> > docs;

void iniParams(){
    //Inicialitzar el Parametres
    cout << "Que K vols utilitzar? (0: usar K per defecte = " << k <<")" << endl;
    int aux;
    cin >> aux;
    if (aux>0) k=aux;
}

void readDocuments(char* argv[]) {
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

void writeSimilarity() {
    //Escriu per pantalla la Similitud de Jaccard a partir de la Matriu Caracteristica
    double x = 0.0;
    double y = 0.0;
    for (int i = 0; i < CM.size(); i++) {
        int aux = 0;
        if (CM[i][0]) aux++;
        if (CM[i][1]) aux++;
        if (aux == 2) x++;
        if (aux == 1) y++;
    }
    double jSim = x/(x+y);
    cout << "Similitud de Jaccard per els dos documents = " << jSim << endl;
}

int main(int argc, char *argv[]) {
    if (argc != 3){ cout << "Usage: parámetros deben ser 2 nombres de archivos de texto del mismo directorio a comparar" << endl; return 0;}
    iniParams();
    readDocuments(argv);
    Characteristic_Matrix cm(k,docs);
    CM = cm.getCM();
    writeSimilarity();
}
