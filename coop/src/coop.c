#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//χρησιμοποιούμε τις κατάλληλες βιβλιοθήκες 
#define MAX pow(10,6)
#define C 67
#define D 68
//ορίζω σαν σταθερές τους χαρακτήρες C και D για την διευκόλυνση μου καθώς και τον μέγιστο αριθμό γύρων
int main(void){
    int bot=D;//οριστικοποιώ την πρώτη κίνηση
    int player;//αυτή είναι ο παίχτης δηλαδή ο χρήστης
    int rounds=0;//θα την χρησιμποιήσω για τους γύρους
    putchar(bot);//εκτυπώνω την πρώτη κίνηση του υπολογιστή 
    fflush(stdout);//χρησιμοποιώ αυτήν την εντολή για να καθαρίζω το buffer μετά από κάθε εκτύπωση
    putchar('\n');//νέα γραμμή 
    fflush(stdout);
    player=getchar(); //ζητώ νεά κίνηση
    rounds++;//την αυξάνω μετά από καθε κίνηση του χρήστη
    while((player != EOF)&&(rounds<=MAX)){//το loop όπως και το παιχνίδι τερματίζει είτε όταν φτάνουμε 
    //στους μέγιστους γύρους είτε όταν ο χρήστης τα παραταέι
    if((player!=C) && (player!=D)){
      player=getchar();//αν δεν παίζει με τις κατάλληλες κινήσεις το προσπερνάει και ζητά άλλη κίνηση
      continue;
    }
    if(rounds==MAX){
      break;//αυτό είναι για την αποφυγεί παραπάνω κίνησης του υπολογιστή καθώς 
      //για κάποιο λόγο τα rounds αυξάνονται μετά από κάθε κινηση του bot και όχι του παίχτη
      //που νόμιζα πως είχα σχεδιάση
    }
    
       if(rounds%3==0){
          if(player==D){
            putchar(C);
            fflush(stdout);
            putchar('\n');
       
          }
          else{
            putchar(D);
            fflush(stdout);
            putchar('\n');
    
        }//η τακτική μου βασίζεται στην συμπεριφορά του αντίπαλου
        //όμως ανά 3 κινήσεις τυπώνει το αντίθετο για να τον ξαφνιάζει
      }
      else{
        bot=player;
        putchar(bot);
        fflush(stdout);
        putchar('\n');

       }
     
      //εφόσον όλες οι περιπτώσεις τελειώνουν με putchar χρησιμοποιώ ένα ομαδικώ καθάρισμα του buffer
      // για κάθε περίπτωση
       fflush(stdout);
       player=getchar(); 
       rounds++;// αυξάνω τους γύρους ύστερα από κάθε κίνηση του αντιπάλου

       //αυτές οι εντολές βρίσκονται έξω από το if καθώς εκτελούνται έτσι και αλλιώς
      
     }
    return 0;
}
