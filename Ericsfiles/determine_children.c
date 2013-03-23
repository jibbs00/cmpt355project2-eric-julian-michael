
#include <stdio.h>
#include <stdlib.h>
void transitionstate(node *ptr, char action[][]);
void copyparenttochild(node *parent, node *child){
  int count=0;
  int counter=0;
while(counter<size){
    while(count<size){
      child->state[count][counter]=parent->state[count][counter];
      count++;}
    counter++;}


}

void determine_child(node *parent, char enemy, char friendly){
  int count=0;
  const int size=8;
  int spot[2];
  int counter=0;
  node *ptr, *first;
  parent->child_head=first;
  ptr=first;
  //checks for children horizontally
  while(count<size){
	while(counter<size){
	     if(counter+2<=size){
                   if(enemy=parent->state[count][counter]&&friendly==parent->state[count][counter+1]&&parent->state[count][counter+2]=='0'){
		       spot[0]=count;
		       spot[1]=counter;
		       ptr = malloc( sizeof(node) );
		       copyparenttochild(parent, ptr);
		       }
	  }
	     if(counter-2>=0){
	           if(enemy==parent->state[count][counter]&&friendly==parent->state[count][counter-1]&&parent->state[count][counter-2]=='0'){
		      spot[0]=count;
		      spot[1]=counter;}
	  }

	  printf ( "%c", parent->state[count][counter]);
	  counter=counter+1;}
	count++;}



    }}

    }
