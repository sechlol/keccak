/* API test */

#include <stdio.h>
#include <stdlib.h>
#include "src/KeccakF1600.h"


int main(){
  unsigned long** INPUT=malloc(5*sizeof(unsigned long));
  int x;
  for(x=0;x<5;x++){
    INPUT[x]=malloc(5*sizeof(unsigned long));
  }
  INPUT[0][0]=0;
  INPUT[1][0]=0;
  INPUT[2][0]=0;
  INPUT[3][0]=0;
  INPUT[4][0]=0;

  INPUT[0][1]=0;
  INPUT[1][1]=0;
  INPUT[2][1]=0;
  INPUT[3][1]=0;
  INPUT[4][1]=0;

  INPUT[0][2]=0;
  INPUT[1][2]=0;
  INPUT[2][2]=0;
  INPUT[3][2]=0;
  INPUT[4][2]=0;

  INPUT[0][3]=0;
  INPUT[1][3]=0;
  INPUT[2][3]=0;
  INPUT[3][3]=0;
  INPUT[4][3]=0;

  INPUT[0][4]=0;
  INPUT[1][4]=0;
  INPUT[2][4]=0;
  INPUT[3][4]=0;
  INPUT[4][4]=0;

  unsigned long** OUTPUT_REF=malloc(5*sizeof(unsigned long));
  for(x=0;x<5;x++){
    OUTPUT_REF[x]=malloc(5*sizeof(unsigned long));
  }

  OUTPUT_REF[0][0]=0xF1258F7940E1DDE7;
  OUTPUT_REF[1][0]=0x84D5CCF933C0478A;
  OUTPUT_REF[2][0]=0xD598261EA65AA9EE;
  OUTPUT_REF[3][0]=0xBD1547306F80494D;
  OUTPUT_REF[4][0]=0x8B284E056253D057;

  OUTPUT_REF[0][1]=0xFF97A42D7F8E6FD4;
  OUTPUT_REF[1][1]=0x90FEE5A0A44647C4;
  OUTPUT_REF[2][1]=0x8C5BDA0CD6192E76;
  OUTPUT_REF[3][1]=0xAD30A6F71B19059C;
  OUTPUT_REF[4][1]=0x30935AB7D08FFC64;
 
  OUTPUT_REF[0][2]=0xEB5AA93F2317D635;
  OUTPUT_REF[1][2]=0xA9A6E6260D712103;
  OUTPUT_REF[2][2]=0x81A57C16DBCF555F;
  OUTPUT_REF[3][2]=0x43B831CD0347C826; 
  OUTPUT_REF[4][2]=0x01F22F1A11A5569F;

  OUTPUT_REF[0][3]=0x05E5635A21D9AE61;
  OUTPUT_REF[1][3]=0x64BEFEF28CC970F2;
  OUTPUT_REF[2][3]=0x613670957BC46611;
  OUTPUT_REF[3][3]=0xB87C5A554FD00ECB;
  OUTPUT_REF[4][3]=0x8C3EE88A1CCF32C8;

  OUTPUT_REF[0][4]=0x940C7922AE3A2614;
  OUTPUT_REF[1][4]=0x1841F924A2C509E4;
  OUTPUT_REF[2][4]=0x16F53526E70465C2;
  OUTPUT_REF[3][4]=0x75F644E97F30A13B;
  OUTPUT_REF[4][4]=0xEAF1FF7B5CECA249;
  
  unsigned long** OUTPUT=KeccakF(INPUT);


  //check 
  int y;
  int count=1;
  for(x=0;x<5;x++){
    for(y=0;y<5;y++){
      if(OUTPUT[x][y]!=OUTPUT_REF[x][y]){
	count=0;
      }
    }
  }
  if(count==0){
    printf("FAIL\n");
  }
  else{
    printf("PASS\n");
  }

  for(x=0;x<5;x++){
    free(INPUT[x]);
    free(OUTPUT[x]);
    free(OUTPUT_REF[x]);
  }
   free(INPUT);
   free(OUTPUT);
   free(OUTPUT_REF);

 
  return 0;
}
