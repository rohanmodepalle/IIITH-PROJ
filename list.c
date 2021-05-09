// #include "graph.h"
// #include "graph.c"
// #include "personll.h"
#include "extra.h"
#include "personll.c"
int peoplecounter;

void hello()
{
    printf("hello \n");
}
void pehlaque(List *positive_list)
{
    int d, dcomp; //d->day in which list is given
    d = queue_dequeue(positive_list);
    printf("%d ", d);
    int size = queue_size(positive_list);
    printf("%d ", size);
    //queue of all positive list
    if (d > 15)
    {
        dcomp = d - 15;
    }
    else
    {
        dcomp = 0;
    }
    int p_id; //positive id
    while (size > 0)
    { //on day d
        p_id = queue_dequeue(positive_list);
        printf("%d ", p_id);
        strcpy(people[p_id].string, s4); //s4 = positive
        people[p_id].date = 14;
        for (int i = 1; i <= peoplecounter; i++)
        { //people counter = all people in simulation
            for (int j = dcomp; j < d; j++)
            {
                //s_list for each day =
                if (people[i].s_list[j] == people[p_id].s_list[j] && strcmp(people[i].string, s4) != 0)
                {
                    strcpy(people[i].string, s2); //s2 = primary
                    printf("%d ", i);
                    people[i].infect_day = j; //primary on d-x  || d-x to d-1|| d-15 x= 1 to 15
                }
            }
        }
        size--;
    }
    //d -> d-15 that person got covid
    //1<x<15 d-15,primary contacts (d-15 to d-1)- secondary primary contacts
    List *primary = new_queue();
    for (int i = 1; i <= peoplecounter; i++)
    {
        if (strcmp(people[i].string, s2) == 0)
        { //s2 = primary
            queue_enqueue(primary, i);
        }
    }
    int size_second = queue_size(primary);
    int prim_id;
    while (size_second > 0)
    {
        prim_id = queue_dequeue(primary);
        for (int i = 1; i <= peoplecounter; i++)
        {
            for (int j = people[prim_id].infect_day; j < d; j++)
            {
                if (people[i].s_list[j] == people[prim_id].s_list[j] && strcmp(people[i].string, s4) != 0 && strcmp(people[i].string, s2) != 0)
                {
                    strcpy(people[i].string, s3); //s3 = secondary
                }
            }
        }
        size_second--;
    }

    List *primi = new_queue();
    List *secoi = new_queue();
    for (int i = 1; i <= peoplecounter; i++)
    {
        if (strcmp(people[i].string, s2) == 0)
        {
            queue_enqueue(primi, i);
            printf("p %d", i);
        }
        if (strcmp(people[i].string, s3) == 0)
        {
            queue_enqueue(secoi, i);
            printf("s %d", i);
        }
    }
}
//          0  1 2  3  4
// s_list 1= [2 3 -1 -1 -1]
// s_list 2= [3 3 4 4 -1]
// day 1
// query ask, if any person move??
void movement(int Day, int perid, int Destination)
{
    people[perid].s_list[Day] = Destination;
}
//remember this is only for day = 1 onwards and not less than that
void stable_transfer(int Day)
{
    for (int i = 1; i <= peoplecounter; i++)
    {
        if (people[i].s_list[Day] == -1)
        {
            people[i].s_list[Day] = people[i].s_list[Day - 1];
        }
    }
}
// This function is to reset the status of every primary and secondary 
// contact to neutral
void reset_list(int Day)
{
    for (int i = 1; i <= peoplecounter; i++)
    {
        if (strcmp(people[i].string, s2) == 0 || strcmp(people[i].string, s3) == 0)
        {
            strcpy(people[i].string, s1);
        }
        if (strcmp(people[i].string, s4) == 0)
        {
            people[i].date--;
        }
        if (people[i].date == 0)
        {
            strcpy(people[i].string, s1);
            people[i].date = -1;
        }
    }
}