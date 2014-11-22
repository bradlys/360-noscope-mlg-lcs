#include <stdio.h>
#include <stdlib.h>

int getLCSLength(long long int * A, int Abegin, int Aend, long long int * B, int Bbegin, int Bend){
    int Alen = Aend - Abegin;
    int Blen = Bend - Bbegin;
    if(Alen == 0 || Blen == 0){
        return 0;
    }
    long long int * newA = A;
    long long int * newB = B;
    newA += Abegin;
    newB += Bbegin;
    int K[2][Blen+1];
    for(int i = 0; i < Blen+1; i++){
        K[1][i] = 0;
        K[0][i] = 0;
    }
    for(int i = 0; i < Alen; i++){
        for(int j = 0; j < Blen+1; j++){
            K[0][j] = K[1][j];
        }
        K[1][0] = 0;
        for(int j = 1; j < Blen+1; j++){
            if(newA[i] == newB[j-1]){
                K[1][j] = K[0][j-1] + 1;
            } else {
                if(K[0][j] > K[1][j-1]){
                    K[1][j] = K[0][j];
                } else {
                    K[1][j] = K[1][j-1];
                }
            }
        }
    }
    return K[1][Blen];
}

void findLCS(long long int * A, int Abegin, int Aend, long long int * B, int Bbegin, int Bend){
    int Alen = Aend - Abegin;
    int Blen = Bend - Bbegin;
    long long int * newA = A;
    long long int * newB = B;
    newA += Abegin;
    newB += Bbegin;
    if (Alen == 0){
        return;
    } else if ( Alen == 1){
        for(int i = 0; i < Blen; i++){
            if(newA[0] == newB[i]){
                printf("%lli ", newA[0]);
                break;
            }
        }
        return;
    } else {
        //Split A
        int AAbegin = Abegin;
        int ABbegin = Abegin + Alen/2;
        int AAend = Abegin + Alen/2;
        int ABend = Abegin + Alen;
        
        //Split B
        int BAbegin = Bbegin;
        int BBbegin = Bbegin + Blen/2;
        int BAend = Bbegin + Blen/2;
        int BBend = Bbegin + Blen;
        //Find correct split for B
        int sizeLCSOriginal = getLCSLength(A, Abegin, Aend, B, Bbegin, Bend);
        for (int k = 0; k < Blen+1; k++){
            BBbegin = Bbegin + k;
            BAend = Bbegin + k;
            int sizeLCSA = getLCSLength(A, AAbegin, AAend, B, BAbegin, BAend);
            int sizeLCSB = getLCSLength(A, ABbegin, ABend, B, BBbegin, BBend);
            if(sizeLCSA + sizeLCSB == sizeLCSOriginal){
                break;
            }
        }
        
        findLCS(A, AAbegin, AAend, B, BAbegin, BAend);
        findLCS(A, ABbegin, ABend, B, BBbegin, BBend);
        
        return;
    }
}

int main() {
    int n = 0;
    int m = 0;
    scanf("%i", &n); scanf("%i", &m);
    long long int A[n];
    long long int B[m];
    for(int i = 0; i < n; i++){
        scanf("%lli", &A[i]);
    }
    for(int i = 0; i < m; i++){
        scanf("%lli", &B[i]);
    }
    findLCS(A, 0, n, B, 0, m);
    return 0;
}
