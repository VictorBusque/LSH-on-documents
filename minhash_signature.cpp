#include"minhash_signature.h"

MinHash_Signature::MinHash_Signature(vector<vector<bool> > CM, int N) {
    this->CM = CM;
    this->N = N;
    fullRandoms();
    computeSM();
}

void MinHash_Signature::fullRandoms() {
    //Omplir vectors per al diversos Hashings de forma aleatoria
    for (int i = 0; i < N; i++) {
        coefs.push_back(rand() %100);
        tInd.push_back(rand() %100);
    }
}

int MinHash_Signature::min (int a, int b) {
    //Minim entre 'a' i 'b'
    if (a<b) return a;
    else return b;
}

int MinHash_Signature::hv(int i, int key) {
    //Retorna el Hashing 'i' per a la clau key (return Hi(key))
    int coef = coefs[i];
    int indep_term = tInd[i];
    return ((coef*key + indep_term)%CM.size());
}

void MinHash_Signature::computeSM() {
    //Calcul de la Matriu de Signatures
    //Sets are columns of M, rows are each hi (0<=i<N) we must applicate
    //sig(h,c) = min(sig(h,c) , h(h,r).
    int ndocs = CM[0].size();
    SM = vector<vector<int> > (N, vector<int>(ndocs, CM.size()));
    for (int r = 0; r < CM.size(); r++) {
        for (int c = 0; c < ndocs; c++) {
            if (CM[r][c]) {
               for (int h = 0; h < N; h++) {
                   SM[h][c] = min( hv(h,r) , SM[h][c] );
               }
            }
        }
    }
}

vector<vector<int> > MinHash_Signature::getSM() {
    return SM;
}
