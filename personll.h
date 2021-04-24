//#include "graph.c"

struct element {
    int data;
    struct element* next;
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
    struct element* root_positive;
    struct element* root_primary;
    struct element* root_secondary;
};
