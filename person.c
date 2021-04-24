#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include "person.h"
#define N 100
struct person *people[N];
struct tempstats *stations[N];
int inputppl(int K)
{
    
    char s1[] = "Neutral";
    char s4[]="Positive";
    char s2[] = "Primary";
    char s3[] = "Secondary";
    people[K] = (struct person *)malloc(K * sizeof(struct person));
    stations[K] = (struct tempstats *)malloc(K * sizeof(struct tempstats));
    for (int i = 0; i < K; i++)
    {
        scanf("%d", &people[i]->source_station);
        strcpy(people[i]->string, s1);
    }
    int L = 10; //l=covid positive ppl;
    for (int i = 0; i < L; i++)
    {
        int x;
        scanf("%d", &x);
        strcpy(people[i]->string, s4);
        stations[people[x]->source_station]->positive++;
        stations[people[x]->source_station]->positive_array[i]=x;
    }
    for (int i = 0; i < K; i++)
    {
        if ((stations[people[i]->source_station]->positive) > 0 && strcmp(people[i]->string,s4)!=0)
        {
            stations[people[i]->source_station]->primary++;
            strcpy(people[i]->string, s2);
            stations[people[i]->source_station]->primary_array[i]=i;
        }
        if ((stations[people[i]->source_station]->primary) > 0 && (stations[people[i]->source_station]->positive!=0))
        {
            stations[people[i]->source_station]->secondary++;
            strcpy(people[i]->string, s3);
            stations[people[i]->source_station]->secondary_array[i]=i;
        }
    }
}
int printperson(struct person *people[],int x)
{
    for(int i=1;i<15;i++)
    {
        //printf("Day %d",i);
        people[x]->date++;
        printf("Station=%d Condition=%s Date=%d",people[x]->source_station,people[x]->string,people[x]->date);
    }
}
