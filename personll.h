//#include "graph.c"
//=============================================================================
//Author::N Harsha Vardhan
//Dated:: 26th Apr 2021
//Time:: 1:16 AM
//=============================================================================

//=============================================================================
//this is a structure for the elements in the linked lists
//=============================================================================
struct element {
    int data;
    struct element* next;
};


//=============================================================================
//this is the structure for storing various details of the people
//=============================================================================
struct person {
    int date;
    char string[10];
    int source_station;
    //=============================================================================
    //this is the structure for storing various details of the people travel itenary
    //=============================================================================
    int dates[15];
    char destination;
};
//=============================================================================
//this is a structure for stroing the various information regarding the stations
//=============================================================================
struct tempstats{
    int positive;
    int primary;
    int secondary;
    struct element* root_positive;
    struct element* root_primary;
    struct element* root_secondary;
};
