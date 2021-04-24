#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include "person.h"

int inputppl(int K)
{
    struct person *people[K];
    struct tempstats *stations[K];
    char s1[] = "Neutral";
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
        stations[people[x]->source_station]->positive++;
    }
    for (int i = 0; i < K; i++)
    {
        if ((stations[people[i]->source_station]->positive) > 0)
        {
            char s2[] = "Primary";
            strcpy(people[i]->string, s2);
        }
        if ((stations[people[i]->source_station]->primary) > 0)
        {
            char s3[] = "Secondary";
            strcpy(people[i]->string, s3);
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
