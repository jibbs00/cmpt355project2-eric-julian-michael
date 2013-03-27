//Micheal text me at 1-780-404-6637 if you have any questions about this code
#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//since i have hardcoded the first and second states of the game will most likely remove the bool variable from this
//function. The node parent should point to the state that needs to be changed and move should be a four element integer
//array with the first and second position being starting location of the piece being moved and the 3rd and 4th position where it is being moved to

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
//----------------------
//copies parent board to child board
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
//---------------------------------------
void determine_child(node *root, char enemy, char friendly){
  int count=0;
  const int size=8;
  int spot[4];
  int counter=0;
  int checker=0;
  node *ptr, *prev;
  bool start=false, first=true;
  root->child_head=ptr;
  //checks if it is the starting state and determines children from there
  //checks if it is the first or second move checker will be 0 if first or 1 if it is the second
  //plan on making this its own function now that i see how large it is. will do tomorrow
	   while(count<size){
	       while(counter<size){
		    if(root->state[count][counter]=='O'){checker++;}
		    counter++;
	       }
	     counter=0;
	     count++;
	   }
	   //------------------
	   count=0;
	   counter=0;
	   //occurs if it is the first move of the game
	   if(checker==0){
	        while(count<4){
		   if(count==0){
		       ptr = malloc( sizeof(node) );
		       root->child_head=root;
		       copyparenttochild(root, ptr);
		       ptr->state[0][0]='O';
		       ptr->parent=root;
		   }
		   if(count==1){
		       prev=ptr;
		       ptr = malloc( sizeof(node) );
		       copyparenttochild(root, ptr);
		       ptr->state[3][3]='O';
		       prev->next=ptr;
		       ptr->parent=root;
		   }
		   if(count==2){
		       prev=ptr;
		       ptr = malloc( sizeof(node) );
		       copyparenttochild(root, ptr);
		       ptr->state[4][4]='O';
		       prev->next=ptr;
		       ptr->parent=root;
		   }

		   if(count==3){
		       prev=ptr;
		       ptr = malloc( sizeof(node) );
		       copyparenttochild(root, ptr);
		       ptr->state[7][7]='O';
		       ptr->parent=root;
		       prev->next=ptr;
		   }
		   
		   count++;
		}
		//retunrs if it was the first move
	   return;   }
	   //-------------------------
	   
	     //occurs if it is the secod move not only one of these if statements should execute
count=0;
	   if(checker==1){
	     while(count<size){
	          while(counter<size){
		       if(root->state[count][counter]=='O'){
			    if(count==0){
			      //first child if top right was choosen previously
			      ptr = malloc( sizeof(node) );
			      root->child_head=ptr;
			      copyparenttochild(root, ptr);
			      ptr->state[0][1]='O';
			      ptr->parent=root;
			      //second child top right was choosen previously
			      prev=ptr;
			      ptr = malloc( sizeof(node) );
      			      copyparenttochild(root, ptr);
			      ptr->state[1][0]='O';
			      ptr->parent=root;
			      prev=ptr;
			      ptr = malloc( sizeof(node) );
			    }
			    //if pos[3][3] was choosen prevously
			    if(count==3){
			      //allocates first child
			      ptr = malloc( sizeof(node) );
			      root->child_head=ptr;
			      copyparenttochild(root, ptr);
			      ptr->state[3][2]='O';
			      ptr->parent=root;
			      prev=ptr;
			      //allocates 2nd child
			      ptr = malloc( sizeof(node) );
			      copyparenttochild(root, ptr);
			      ptr->state[3][4]='O';
			      ptr->parent=root;
			      prev->next=ptr;
			      prev=ptr;
			       //allocates 3rd  child
			      ptr = malloc( sizeof(node) );
			      copyparenttochild(root, ptr);
			      ptr->state[2][3]='O';
			      ptr->parent=root;
			      prev->next=ptr;
			      prev=ptr;
			       //allocates 4th  child
			      ptr = malloc( sizeof(node) );
			      copyparenttochild(root, ptr);
			      ptr->state[4][3]='O';
			      ptr->parent=root;
			      prev->next=ptr;
			      prev=ptr;
			    }
			     //if pos[4][4] was choosen prevously
			    if(count==4){
			      //allocates first child
			      ptr = malloc( sizeof(node) );
			      root->child_head=ptr;
			      copyparenttochild(root, ptr);
			      ptr->state[4][3]='O';
			      ptr->parent=root;
			      prev=ptr;
			      //allocates 2nd child
			      ptr = malloc( sizeof(node) );
			      copyparenttochild(root, ptr);
			      ptr->state[4][5]='O';
			      ptr->parent=root;
			      prev->next=ptr;
			      prev=ptr;
			       //allocates 3rd  child
			      ptr = malloc( sizeof(node) );
			      copyparenttochild(root, ptr);
			      ptr->state[3][4]='O';
			      ptr->parent=root;
			      prev->next=ptr;
			      prev=ptr;
			       //allocates 4th  child
			      ptr = malloc( sizeof(node) );
			      copyparenttochild(root, ptr);
			      ptr->state[5][3]='O';
			      ptr->parent=root;
			      prev->next=ptr;
			      prev=ptr;
			    }
			    if(count==7){
			      //first child if bottom left was choosen previously
			      ptr = malloc( sizeof(node) );
			      root->child_head=ptr;
			      copyparenttochild(root, ptr);
			      ptr->state[7][6]='O';
			      ptr->parent=root;
			      //second child top right was choosen previously
			      prev=ptr;
			      ptr = malloc( sizeof(node) );
      			      copyparenttochild(root, ptr);
			      ptr->state[6][7]='O';
			      ptr->parent=root;
			      prev=ptr;
			      ptr = malloc( sizeof(node) );
			    }
			    

		       }
		      
		       counter++;
		  }
	     counter=0;
	     count++;}
	     //returns occurs ifit was the second move
	     return;  }
	   

  //----------------------------------------------------------------------
  count=0;
  counter=0;
  //checks for children horizontally and creates them as it finds them occurs when it is not the first or second move of the game
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

