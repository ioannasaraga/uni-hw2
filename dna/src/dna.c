#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100000+1
//ορίζω τις κατάλληλες βιβλιοθήκες καθώς και το μέγιστο αριθμό βάσεων είναι +1 λόγω του '\0'

int main(int argc, char**argv){
  if(argc !=3){
        printf("Error: arguments missing. Usage: ./dna dnafile1 dnafile2\n");
        return 1;
    }//επιβεβαιώνω πως τα ορίσματα έχουν την κατάλληλη δομή 

 FILE* file1 = fopen(argv[1], "r");
 FILE* file2 = fopen(argv[2], "r");//ανοίγω μόνο για ανάγνωση τα αρχεία του χρήστη
 if(file1==NULL){
    printf("Error: cannot open file %s\n",argv[1]);
    return 1;
 }
  if(file2==NULL){
    printf("Error: cannot open file %s\n",argv[2]);
    return 1;
 }//αν δεν πετύχει η ανάγνωση βγαίνω με έξοδο 1
char *dna1 = malloc(sizeof(char) *MAX);
size_t lbyte1=fread(dna1,sizeof(char),MAX-1,file1);//δημιουργώ έναν πίνακα με το πρώτο dna με malloc επειδή
//δεν επιθυμώ να δεσμεύω πάντα την μέγιστη μνήμη μόνο όση χρειάζομαι
dna1[lbyte1]='\0';//στο τέλος προσθέτω το NULL byte υπολογίζω το μέγεθος της αλυσίδας μέσω των χαρακτήρων που διαβάζει η fread  
char *dna2 = malloc(sizeof(char) *MAX);
size_t lbyte2=fread(dna2,sizeof(char),MAX-1,file2);
dna2[lbyte2]='\0';//ακολουθώ τη ίδια διαδικασία για το δεύτερο dna 

char *mutual = malloc(sizeof(char) *MAX);//ορίζω δύο πίνακες μία για να αποθηκεύω το μέγιστο κοινό dna 
char *tmp = malloc(sizeof(char) *MAX);//μία προσωρινή για να αποθηκεύω την κοινή αλυσίδα 
unsigned int i,j;
size_t length1=strlen(dna1);//υπολογίζω τα μήκη των dna 
size_t length2=strlen(dna2);

if (dna1 == NULL || dna2 == NULL || mutual == NULL || tmp == NULL) {
    printf("Error: memory allocation failed\n");
    fclose(file1);
    fclose(file2);
    free(dna1);
    free(dna2);
    free(mutual);
    free(tmp);
    return 1;//ελέγχω ότι έχει δεσμευτεί σωστά η μνήμη που επιθυμώ 
}

for (i = 0; i < MAX; i++) {
    mutual[i] = '\0';
    tmp[i] = '\0';
 }//επιβεβαιώνω ότι θα ναι '\0' οι πίνακες που χρειάζομαι για την εύρεση

for(i=0;i<length1;i++){//το πρώτο loop είναι για τους χαρακτήρες του dna1 
  if(dna1[i] != 'A' && dna1[i] != 'G'  && dna1[i] != 'T' && dna1[i] != 'C' ){
         continue;//ελέγχω ότι δεν χρησιμοποιούνται άλλες βάσεις 
      }   
   for(j=0;j<length2;j++){
         if(dna2[j] != 'A' && dna2[j] != 'G'  && dna2[j] != 'T' && dna2[j] != 'C' ){
              continue;//ελέγχω ότι δεν χρησιμοποιούνται άλλες βάσεις
           }
   
      if(dna1[i]==dna2[j]){//το δεύτερο loop είναι για τους χαρακτήρες του dna2 
         unsigned int k=0;//πρακτικά ελέγχω για κάθε χαρκτήρα του dna1 αν ισούται με οποιδήποτε του dna2
         while(dna1[i]==dna2[j]){// για όσο ισούται οι αλισίδες αποθηκεύω αυτην την κοινή στον προσωρινό πίνακα
           
            tmp[k]=dna2[j];
            i++;
            j++;
            k++;
         }
         i=i-k;
         j--;//πρέπει να μειωθούν για να μην προσπεραστεί κάποια βάση 
         if(strlen(mutual)<strlen(tmp)){
             strcpy(mutual,tmp);
         }//το κοινό περνάει στην μέγιστη αλυσίδα μόνο αν έχει μεγαλυτέρο μήκος από το προηγούμενο μεγαλύτερο
         k=0;
         for(k=0;k<strlen(tmp);k++){
            tmp[k]='\0';//μηδενίζω την προσωρινή μετά από κάθε χρήση της
        }
      }
   }
}
if(strlen(mutual)>1){
   printf("%s\n",mutual);// τυπώνω την μέγιστη κοινή αλυσίδα μονο αν περιέχει πάνω από έναν χαρακτήρα
}
fclose(file1);
fclose(file2);//κκλείνω τα αρχεία που άνοιξα
free(dna1);
free(dna2);
free(mutual);
free(tmp);//αποδεσμεύω όλη την μνήμη που χρησιμοποιήσα
return 0;
}
