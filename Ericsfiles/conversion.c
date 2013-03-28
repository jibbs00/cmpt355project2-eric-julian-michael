
#include <stdio.h>
#include <stdlib.h>

void conversion(int spot[], char move[]){
  int count=0, counter=0;
  const int size=8;
  if(spot[0]==0&&spot[1]==0){move[0]='A'; 
    move[1]=spot[1]+1;}


  if(spot[0]==1&&spot[1]==0){move[0]='B';
    move[1]=spot[1]+1;}
    

  if(spot[0]==2&&spot[2]==0){move[0]='C';
    move[1]=spot[1]+1;}

     if(spot[0]==3&&spot[1]==0){move[0]='D';
       move[1]=spot[1]+1;}
    

     if(spot[0]==4&&spot[2]==0){move[0]='E';
       move[1]=spot[1]+1;}
    
     if(spot[0]==5&&spot[1]==0){move[0]='F';
       move[1]=spot[1]+1;}
     
     

     if(spot[0]==6&&spot[2]==0){move[0]='G';
       move[1]=spot[1]+1;}
    

     if(spot[0]==7&&spot[1]==0){move[0]='H';
       move[1]=spot[1]+1;}
     

}
int main(){
  int arr[2];
  arr[0]=1;
  arr[1]=3;
  conversion(



}
