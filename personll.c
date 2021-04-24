#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include "personll.h"
#define N 5
struct person people[N];
struct tempstats stations[N];

struct element* createelement(int x)
{
    struct element* temp;
    temp=(struct element*)malloc(sizeof(struct element));
    temp->data=x;
    temp->next=NULL;

    return temp;
}
void insertelement(struct element *root,int x)
{
    struct element *temp=createelement(x);
    if(root==NULL)
    {
        root=temp;
    }
    else
    {
        struct element* temp1;
        temp1=(struct element*)malloc(sizeof(struct element));
        temp1=root;
        root=temp;
        root->next=temp1;
    }
}
void printlist(struct element *root)
{
    while(root)
    {
        printf("%d  ",root->data);
    }
}
// int inputppl(int K)
// {
    
//     char s1[] = "Neutral";
//     char s4[]="Positive";
//     char s2[] = "Primary";
//     char s3[] = "Secondary";
//     //people[N] = (struct person *)malloc(N * sizeof(struct person));
//     //stations[N] = (struct tempstats *)malloc(N * sizeof(struct tempstats));
//     for (int i = 1; i <= K; i++)
//     {
//         printf("Enter the source station of %d\n",i);
//         scanf("%d", &people[i].source_station);
//         strcpy(people[i].string, s1);
//         //stations[]
//     }
//     int L = 1; //l=covid positive ppl;
//     for (int i = 1; i <= L; i++)
//     {
//         int x;
//         printf("Enter the index of the positive person \n");
//         scanf("%d", &x);
//         strcpy(people[x].string, s4);
//         stations[people[x].source_station].positive++;
//         stations[people[x].source_station].positive_array[i]=x;
//     }
//     for (int i = 1; i <= K; i++)
//     {
//         if ((stations[people[i].source_station].positive) > 0 && (strcmp(people[i].string,s4)!=0))
//         {
//             stations[people[i].source_station].primary++;
//             strcpy(people[i].string, s2);
//             stations[people[i].source_station].primary_array[i]=i;
//         }
//         else if ((stations[people[i].source_station].primary) > 0 && (stations[people[i].source_station].positive!=0))
//         {
//             stations[people[i].source_station].secondary++;
//             strcpy(people[i].string, s3);
//             stations[people[i].source_station].secondary_array[i]=i;
//         }
//     }
// }
// int printperson(struct person people[],int x)
// {
//     for(int i=1;i<15;i++)
//     {
//         //printf("Day %d",i);
//         people[x].date++;
//         printf("Station=%d Condition=%s Date=%d",people[x].source_station,people[x].string,people[x].date);
//     }
// }
// int stationsquery(struct tempstats stations[],int K)
// {
//     for(int i=1;i<= K; i++)
//     {
//         printf("Station Number: %d\n",i);
//         printf("Positive people=%d\tPrimary People=%d\tSecondary People=%d\n",stations[i].positive,stations[i].primary,stations[i].secondary);
//         printf("The indexes of Positive people are\n");
//         for(int j=0;j<100;j++)
//         {
//             if(stations[i].positive_array[j]!=0)
//             {
//                 printf("%d  ",stations[i].positive_array[j]);
//             }
//         }
//         printf("\n");
//         printf("The indexes of Primary people are\n");
//         for(int j=0;j<100;j++)
//         {
//             if(stations[i].primary_array[j]!=0)
//             {
//                 printf("%d  ",stations[i].primary_array[j]);
//             }
//         }
//         printf("\n");
//         printf("The indexes of secondary people are\n");
//         for(int j=0;j<100;j++)
//         {
//             if(stations[i].secondary_array[j]!=0)
//             {
//                 printf("%d  ",stations[i].secondary_array[j]);
//             }
//         }
//         printf("\n");

//     }
// }
int main()
{
    // int pep;
    // printf("Enter Number of people\n");
    // scanf("%d",&pep);
    // inputppl(pep);
    // int stat;
    // printf("Enter Station To query\n");
    // {
    //     scanf("%d",&stat);
    //     stationsquery(stations,stat);
    // }
    insertelement(stations[0].root_positive,1);
    insertelement(stations[0].root_positive,2);
    insertelement(stations[0].root_positive,6);
    printlist(stations[0].root_positive);
}