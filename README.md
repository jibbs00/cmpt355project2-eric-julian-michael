cmpt355project2-eric-julian-michael
===================================
+++++++++++++++++++++++++++++++++++
repository for CMPT 355 Project 2.  Members: Eric, Julian, Michael

Mar. 19
     Michael: 
     	      Note, for the node states, anything between two zeroes on
     a straight are 0 as well, just cant find a way to represent that now
     (ie 0W0WBWB = 000BWB)
     	      Also, if my code is hard to read or is not understandable,
     its probably because current_node is set weirdly so i have to represent
     current_state->next->next or something liek that because I cant actually
     go to the next state using current_state = current_state->next as it screws
     up creating the nodes (doesnt add the children to the right node)