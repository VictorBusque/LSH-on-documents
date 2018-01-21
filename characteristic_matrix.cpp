#include"characteristic_matrix.h"


//PUBLIC METHODS
Characteristic_Matrix::Characteristic_Matrix(int k, vector<vector<char> > docs) {
    this->k = k;
    this->docs = docs;
    ndocs = docs.size();
    generateKShingles();
    hashShingles();
    generateUniversal();
    computeCM();
}

vector<vector<bool> > Characteristic_Matrix::getCM() {
    return CM;
}

void Characteristic_Matrix::generateKShingles() {
    //Generar el k-shingles dels dos documents
    kshings = vector<vector<string> > (ndocs);

    for (int index=0; index<ndocs; index++){
        vector<char> kshingle(k);
        
        for (int i = 0; i < k; i++) {
            kshingle[i] = docs[index][i];
        }
        
        string srt(kshingle.begin(), kshingle.end());
        kshings[index].push_back(srt);
            
        for (int i = k; i < docs[index].size(); i++) {
            kshingle.erase(kshingle.begin());
            kshingle.push_back(docs[index][i]);
            string srt(kshingle.begin(), kshingle.end());
            kshings[index].push_back(srt);
        }

    }

    
}

void Characteristic_Matrix::hashShingles() {
    //Fer Hashing dels k-shingles
    hash<string> h;
    buckets = vector<map<int,int> > (ndocs);
    int kshingsize = kshings[0].size();
    for (int index=1; index<ndocs; index++){
       if (kshings[index].size() > kshingsize) kshingsize = kshings[index].size();
    }

    for (int index=0; index<ndocs; index++){
        for (int i = 0; i < kshings[index].size(); i++) {
            buckets[index][h(kshings[index][i]) % kshingsize] = h(kshings[index][i]) % kshingsize;
        }
    }
}

void Characteristic_Matrix::generateUniversal() {
    //Generar l'Universal k-shingle
    for (int index=0; index<ndocs; index++){
        std::map<int,int>::iterator it=buckets[index].begin();
        while ((it != buckets[index].end())) {
            universal_kshingles[it->first] = it->first;
            it++;
        }
    }
}

void Characteristic_Matrix::computeCM() {
    //Calcul de la Matriu Caracteristica
    CM= vector<vector <bool> >(universal_kshingles.size(), vector<bool> (ndocs,false));
    std::map<int,int>::iterator u_it = universal_kshingles.begin();
    int i_uni = 0;

    while (u_it != universal_kshingles.end()) { //row iterator
        for (int index = 0; index < ndocs; index++) {//column iterator
            if (buckets[index].find(u_it->second) != buckets[index].end()) { //means element is in Set1
                CM[i_uni][index] = true;
            }
        }
        ++i_uni;
        ++u_it;
    }
}
