#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include "personll.h"
#define N 100
struct person people[N];
struct tempstats stations[N];
char s1[] = "Neutral";
char s4[] = "Positive";
char s2[] = "Primary";
char s3[] = "Secondary";
//=============================================================================
//Author::N Harsha Vardhan
//Dated:: 26th Apr 2021
//Time:: 1:16 AM
//=============================================================================
//Linked Lists Utility function.
//=============================================================================
struct element *createelement(int x)
{
    struct element *temp;
    temp = (struct element *)malloc(sizeof(struct element));
    temp->data = x;
    temp->next = NULL;

    return temp;
}
//=============================================================================
//linked lists insertion function......used root element replacement to trim time complexity
//=============================================================================
void insertelement(struct element **head_ref, int new_data)
{
    /* 1. allocate element */
    struct element *new_element = (struct element *)malloc(sizeof(struct element));

    /* 2. put in the data  */
    new_element->data = new_data;

    /* 3. Make next of new element as head */
    new_element->next = (*head_ref);

    /* 4. move the head to point to the new element */
    (*head_ref) = new_element;
}
//=============================================================================
//linked lists deletion function......
void deleteelement(struct element **head_ref, int key)
{
    // Store head element
    struct element *temp = *head_ref, *prev;

    // If head element itself holds the key to be deleted
    if (temp != NULL && temp->data == key)
    {
        *head_ref = temp->next; // Changed head
        free(temp);             // free old head
        return;
    }

    // Search for the key to be deleted, keep track of the
    // previous element as we need to change 'prev->next'
    while (temp != NULL && temp->data != key)
    {
        prev = temp;
        temp = temp->next;
    }

    // If key was not present in linked list
    if (temp == NULL)
        return;

    // Unlink the element from linked list
    prev->next = temp->next;

    free(temp); // Free memory
}
//=============================================================================
// void insertelement(struct element *root, int x)
// {
//     struct element *temp = createelement(x);
//     // if(root==NULL)
//     // {
//     //     root=temp;
//     // }
//     //else

//     // struct element* temp1;
//     // temp1=(struct element*)malloc(sizeof(struct element));
//     // temp1=root;
//     temp->next = root;
//     root = temp;

//     printf("inserted \n");
// }
//Linked list utility which prints
int printlist(struct element *root)
{
    if (root == NULL)
    {
        printf("This list is empty.\n");
        printf("\n\n\n\n");
        return 0;
    }
    else
    {
        while (root)
        {
            printf("%d  ", root->data);
            root = root->next;
        }
        printf("\n");
    }
    printf("\n\n\n\n");
    return 0;
}
//=============================================================================
//function which individually queries the station that we provide
//=============================================================================
void individual_station_query()
{
    int x;
    printf("Enter The Station To Query\n");
    scanf("%d", &x);
    printf("Station Number: %d\n", x);
    printf("Positive people=%d\tPrimary People=%d\tSecondary People=%d\n", stations[x].positive, stations[x].primary, stations[x].secondary);
    printf("The indexes of total people in the station are\n");
    //printlist(stations[x].total);
    printarray(stations[x].index_arr);
    printf("The indexes of Positive people are\n");
    printlist(stations[x].root_positive);
    //printf("\n");
    printf("The indexes of Primary people are\n");
    printlist(stations[x].root_primary);
    //printf("\n");
    printf("The indexes of secondary people are\n");
    printlist(stations[x].root_secondary);
    //printf("\n");
}
//=============================================================================
//utility input function
//=============================================================================
int inputppl(int K)
{

    //people[N] = (struct person *)malloc(N * sizeof(struct person));
    //stations[N] = (struct tempstats *)malloc(N * sizeof(struct tempstats));
    for (int i = 1; i <= K; i++)
    {
        printf("Enter the source station of %d\n", i);
        scanf("%d", &people[i].source_station);
        strcpy(people[i].string, s1);
        //stations[]
    }
    int L;
    printf("Enter the Number of covid positive people\n");
    scanf("%d", &L);
    //l=covid positive ppl;
    for (int i = 1; i <= L; i++)
    {
        int x;
        printf("Enter the index of the positive person \n");
        scanf("%d", &x);
        strcpy(people[x].string, s4);
        stations[people[x].source_station].positive++;
        insertelement(&stations[people[x].source_station].root_positive, x);
        //insertelement(&stations[people[x].source_station].total, x);
    }
    for (int i = 1; i <= K; i++)
    {
        if ((stations[people[i].source_station].positive) > 0 && (strcmp(people[i].string, s4) != 0))
        {
            stations[people[i].source_station].primary++;
            strcpy(people[i].string, s2);
            insertelement(&stations[people[i].source_station].root_primary, i);
            //insertelement(&stations[people[i].source_station].total, i);
        }
        else if ((stations[people[i].source_station].primary) > 0 && (stations[people[i].source_station].positive != 0) && (strcmp(people[i].string, s4) != 0))
        {
            stations[people[i].source_station].secondary++;
            strcpy(people[i].string, s3);
            insertelement(&stations[people[i].source_station].root_secondary, i);
            //insertelement(&stations[people[i].source_station].total, i);
        }
    }
}
//=============================================================================
//incomplete function
//=============================================================================
void printperson(int x)
{
    for (int i = 1; i < 15; i++)
    {
        //printf("Day %d",i);
        people[x].date++;
        printf("Station=%d Condition=%s Date=%d\n", people[x].source_station, people[x].string, people[x].date);
    }
}
//=============================================================================
//individual query based function
//=============================================================================
void individual_person_query()
{
    int x;
    printf("Enter The Person's Index You Want to Query\n");
    scanf("%d", &x);
    printf("Station=%d\nCondition=%s\nDate=%d\n", people[x].source_station, people[x].string, people[x].date);
    printf("\n\n\n");
}
//=============================================================================
//prints the array
//=============================================================================
void printarray(int *arr)
{
    for(int i=1;i<=N;i++)
    {
        if(arr[i]>0)
        {
            printf("%d ",i);
        }
    }
    printf("\n");
}
//=============================================================================
//prints the situation of all the stations till the given input
//=============================================================================
int stationsquery(struct tempstats stations[])
{
    int K;
    printf("Enter Till Which Station You Want To Query\n");
    scanf("%d", &K);
    for (int i = 1; i <= K; i++)
    {
        printf("Station Number: %d\n", i);
        printf("Positive people=%d\tPrimary People=%d\tSecondary People=%d\n", stations[i].positive, stations[i].primary, stations[i].secondary);
        printf("The indexes of total people in the station are\n");
        //printlist(stations[i].total);
        printarray(stations[i].index_arr);
        printf("The indexes of Positive people are\n");
        printlist(stations[i].root_positive);
        //printf("\n");
        printf("The indexes of Primary people are\n");
        printlist(stations[i].root_primary);
        //printf("\n");
        printf("The indexes of secondary people are\n");
        printlist(stations[i].root_secondary);
        //printf("\n");
    }
}
//=============================================================================
//To uniformanize the dates
//=============================================================================
// void dateconstanter(int index, int station, int x, int y)
// {
//     for (int i = x - 1; i < y; i++)
//     {

