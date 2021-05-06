#include <stdlib.h>
#include <assert.h>
#include "extra.h"

//LIST
typedef struct node Node;
//points to the next node in the list, and to some data
struct node {
    int data;
    Node *next;
};
//points to its first and last nodes, and stores its size (num. nodes)
struct list {
    int size;
    Node *head;
    Node *tail;
};
//create a new node and return its address
Node *new_node() {
    Node *node = malloc(sizeof *node);
    assert(node);
    
    return node;
}
// helper function to clear memory of a node
void free_node(Node *node) {
    free(node);
}
// create a new list and return a pointer to it
List *new_list() {
    List *list = malloc(sizeof *list);
    assert(list);
    
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}
// destroy a list and free its memory
void free_list(List *list) {
    assert(list != NULL);
    // free each node
    Node *node = list->head;
    Node *next;
    while (node) {
        next = node->next;
        free_node(node);
        node = next;
    }
    // free the list struct itself
    free(list);
}
// add an element to the front of a list-O(1)
void list_add_start(List *list, int data) {
    assert(list != NULL);
    // create and initialise a new list node
    Node *node = new_node();
    node->data = data;
    node->next = list->head; // next will be the old first node (may be null)
    // place it at the start of the list
    list->head = node;
    // if list was empty, this new node is also the last node now
    if(list->size == 0) {
        list->tail = node;
    }
    // and we need to keep size updated!
    list->size++;
}
// add an element to the back of a list-O(1)
void list_add_end(List *list, int data) {
    assert(list != NULL);
    // we'll need a new list node to store this data
    Node *node = new_node();
    node->data = data;
    node->next = NULL; // as the last node, there's no next node
    if(list->size == 0) {
        // if the list was empty, new node is now the first node
        list->head = node;
    } else {
        // otherwise, it goes after the current last node
        list->tail->next = node;
    }
    // place this new node at the end of the list
    list->tail = node;
    // and keep size updated too
    list->size++;
}
// remove and return the front data element from a list-O(1)
int list_remove_start(List *list) {
    assert(list != NULL);
    assert(list->size > 0);
    
    // we'll need to save the data to return it
    Node *start_node = list->head;
    int data = start_node->data;
    
    // then replace the head with its next node (may be null)
    list->head = list->head->next;
    
    // if this was the last node in the list, the tail also needs to be cleared
    if(list->size == 1) {
        list->tail = NULL;
    }
    
    // the list is now one node smaller
    list->size--;
    
    // and we're finished with the node holding this data
    free_node(start_node);
    
    // done!
    return data;
}

// remove and return the final data element in a list- O(n), 
int list_remove_end(List *list) {
    assert(list != NULL);
    assert(list->size > 0);
    
    // we'll need to save the data to return it
    Node *end_node = list->tail;
    int data = end_node->data;
    
    // then replace the tail with the second-last node (may be null)
    // (to find this replacement, we'll need to walk the list --- the O(n) bit
    Node *node = list->head;
    Node *prev = NULL;
    while (node->next) {
        prev = node;
        node = node->next;
    }
    list->tail = prev;
    
    if(list->size == 1) {
        // if we're removing the last node, the head also needs clearing
        list->head = NULL;
    } else {
        // otherwise, the second-last node needs to drop the removed last node
        prev->next = NULL;
    }
    
    // the list just got one element shorter
    list->size--;
    
    // we're finished with the list node holding this data
    free_node(end_node);
    
    // done!
    return data;
}
// return the number of elements contained in a list
int list_size(List *list) {
    assert(list != NULL);
    return list->size;
}
// returns whether the list contains no elements (true) or some elements (false)
bool list_is_empty(List *list) {
    assert(list != NULL);
    return (list->size==0);
}

//STACK
// create a new stack and returns a pointer to it
List *new_stack() {
    return new_list();
}
// destroy a stack and free its memory
void free_stack(List *stack) {
    free_list(stack);
}
// push an element to the stack (adds to front of stack)-O(1)
void stack_push(List *stack, int data) {
    list_add_start(stack, data);
}
// pop and return an element from the stack (removes from front of stack)-O(1)
int stack_pop(List *stack) {
    return list_remove_start(stack);
}
// return the number of elements contained in a stack
int stack_size(List *stack) {
    return list_size(stack);
}
// returns whether the stack contains no elements (true) or some elements (false)
bool stack_is_empty(List *stack) {
    return list_is_empty(stack);
}

//QUEUE
// create a new queue and reutrn a pointer to it
List *new_queue() {
    return new_list();
}
// destroy a queue and free its memory
void free_queue(List *queue) {
    free_list(queue);
}
// enqueue an element (adds to end of queue)-O(1)
void queue_enqueue(List *queue, int data) {
    list_add_end(queue, data);
}
// dequeue and return an element (removes from front of queue)-O(1)
int queue_dequeue(List *queue) {
    return list_remove_start(queue);
}
// return the number of elements contained in a queue
int queue_size(List *queue) {
    return list_size(queue);
}
// returns whether the queue contains no elements (true) or some elements (false)
bool queue_is_empty(List *queue) {
    return list_is_empty(queue);
}