#ifndef _LIST_H_
#define _LIST_H_

struct List {
    struct ListNode * head;
    struct ListNode * tail;
    int count;
};

struct ListNode {
    void * data;
    struct ListNode * next;
};

struct List * new_list( void );
void delete_list( struct List ** list );

void add_front( struct List ** list, void * data );

#endif /* _LIST_H_ */
