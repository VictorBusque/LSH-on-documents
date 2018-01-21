#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<math.h>
#include"characteristic_matrix.h"
#include"minhash_signature.h"
using namespace std;



int k = 5;
int N = 500; //number of hash functions
int b = 100; //number of bands
int r = 5;   //number of row per band
double t;    //threshold

int ndocs;

vector<vector<char> > docs;

map<pair<int,int>, double> candidates;

vector<vector <bool> > CM;
vector<vector<int> > SM;


void iniParams(int argc){
    //Inicialitzar el Parametres
    ndocs = argc-1;
    cout << "Que K vols utilitzar? (0: usar K per defecte = " << k <<")" << endl;
    int auxK;
    cin >> auxK;
    if (auxK>0) k=auxK;

    cout << "Quantes bandes vols utilitzar? (0: usar B per defecte = " << b <<")" << endl;
    int auxB;
    cin >> auxB;
    if (auxB>0) b=auxB;
    cout << "Quantes files per banda vols utilitzar? (0: usar R per defecte = " << r <<")" << endl;
    int auxR;
    cin >> auxR;
    if (auxR>0) r=auxR;

    N = b*r;

    double b1 = b;
    double r1 = r;
    t = pow((1/b1),(1/r1)); //t ~ (1/b)^(1/r) [threshold auto-calculado]

    cout << "Quin threshold vols utilitzar? (0: usar T autocalculat = " << t <<")" << endl;
    double auxT;
    cin >> auxT;
    if (auxT!=0) t=auxT;
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

double jaccardSimilarity(int d1, int d2) {
    double value = 0;
    for (int k = 0; k < N; k++) {
        if (SM[k][d1] == SM[k][d2]) value++;
    }
    value = value / N;
    return value;
}

void generateCandidates() {
    //Genera els candidat per al LSH
    hash<string> h; //to hash all rows of all bands.
    vector <vector<int> > buckets(b, vector<int> (ndocs)); //vector[i] -> vector<int> on cada int és el bucket de la fila r

    for (int band = 0; band < b; band++) {
        for (int c = 0; c < ndocs; c++) {
            char aux[r];
            for (int row = 0; row < r; row++) {
                aux[row] = SM[band*r+row][c];
            }
            //at this point, a single row is computed.
            string aux1 = aux;
            buckets[band][c] = h(aux1);
        }
    }

    //processing candidates;
    for (int band = 0; band < b; band++) {
        for (int c = 0; c < ndocs-1; c++) {
            for (int k = c+1; k < ndocs; k++) {
                if (buckets[band][c] == buckets[band][k]) {
                    pair<int,int> p;
                    p.first = c;
                    p.second = k;
                    candidates[p]= 0;
                }
            }
        }
    }

    std::map<pair<int,int>,double>::iterator it = candidates.begin();

    while (it != candidates.end()) {
        it->second = jaccardSimilarity(it->first.first, it->first.second);
        it++;
    }

}

void writeSimilarity(char *argv[]) {
    //Escriu per pantalla la Similitud de tots els candidats amb Similitud superior al threshold
    cout <<"VALOR DE THRESHOLD: "<< t << endl;
    int similars = 0;
    std::map<pair<int,int>,double>::iterator it = candidates.begin();
    while (it != candidates.end()) {
        if(it->second >= t){
            cout << "Similitud(" << argv[(it->first.first)+1] << ", " << 
            argv[(it->first.second)+1] << ") = " << it->second << endl;
            similars++;
        }
        it++;
    }
    if (similars == 0) cout << "No hi ha cap parell de documents significativament similars."<<endl;
}

int main(int argc, char *argv[]) {
    if (argc < 3){ cout << "Usage: parámetros deben ser 2 o más nombres de archivos de texto del mismo directorio a comparar" << endl; return 0;}
    iniParams(argc);
    readDocuments(argv);
    Characteristic_Matrix cm(k,docs);
    CM = cm.getCM();
    MinHash_Signature sm(CM,N);
    SM = sm.getSM();
    generateCandidates();
    writeSimilarity(argv);
}
