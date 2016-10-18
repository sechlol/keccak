#include <stdio.h>
#include <stdlib.h>
#include "KeccakF1600.h"
#include "Keccak_r1024.h"

/* This function returns a new padded message */
unsigned char* padding(unsigned char* mex, unsigned int* size){

    unsigned char* newMex;

    //calculate the new dimension for the padded array
    unsigned int i,newSize=(*size+128-(*size%128));

    newMex=malloc(newSize*sizeof(unsigned char));

    // Copy old message in the new one
    for(i=0;i<*size;i++){
        newMex[i] = mex[i];
    }

    // add tailing byte
    newMex[i]=0x01;
    i++;

    // add zeros untin the end
    while(i < newSize){
        newMex[i]=0x00;
        i++;
    }

    // xor the last byte with 0x80
    newMex[newSize-1] ^= 0x80;

    // update the size of the message
    *size=newSize;
    return newMex;
}

unsigned char* Hash(unsigned char* mess, unsigned int lenght){
    unsigned int x,i;

    /* Padding Phase */
    unsigned int sizeP=lenght;
    unsigned char* P = padding(mess,&sizeP);

    /* Initialize */
    unsigned char *S,*newS;

    S=malloc(200 * sizeof(unsigned char));
    for(x=0;x<200;x++){
        S[x]=0;
    }

    /* Absorbing Phase */
    for(i=0;i<(sizeP/128);i++){
        for(x=0;x<128;x++)
            S[x] ^= P[i*128+x];

        newS = KeccakF_bytes(S);
        free(S);
        S = newS;
    }

    /* Squeezing Phase */
    unsigned char* Z = malloc(128 * sizeof(unsigned char));
    for(x=0;x<128;x++)
        Z[x] = S[x];

    return Z;
}
