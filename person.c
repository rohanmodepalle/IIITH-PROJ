#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include "person.h"
#define N 5
struct person people[N];
struct tempstats stations[N];
int inputppl(int K)
{
    
    char s1[] = "Neutral";
    char s4[]="Positive";
    char s2[] = "Primary";
    char s3[] = "Secondary";
    //people[N] = (struct person *)malloc(N * sizeof(struct person));
    //stations[N] = (struct tempstats *)malloc(N * sizeof(struct tempstats));
    for (int i = 0; i < K; i++)
    {
        scanf("%d ", &people[i].source_station);
        strcpy(people[i].string, s1);
        //stations[]
    }
    int L = 1; //l=covid positive ppl;
    for (int i = 0; i < L; i++)
    {
        int x;
        scanf("%d", &x);
        strcpy(people[x].string, s4);
        stations[people[x].source_station].positive++;
        stations[people[x].source_station].positive_array[i]=x;
    }
    for (int i = 0; i < K; i++)
    {
        if ((stations[people[i].source_station].positive) > 0 && strcmp(people[i].string,s4)!=0)
        {
            stations[people[i].source_station].primary++;
            strcpy(people[i].string, s2);
            stations[people[i].source_station].primary_array[i]=i;
        }
        if ((stations[people[i].source_station].primary) > 0 && (stations[people[i].source_station].positive!=0))
        {
            stations[people[i].source_station].secondary++;
            strcpy(people[i].string, s3);
            stations[people[i].source_station].secondary_array[i]=i;
        }
    }
}
int printperson(struct person people[],int x)
{
    for(int i=1;i<15;i++)
    {
        //printf("Day %d",i);
        people[x].date++;
        printf("Station=%d Condition=%s Date=%d",people[x].source_station,people[x].string,people[x].date);
    }
}
int stationsquery(struct tempstats stations[],int K)
{
    for(int i=0;i< K; i++)
    {
        printf("Station Number: %d\n",i+1);
        printf("Positive people=%d\tPrimary People=%d\tSecondary People=%d\n",stations[i].positive,stations[i].primary,stations[i].secondary);
        printf("The indexes of Positive people are\n");
        for(int j=0;j<100;j++)
        {
            if(stations[i].positive_array[j]!=0)
            {
                printf("%d  ",stations[i].positive_array[j]);
            }
        }
        printf("The indexes of Primary people are\n");
        for(int j=0;j<100;j++)
        {
            if(stations[i].primary_array[j]!=0)
            {
                printf("%d  ",stations[i].primary_array[j]);
            }
        }
        printf("The indexes of secondary people are\n");
        for(int j=0;j<100;j++)
        {
            if(stations[i].secondary_array[j]!=0)
            {
                printf("%d  ",stations[i].secondary_array[j]);
            }
        }

    }
}
int main()
{
    inputppl(4);
    stationsquery(stations,3);
}