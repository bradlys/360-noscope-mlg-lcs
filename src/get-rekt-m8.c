#include <stdio.h>
#include <stdlib.h>

/**
 * O(N*M) time complexity method where
 * N is length of A and M is length of B.
 * This function returns the length
 * of the longest common subsequence between
 * A and B. It has a space complexity of
 * O(2*M) (2 times M) but could be reduced to
 * O(M+1). (M plus 1) Reason I didn't do that is
 * 'cause I implemented that solution earlier
 * and then erased the god damn thing without
 * saving it.
 * 
 * I'm not sure but I think it might also be possible to reduce
 * the space complexity to O(min(N, M) + 1) for this method.
 * Set K[min(N,M)] and iterate appropriately.
 *
 */
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

/**
 * Prints the longest common subsequence
 * to standard out. This will run 
 * approximately O(log(N+M)) times due to
 * recursive calls. Fortunately, this uses
 * very little space. Of course, it's not
 * a constant amount of space. It's something like
 * O(log(M+N)). Which in the scheme of things, ain't bad.
 * The reason it uses that space is because of all the recursive
 * calls (O(log(M+N)) and the storage of things like
 * Alen, Blen, AAbegin, etc.
 * 
 * And then, of course, it runs getLCSLength() which takes a
 * monsterous O(M*N) time. It runs it a lot too. If space
 * were not a huge issue then possibly having a lookup table
 * for most frequently called getLCSLength() values could
 * speed up time. Just a thought. Memoization is a thing.
 */
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

/**
 * Takes the data from standard in,
 * outputs it to standard out. What more could you
 * ever ask for?
 * 
 * Not including constant factors:
 * Approx Runtime: O(M*N*log(N+M))
 * Approx Space: O(M+N)
 * Approx rekt: O(MLG)
 * Approx chance of hiring manager taking this lightly: 0%
 */
int main() {
    int n = 0; int m = 0;
    scanf("%i", &n); scanf("%i", &m);
    long long int A[n]; long long int B[m];
    for(int i = 0; i < n; i++){
        scanf("%lli", &A[i]);
    }
    for(int i = 0; i < m; i++){
        scanf("%lli", &B[i]);
    }
    findLCS(A, 0, n, B, 0, m);
    return 0;
}
