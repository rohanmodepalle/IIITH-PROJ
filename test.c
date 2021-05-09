#include<stdio.h>
#include "extra.c"
int main(){
    List* test = new_queue();
    queue_enqueue(test,1);
    queue_enqueue(test,2);
    queue_enqueue(test,3);
    queue_enqueue(test,4);
    queue_enqueue(test,5);
    printf("%d ",queue_size(test));
    int d = queue_dequeue(test);
    printf("%d",d);
}