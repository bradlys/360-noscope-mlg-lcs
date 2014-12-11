#include <stdio.h>
#include <stdlib.h>

/**
 * O(N*M) time complexity method where
 * N is length of A and M is length of B.
 * This function returns the length
 * of the longest common subsequence between
 * A and B. This has O(M+1) space complexity outside
 * supplied argument strings O(M+N). Altogether,
 * it is linear space.
 * 
 * There should be a methodology to improve the
 * space complexity to O(MIN(N,M) + 1) but I could
 * not implement it and have it function correctly.
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
    int K[Blen];
    int i = 0;
    //Make sure K array is all zeroes
    for(i = 0; i < Blen; i++){
        K[i] = 0;
    }
    //loop over rows
    for(i = 0; i < Alen; i++){
    	int j = 0;
    	//initial column before letters is always 0
    	long long int upperLeftCornerValue = 0;
    	long long int leftValue = 0;
    	//this is technically K[j] but it gets assigned later
    	long long int aboveValue = 0;
    	//Loop over columns
        for(j = 0; j < Blen; j++){
        	//if match, upper left column value + 1
            if(newA[i] == newB[j]){
                K[j] = upperLeftCornerValue + 1;
            } else {
            	//if j == 0, leftValue is always 0
            	if(j > 0){
            		leftValue = K[j-1];
        		}
        		//aboveValue is always the last rows value,
        		//which is still in the array because K[j] hasn't
        		//been replaced yet
        		aboveValue = K[j];
        		//assign K[j] whichever is larger
            	if(leftValue > aboveValue){
            		K[j] = leftValue;
        		} else {
        			K[j] = aboveValue;
    			}
            }
            upperLeftCornerValue = K[j];
        }
    }
    return K[Blen-1];
}

/**
 * Prints the longest common subsequence of two
 * long long int arrays to standard out. Easily
 * modified to return it in an array instead.
 * Approximate runtime: O(M*N*(M+N))
 * Approximate space: O(M+N)
 * 
 */
void findLCS(long long int * A, int Abegin, int Aend, long long int * B, int Bbegin, int Bend){
    int Alen = Aend - Abegin;
    if (Alen == 0){
        return;
    }
    int Blen = Bend - Bbegin;
    long long int * newA = A;
    long long int * newB = B;
    newA += Abegin;
    newB += Bbegin;
    if ( Alen == 1){
		int i = 0;
        for(i = 0; i < Blen; i++){
            if(newA[0] == newB[i]){
            	//bingo, throw it to standard out
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
		int k = 0;
        for (k = 0; k < Blen+1; k++){
            BBbegin = Bbegin + k;
            BAend = Bbegin + k;
            int sizeLCSA = getLCSLength(A, AAbegin, AAend, B, BAbegin, BAend);
            int sizeLCSB = getLCSLength(A, ABbegin, ABend, B, BBbegin, BBend);
            if(sizeLCSA + sizeLCSB == sizeLCSOriginal){
                break;
                //Found the split
            }
        }
        
        //Let's split!
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
 * Approx Runtime: O(M*N*(M+N))
 * Approx Space: O(M+N)
 * Approx rekt: O(MLG)
 * Approx chance of hiring manager taking this lightly: 0%
 */
int main() {
    int n = 0; int m = 0;
    scanf("%i", &n); scanf("%i", &m);
    long long int A[n]; long long int B[m];
    int i = 0;
    for(i = 0; i < n; i++){
        scanf("%lli", &A[i]);
    }
    for(i = 0; i < m; i++){
        scanf("%lli", &B[i]);
    }
    findLCS(A, 0, n, B, 0, m);
    return 0;
}
