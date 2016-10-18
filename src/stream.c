#include "stream.h"


// Initialisation function
// The key is of lenght 16 bytes and will corresponds to the 16 first bytes of the 1600-bits state S. 
// The others bytes correspond to the initial value. Here 0. 
void initialisation(unsigned char *S,unsigned char* key){
   memset(S,0,200*sizeof(unsigned char));
   memcpy(S,key,16*sizeof(unsigned char));
}


// This encryption function return a ciphertext of lenght lenght corresponding to the plaintext Plaintext. 
// The key is 16-bytes. 
unsigned char* encrypt( unsigned char* key, unsigned char* Plaintext,unsigned int lenght){
	
	int i,j;
	
	//count the number of 128-block
	int numBlocks = lenght > 0 ? ((lenght-1)/128)+1 : 0;
	
	//allocate arrays
	unsigned char* S = calloc(200,sizeof(unsigned char));
	unsigned char* C = calloc(128*numBlocks,sizeof(unsigned char));
	unsigned char* paddedPlain = calloc(128*numBlocks,sizeof(unsigned char));
	unsigned char* t;
	
	//initialize initial state
	initialisation(S,key);
	
	//pad the plaintext to 128 byte block
    memcpy(paddedPlain,Plaintext,lenght*sizeof(unsigned char));
    
    for(i=0;i<numBlocks;i++){
		t = KeccakF_bytes(S);
		free(S);
		S = t;
		
		//append to ciphertext a block of plaintext Xored using S
		for(j=0;j<128;j++){
			C[i*128+j] = paddedPlain[i*128+j]^S[j];
		}
	}
	
	return C; 
}


