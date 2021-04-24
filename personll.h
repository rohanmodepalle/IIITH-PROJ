//#include "graph.c"

struct element {
    int data;
    struct node* next;
};
struct person {
    int date;
    char string[10];
    int source_station;
    char destination;
};

struct tempstats{
    int positive;
    int primary;
    int secondary;
    struct node* root_positive;
    struct node* root_primary;
    struct node* root_secondary;
};