//         people[index].dates[i] = station;
//         //printf("%d\n",people[index].dates[i]);
//     }
// }
//=============================================================================
//takes person as input and his station and changes person and station statuses
//=============================================================================
void changestatuses(int person, int station)
{
    if (/*stations[person].primary>0 &&*/ strcmp(people[person].string, s4) != 0)
    {
        strcpy(people[person].string, s3);
        stations[person].secondary++;
        insertelement(&stations[person].root_secondary, person);
        //deleteelement()
    }
}
//=============================================================================
//takes person as input and makes his travel iterinary
//=============================================================================
void traveller(int i)
{
    struct person required_person = people[i];
    int x, y, station;
    printf("Enter the dates and station and enter -1 -1 to terminate\n");

    while (x != -1 && y != -1)
    {
        scanf("%d %d %d", &x, &y, &station);
        dateconstanter(i, station, x, y);
        changestatuses(i, station);
        //inserte
    }
}
// void covidpostiveafterdate()
// {

// }
//=============================================================================
//Util function to print array to test
//=============================================================================
// void printer(int index)
// {
//     for (int i = 0; i < 15; i++)
//     {
//         printf("%d ", people[index].dates[i]);
//     }
// }
//=============================================================================
//Util function for travelling
//=============================================================================
void changestations(int i)
{
    struct person person_use = people[i];
    if((person_use.dates>0))
    {
        printf("Invalid Person, Person is quarantined or positive, Cannot travel\n");
    }
    else
    {
        int x;
        stations[person_use.source_station].index_arr[i]=0;
        printf("Enter Destination\n");
        scanf("%d",&x);
        person_use.source_station=x;
        for(int i= 1; i <= N; i++)
        {
            if(stations[x].index_arr[i]>0)
            {
                person_use.arr[i]=14;
            }
        }
        stations[person_use.source_station].index_arr[i]=1;
    }
}
int q1_primary[100];
int q1_sec[100];
void cleanarr()
{
    for (int i=0;i<100;i++)
    {
        q1_primary[i]=0;
        q1_sec[i]=0;
    }
}
void covidpos(int n,int arr[n])
{
    int z=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n; j++)
        {
            if(people[i].arr[arr[j]]>0)
            {
                q1_primary[z]=i;
                z++;
            }
        }
    }
    z=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n; j++)
        {
            if(people[i].arr[q1_primary[j]]>0)
            {
                q1_sec[z]=i;
                z++;
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        people[arr[i]].dates=14;
    }
}
//=============================================================================
//Util function for cleaning the arrays
//=============================================================================
void cleaner()
{
    for(int i=0;i<N; i++)
    {
        for(int j=0;j<N; j++)
        {
            stations[i].index_arr[j]=0;
            people[i].arr[j]=0;
        }
    }
}
//=============================================================================
//Util function for changing date /decrementing dates
//=============================================================================
void decrementer()
{
    for(int i=1;i<=N;i++)
    {
        for( int j=1;j<=N;j++)
        {
            people[i].arr[j]--;
        }
    }
}
//=============================================================================
//Util function for printing lists in part 1
//=============================================================================
void printtemp(int n,int arr[n])
{
     for(int i=0;i<n;i++)
     {
         if(arr[i]!=0)
         {
             printf("%d ",i);
         }
     }
     printf("\n");
}
//=============================================================================
//main function to test the implementation....there is no interference with the actual peice of code ie the graphs implementation
//=============================================================================
int main()
{
    int pep;
    printf("Enter Number of people\n");
    scanf("%d", &pep);
    //pep=1;
    inputppl(pep);
    int stat;
    cleaner();
    cleanarr();
    //stationsquery(stations);
    //individual_person_query();
    //individual_station_query();
    //printf("Enter ")
    //traveller(1);
    //traveller(0);
    individual_person_query();
    printer(0);
}