void determine_child(node *parent, char enemy, char friendly)
{
  int row, col;
  
  //***testing
  node *new_node = malloc(sizeof(node));
  if(new_node == NULL){
    printf("malloc fail: _createNode\n");
    exit(EXIT_FAILURE);
  }
  memset(new_node,0,sizeof(node));
  
  //TESTING TO SEE IF AFTER FIRST MOVE STATE (only one spot free on baord)
  int slot_count = 0;
  int pos_x, pos_y;
  for(row = 0; row < BOARD_SIZE; row++){
    for(col = 0; col < BOARD_SIZE; col++){
      if(parent->state[row][col] == 'O'){
	slot_count++;
	pos_x = row;
	pos_y = col;
      }
    }
  }
  
  //if only one open slot, must be first move for agent so choose all
  //adjacent slots to the open one as possible states
  if(slot_count == 1){
    /* above slot */
    if( (pos_x - 1) >= 0){
        /* copy state over to head node */
	_copyBoard(new_node,parent->state);
	/* change state */
	new_node->state[pos_x - 1][pos_y] = 'O';
	/* create child node */
	//create_node(parent,new_node->state);
	_printState(new_node);
    }
    /* below slot */
    if( (pos_x + 1) < BOARD_SIZE){
          /* copy state over to head node */
	_copyBoard(new_node,parent->state);
	/* change state */
	new_node->state[pos_x + 1][pos_y] = 'O';
	/* create child node */
	//create_node(parent,new_node->state);
	_printState(new_node);
    }
    /* left of slot */
    if( (pos_y - 1) >= 0){
          /* copy state over to head node */
	_copyBoard(new_node,parent->state);
	/* change state */
	new_node->state[pos_x][pos_y - 1] = 'O';
	/* create child node */
	//create_node(parent,new_node->state);
	_printState(new_node);
    }
    /* right of slot */
    if( (pos_y + 1) < BOARD_SIZE){
          /* copy state over to head node */
	_copyBoard(new_node,parent->state);
	/* change state */
	new_node->state[pos_x][pos_y + 1] = 'O';
	/* create child node */
	//create_node(parent,new_node->state);
	_printState(new_node);
    }
    
    //return, dont evaluate further
    return;
  }


  //else, evaluate for typical board state

  /* ----- HORIZONTAL ----- */
  for(row = 0; row < BOARD_SIZE; row++){

    /* ----- FORWARDS ----- */
    /* based on friendly, decide what col index to start from */
    if(parent->state[row][0] == friendly)
      col = 0;
    else
      col = 1;

    //for(; col < BOARD_SIZE; col += 2){
      /* check if adjacent friendly spot is open,
	 if so move piece */
    _copyBoard(new_node,parent->state);
    for(; (col < BOARD_SIZE) 
	  && ((col + 2) < BOARD_SIZE)
	  && (parent->state[row][col + 2] == 'O'); col += 2){
	  /* copy state over to head node */
      //_copyBoard(new_node,parent->state);
	/* change state */
	new_node->state[row][col] = 'O';
	new_node->state[row][col + 1] = 'O';
	new_node->state[row][col + 2] = friendly;
	/* create child node */
	//create_node(parent,new_node->state);
	//_printState(new_node);
    }
    //_printState(new_node);
      //}

    /* ----- BACKWARDS ----- */
    /* based on friendly, decide what col index to start from */
    if(parent->state[row][BOARD_SIZE - 1] == friendly)
      col = BOARD_SIZE - 1;
    else
      col = BOARD_SIZE - 2;

    //for(; col > 0; col -= 2){
      /* check if adjacent friendly spot is open,
	 if so move piece */
    _copyBoard(new_node,parent->state); 
    for(; (col > 0)
	  && ((col - 2) >= 0)
	  && (parent->state[row][col - 2] == 'O') ; col -= 2){
	/* copy state over to head node */
	_copyBoard(new_node,parent->state);
	/*change state */
	new_node->state[row][col] = 'O';
	new_node->state[row][col - 1] = 'O';
	new_node->state[row][col - 2] = friendly;
	/* create child node */
	//create_node(parent,new_node->state);
	//_printState(new_node);
    }
    //_printState(new_node);
      //}


  }

  /* ----- VERTICALLY ----- */
  for(col = 0; col < BOARD_SIZE; col++){

    /* ----- FORWARDS ----- */
    /* based on friendly, decide what col index to start from */
    if(parent->state[0][col] == friendly)
      row = 0;
    else
      row = 1;

    //for(; row < BOARD_SIZE; row += 2){
      /* check if adjacent friendly spot is open,
	 if so move piece */
    _copyBoard(new_node,parent->state);
    for(; (row < BOARD_SIZE)
	  && ((row + 2) < BOARD_SIZE)
	  && (parent->state[row + 2][col] == 'O'); row += 2){
	  /* copy state over to head node */
	_copyBoard(new_node,parent->state);
	/* change state */
	new_node->state[row][col] = 'O';
	new_node->state[row + 1][col] = 'O';
	new_node->state[row + 2][col] = friendly;
	/* create child node */
	//create_node(parent,new_node->state);
	//_printState(new_node);
    }
    _printState(new_node);
    //}

    /* ----- BACKWARDS ----- */
    /* based on friendly, decide what col index to start from */
    if(parent->state[BOARD_SIZE - 1][col] == friendly)
      row = BOARD_SIZE - 1;
    else
      row = BOARD_SIZE - 2;

    //for(; row > 0; row -= 2){
      /* check if adjacent friendly spot is open,
	 if so move piece */
    _copyBoard(new_node,parent->state);
    for(; (row > 0) 
	  && ((row - 2) >= 0)
	  && (parent->state[row - 2][col] == 'O'); row -= 2){
	/* copy state over to head node */
	//_copyBoard(new_node,parent->state);
	/*change state */
	new_node->state[row][col] = 'O';
	new_node->state[row - 1][col] = 'O';
	new_node->state[row - 2][col] = friendly;
	/* create child node */
	//create_node(parent,new_node->state);
	//_printState(new_node);
    }
    _printState(new_node);
      //}

    
  }


  free(new_node);

}
