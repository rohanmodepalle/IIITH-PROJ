//#include "graph.c"
/* this is a rudimentary array based implementation which sucks both space wise as well as time wise
written just to give a basic idea for the program
written by N Harsha Vardhan .....thanks for reading*/
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
    int positive_array[100];
    int primary_array[100];
    int secondary_array[100];
};
