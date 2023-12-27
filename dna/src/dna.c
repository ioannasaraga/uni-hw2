#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100000+1


int main(int argc, char**argv){
  if(argc !=3){
        printf("Error: arguments missing. Usage: ./dna dnafile1 dnafile2\n");
        return 1;
    }

 FILE* file1 = fopen(argv[1], "r");
 FILE* file2 = fopen(argv[2], "r");
 if(file1==NULL){
    printf("Error: cannot open file %s\n",argv[1]);
    return 1;
 }
  if(file2==NULL){
    printf("Error: cannot open file %s\n",argv[2]);
    return 1;
 }
char *dna1 = malloc(sizeof(char) *MAX);
size_t lbyte1=fread(dna1,sizeof(char),MAX-1,file1);
dna1[lbyte1]='\0';
char *dna2 = malloc(sizeof(char) *MAX);
size_t lbyte2=fread(dna2,sizeof(char),MAX-1,file2);
dna2[lbyte2]='\0';

char *mutual = malloc(sizeof(char) *MAX);
char *tmp = malloc(sizeof(char) *MAX);
int i,j;
size_t length1=strlen(dna1);
size_t length2=strlen(dna2);

for (i = 0; i < MAX; i++) {
    mutual[i] = '\0';
    tmp[i] = '\0';
 }

for(i=0;i<length1;i++){
   for(j=0;j<length2;j++){
      if(dna1[i]==dna2[j]){
         int k=0;
         while(dna1[i]==dna2[j]){
            tmp[k]=dna2[j];
            i++;
            j++;
            k++;
         }
         i=i-k;
         j--;
         if(strlen(mutual)<=strlen(tmp)){
             strcpy(mutual,tmp);
         }
         k=0;
         for(k=0;k<strlen(tmp);k++){
            tmp[k]='\0';
        }
      }
   }
}
if(strlen(mutual)>1){
   printf("%s\n",mutual);
}
fclose(file1);
fclose(file2);
free(dna1);
free(dna2);
free(mutual);
free(tmp);
return 0;
}
