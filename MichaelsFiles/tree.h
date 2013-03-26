#ifndef _TREE_H_
#define _TREE_H_

/*** global head pointer used to build min-max tree,
     and tot point to the current state node ***/
extern node *tree_head;

void Build_Tree(char cur_state[][BOARD_SIZE]);



#endif /* _TREE_H_ */
