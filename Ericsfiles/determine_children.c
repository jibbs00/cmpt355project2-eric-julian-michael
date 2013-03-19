
#include <stdio.h>
#include <stdlib.h>


void determine_child(node *child, node *parent, char enemy, char friendly, string lastmovedetermined){
  int count=0;
  const int size=8;
  int spot[2];
  int counter=0;
  while(counter<size){
    while(count<size){
      child->state[count][counter]=parent->state[count][counter];
      count++;}
    counter++;}

  count=0;
  counter=0;      
  while(count<size){
	while(counter<size){
	  if(counter+2<=size){
            if(ecolor=parent->state[count][counter]&&fcolor==parent->state[count][counter+1]&&parent->state[count][counter+2]=='0'){spot[0]=count;
	      spot[1]=counter;}
	  }
	  if(counter-2>=0){
            if(ecolor==parent->state[count][counter]&&fcolor==parent->state[count][counter-1]&&parent->state[count][counter-2]=='0'){spot[0]=count;
	      spot[1]=counter;}
	  }

	  printf ( "%c", parent->state[count][counter]);
	  counter=counter+1;}
	count++;}



    }}

    }
