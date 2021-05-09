//#include "graph.c"
//=============================================================================
//Author::N Harsha Vardhan
//Dated:: 26th Apr 2021
//Time:: 1:16 AM
//=============================================================================

//=============================================================================
//this is a structure for the elements in the linked lists
//=============================================================================

#ifndef PERSONLL__H__
#define PERSONLL__H__


struct element {
    int data;
    struct element* next;
};

//=============================================================================
//this is the structure for storing various details of the people
//=============================================================================
typedef struct person {
    int infect_day;
    int date;
    char string[10];
    int source_station;
    //=============================================================================
    //this is the structure for storing various details of the people travel itenary
    //=============================================================================
    int dates[15];
    int s_list[60]; //station present per day
    char destination;
}person;

//=============================================================================
//this is a structure for stroing the various information regarding the stations
//=============================================================================

typedef struct tempstats{
    int positive;
    int primary;
    int secondary;
    struct element* root_positive;
    struct element* root_primary;
    struct element* root_secondary;
}tempstats;

#define N 100
struct person people[N];
struct tempstats stations[N];
struct element *createelement(int x);
void insertelement(struct element **head_ref, int new_data);
void deleteelement(struct element** head_ref, int key);
int printlist(struct element *root);
void individual_station_query(int x);
int inputppl(int K);
void printperson(int x);
void individual_person_query();
int stationsquery(struct tempstats stations[]);
void dateconstanter(int index,int station, int x, int y);
void changestatuses(int person,int station);
void traveller(int i);
void printer(int index);

#endif