#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX pow(10,6)
#define C 67
#define D 68

int main(void){
    int me=D;
    int player;
    int rounds=0;
    putchar(me);
    fflush(stdout);
    putchar('\n');
    fflush(stdout);
    player=getchar(); 
    rounds++;
    while((player != EOF)&&(rounds<=MAX)){
    if((player!=C) && (player!=D)){
      player=getchar();
      continue;
    }
    if(rounds==MAX){
      break;
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
    
        }
      }
      else{
        me=player;
        putchar(me);
        fflush(stdout);
        putchar('\n');

       }
     

       fflush(stdout);
       player=getchar();
       rounds++;
      
     }
    return 0;
}
