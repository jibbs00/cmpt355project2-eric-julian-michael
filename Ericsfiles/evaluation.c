#include <stdio.h>
#include <stdlib.h>

int utility ( int board[8][8], char fcolor, char ecolor);
//used for testing ignore 
int main(){
  char c='B';
  const int size=8;
  int board[8][8];
  int count=0, counter=0;

  while( count < size ){
       while(counter<size){
            board[count][counter]='W';
            counter++; }
    count++;}


  utility(board, c);




}

//will evaluate the board and return a number based on the
// number of moves an enemy has
int utility ( int board[8][8], char fcolor, char ecolor ) {
  int count=0, counter=0;
  int size=8;
  int tc=0;
   printf ("%c", color);
   //goes through the board horizontally
 while(count<size){
     while(counter<size){
       if(counter+2<=size){
	    if(ecolor==board[count][counter]&&fcolor==board[count][counter+1]&&board[count][counter+2]=='0'){tc=tc+1;}
       }
       if(counter-2>=0){
	    if(ecolor==board[count][counter]&&fcolor==board[count][counter-1]&&board[count][counter-2]=='0'){tc=tc+1;}
       }

       // printf ( "%c", board[count][counter]);
           counter=counter+1;}
     count++;}
 count=0;
 counter=0;
 //goes through the board vertically
 while(count<size){
   while(counter<size){
     if(count+2<=size){
        if(fcolor==board[counter][count]&&ecolor==board[counter][count+1]&&board[counter][count+2]=='0'){tc=tc+1;}
     }
     if(count-2>=0){
        if(fcolor==board[counter][count]&&ecolor==board[counter][count-1]&&board[counter][count-2]=='0'){tc=tc+1;}
     }
	counter++;}
   count++;}
 return tc;
}
