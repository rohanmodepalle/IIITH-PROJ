#include "graph.c"

struct person {
    int date;
    char string[10];
    int source_station;
    char destination;
};

struct element{
    int data;
    struct elemenet* next;
};
struct tempstats{
    int positive;
    int primary;
    int secondary;
    struct element positive[100];
    struct element primary[100];
    struct element negative[100];

};

