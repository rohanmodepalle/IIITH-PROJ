#ifndef EXTRA__H__
#define EXTRA__H__

#include <stdbool.h>
//LIST
typedef struct list List;
// create a new list and return a pointer to it
List *new_list();
//free the memory of list
void free_list(List *list);
// add an element to the front of a list-O(1)
void list_add_start(List *list, int data);
// add an element to the back of a list-O(1)
void list_add_end(List *list, int data);
// remove and return the front data element from a list-O(1),ensure list_size() > 0
int list_remove_start(List *list);
// remove and return the final data element in a list-O(n),ensure list_size() > 0
int list_remove_end(List *list);
// return the number of elements contained in a list
int list_size(List *list);
// returns whether the list contains no elements (true) or some elements (false)
bool list_is_empty(List *list);

//STACK
List *new_stack();
// destroy a queue and free its memory
void free_stack(List *stack);
// push an element to the stack (adds to front of stack)-O(1)
void stack_push(List *stack, int data);
// pop and return an element from the stack (removes from front of stack)-O(1)
int stack_pop(List *stack);
// return the number of elements contained in a stack
int stack_size(List *stack);
// returns whether the stack contains no elements (true) or some elements (false)
bool stack_is_empty(List *stack);

//QUEUE
// create a new queue and return a pointer to it
List *new_queue();
// destroy a queue and free its memory
void free_queue(List *queue);
// enqueue an element (adds to end of queue)-O(1)
void queue_enqueue(List *queue, int data);
// dequeue and return an element (removes from front of queue)-O(1)
int queue_dequeue(List *queue);
// return the number of elements contained in a queue
int queue_size(List *queue);
// returns whether the queue contains no elements (true) or some elements (false)
bool queue_is_empty(List *queue);

#endif