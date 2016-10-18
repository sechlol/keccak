/* implementation of the internal permutation of Keccak with a 1600-bit state*/


#include <stdio.h>
#include <stdlib.h>
#include "KeccakF1600.h"

//The offset constants.
const int r[5][5]={{0,36,3,41,18},{1,44,10,45,2},{62,6,43,15,61},{28,55,25,21,56},{27,20,39,8,14}};

//The round constants
const unsigned long RC[24]={
                0x0000000000000001, 0x0000000000008082,
			    0x800000000000808A, 0x8000000080008000,
			    0x000000000000808B, 0x0000000080000001,
			    0x8000000080008081, 0x8000000000008009,
			    0x000000000000008A, 0x0000000000000088,
			    0x0000000080008009, 0x000000008000000A,
			    0x000000008000808B, 0x800000000000008B,
			    0x8000000000008089, 0x8000000000008003,
			    0x8000000000008002, 0x8000000000000080,
			    0x000000000000800A, 0x800000008000000A,
			    0x8000000080008081, 0x8000000000008080,
			    0x0000000080000001, 0x8000000080008008 };


void fromBytesToWords(unsigned long  **stateAsWords, unsigned char *stateAsBytes){
  int i,j;
  for(i=0; i<(1600/64); i++){
    stateAsWords[i%5][i/5] = 0;
    for(j=0; j<(64/8); j++)
      stateAsWords[i%5][i/5] |= (unsigned long )(stateAsBytes[i*(64/8)+j]) << (8*j);
  }
}

/* converts a unsigned long 2D matrix in a byte array*/
void fromWordsToBytes(unsigned char *stateAsBytes, unsigned long  **stateAsWords){
    int i,j;
    unsigned char* charPointer;
    for(i=0; i<(1600/64); i++){
        // get the value from long matrix
        unsigned long n = stateAsWords[i%5][i/5];

        //convert into char array
        charPointer = (unsigned char*)(&n);

        //copy into the output
        for(j=0;j<8;j++)
            stateAsBytes[i*8+j] = charPointer[j];
    }
}


//Function to add  to the previous assignement.
 //The state is composed of 200 byte
unsigned char* KeccakF_bytes(unsigned char *state){
    int x;

    //create temporary word arrays and the output array
    unsigned long **inWord, **outWord;
    unsigned char* outState;

    inWord = malloc(5 * sizeof(unsigned long));
    outState = malloc(200 * sizeof(unsigned char));
    for(x=0;x<5;x++)
      inWord[x]=malloc(5*sizeof(unsigned long));

    //convert in words, apply rounds and convert again in bytes
    fromBytesToWords(inWord,state);
    outWord = KeccakF(inWord);
    fromWordsToBytes(outState,outWord);

    //delete temporary arrays
    free(inWord);
    free(outWord);

    return outState;

}

/* implements the modulo operation a%b also supporting negative values for a */
int mod(int a, int b){
   int remaining = a % b;
   if(remaining < 0)
     remaining +=b;
   return remaining;
}

/* Executes a left circular shift. At the end of the operation the original value is not changed
 * (parameter passed per value) */
unsigned long ROL(unsigned long W, int r){
    return W << r | (W >> (sizeof(W) * 8 - r));
}

/* Executes one round of the keccak[1600]. It doesn't need a return type, the computations
 * are done directly in the matrix A. */
void round1600(unsigned long** A, const unsigned long rc){
    int x,y;
    unsigned long B[5][5],C[5],D[5];

    /* Theta step */

    /* Calculating C[0..4] as XORs of different columns of A */
    for(x=0;x<5;x++)
        C[x] = A[x][0] ^ A[x][1] ^ A[x][2] ^ A[x][3] ^ A[x][4];

    /* Calculating D[0..4]. Some indexex could be out of bound, so the mod() function
     * assures to contain the values to always be in modulo 5 */
    for(x=0;x<5;x++)
        D[x] = C[mod(x-1,5)] ^ ROL(C[mod(x+1,5)],1);

    /* Calculating A[0..4][0..4] with a nested for cycle. Every column of A is XORed
     * with the same value of D[] */
    for(x=0;x<5;x++)
        for(y=0;y<5;y++)
            A[x][y] = A[x][y] ^ D[x];

    /* Rho and pi steps: For every value in A executes a rotation and assign the
     * result to a particular cell of the temporary matrix B */
    for(x=0;x<5;x++)
        for(y=0;y<5;y++)
            B[y][mod(2*x+3*y,5)] = ROL(A[x][y],r[x][y]);

    /* Xi step: Ececutes an XOR, NOT and AND bitwise operations taking values from
     * the supporting matrix and assign the result to A */
    for(x=0;x<5;x++)
        for(y=0;y<5;y++)
            A[x][y] = B[x][y] ^ ((~B[mod(x+1,5)][y]) & B[mod(x+2,5)][y]);

    /* Iota step: just mix a constant value (different for every round) to the first cell of A */
    A[0][0] = A[0][0] ^ rc;

}

//Return the state after 24 rounds
//Do not modify the name of this fonction  
unsigned long** KeccakF(unsigned long** input){

    int x,y;

    /* allocate a new bidimensional array in the memory of type unsigned long */
    unsigned long** output=malloc(5*sizeof(unsigned long));
    for(x=0;x<5;x++){
      output[x]=malloc(5*sizeof(unsigned long));
    }

    /* copy the content of the input matrix into the new one */
    for(x=0;x<5;x++)
        for(y=0;y<5;y++)
            output[x][y] = input[x][y];

    /* executes 24 rounds passing always the same pointer as parameter and every time
     * a new value as round constant */
    for(x=0;x<24;x++)
        round1600(output,RC[x]);

    return output;
}

