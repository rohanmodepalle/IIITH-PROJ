#include "graph.c"

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
};