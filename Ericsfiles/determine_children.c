#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
void applymove(node *parent, bool removeone, int move[]){
  int count, counter;
  char startingcolor;
  count=move[0];
  counter=move[1];
  startingcolor=parent->state[count][counter];
  parent->state[count][counter]='O';
  if(removeone==true)return;
  //checks to see if moving along same row and applies move if it is  
if(count==move[2]){
      if(counter<move[3]){
	  while(counter<move[3]){parent->state[count][counter]='O';
	        counter++;
	  }
	 parent->state[count][counter]=startingcolor;
      }
      if(counter>move[3]){
	  while(counter>move[3]){parent->state[count][counter]='O';
	        counter--;
	  }
	  parent->state[count][counter]=startingcolor;
      }
  }
//checks to see if moving along the colum and applies move if it is
if(counter==move[3]){
      if(counter<move[2]){
	  while(count<move[2]){parent->state[count][counter]='O';
	        count++;
	  }
	  parent->state[count][counter]=startingcolor;
      }
      if(counter>move[2]){
	  while(count>move[2]){parent->state[count][counter]='O';
	        count--;
	  }
	  parent->state[count][counter]=startingcolor;
      }
  }

}
  
void copyparenttochild(node *parent, node *child){
  int count=0;
  int counter=0;
const int size=8;
while(counter<size){
    while(count<size){
      child->state[count][counter]=parent->state[count][counter];
      count++;}
    counter++;}


}

void determine_child(node *root, char enemy, char friendly){
  int count=0;
  const int size=8;
  int spot[4];
  int counter=0;
  node *ptr, *prev;
  bool start=false, first=true;
  root->child_head=ptr;
  
  //checks for children horizontally and creates them as it finds them
  while(count<size){
	while(counter<size){
	     if(counter+2<=size){
                   if(enemy=root->state[count][counter]&&friendly==root->state[count][counter+1]&&root->state[count][counter+2]=='0'){
		       if(first==false){prev=ptr;}
		       spot[0]=count;
		       spot[1]=counter;
		       spot[2]=count;
		       spot[3]=counter+2;
		       ptr = malloc( sizeof(node) );
		       copyparenttochild(root, ptr);
		       applymove(ptr, start, spot);
		       if(first==false)prev->next=ptr;
		       ptr->parent=root;
		       first=false;}
	  }
	     if(counter-2>=0){
	           if(enemy==root->state[count][counter]&&friendly==root->state[count][counter-1]&&root->state[count][counter-2]=='0'){
		     if(first==false)prev=ptr; 
		     spot[0]=count;
		      spot[1]=counter;
		        spot[2]=count;
		       spot[3]=counter-2;
		       ptr = malloc( sizeof(node) );
		       copyparenttochild(root, ptr);
		       applymove(ptr, start, spot);
		       if(first==false) prev->next=ptr;
		       ptr->parent=root;
		       first=false;}
	     }
	  

	  counter=counter+1;}
        counter=0;
	count++;}
count=0;
counter=0;
//checks for children vertically and creates them if found
while(counter<size){
	while(count<size){
	     if(count+2<=size){
                   if(enemy=root->state[count][counter]&&friendly==root->state[count+1][counter]&&root->state[count+2][counter]=='0'){
		       if(first==false){prev=ptr;}
		       spot[0]=count;
		       spot[1]=counter;
		       spot[2]=count+2;
		       spot[3]=counter;
		       ptr = malloc( sizeof(node) );
		       copyparenttochild(root, ptr);
		       applymove(ptr, start, spot);
		       if(first==false)prev->next=ptr;
		       ptr->parent=root;
		       first=false;}
	  }
	     if(count-2>=0){
	           if(enemy==root->state[count][counter]&&friendly==root->state[count-1][counter]&&root->state[count-2][counter]=='0'){
		     if(first==false)prev=ptr; 
		     spot[0]=count;
		      spot[1]=counter;
		        spot[2]=count-2;
		       spot[3]=counter;
		       ptr = malloc( sizeof(node) );
		       copyparenttochild(root, ptr);
		       applymove(ptr, start, spot);
		       if(first==false) prev->next=ptr;
		       ptr->parent=root;
		       first=false;}
	     }


	     count++; }
	count=0;
	counter++;
}

}   

