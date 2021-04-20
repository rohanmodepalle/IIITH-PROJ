#ifndef __TRIAL__ERR
#define __TRIAL__ERR

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define long long ll

//Node in adjacency list
struct ListNode{
    int dest;
    int weight;
    struct ListNode* next;
};
//structure of adjacency list
struct AdjList{
    //pointer to head of the node
    struct ListNode *head;
};
typedef struct Graph{
    int V;
    struct AdjList* array;
}Graph;

#endif