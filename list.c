#include "extra.h"
#include "personll.c"

int peoplecounter; //total number of people present in the simulation
void pehlaque(List *positive_list)
{
    int d, dcomp; 
    //first element of the queue is the current day the simulation is present at
    d = queue_dequeue(positive_list);
    int size = queue_size(positive_list);
    //the question stated from day d-x where 1<=x<15
    //if d>15, the above statement is valid otherwise it is essenitally from day-> 0 to d-1.
    if (d > 15)
    {
        dcomp = d - 15;
    }
    else
    {
        dcomp = 0;
    }
    int p_id; //IDs of all the COVID positive people
    while (size > 0)
    { //on day d
        p_id = queue_dequeue(positive_list);
        strcpy(people[p_id].string, s4); //s4 = positive
        stations[people[p_id].s_list[d - 1]].positive++; //increment the positive counter
        people[p_id].date = 14;  //set all the positive people into a 14 day quarantine period
        for (int i = 1; i <= peoplecounter; i++)
        { 
            for (int j = dcomp; j < d; j++)
            {
                if (people[i].s_list[j] == people[p_id].s_list[j] && strcmp(people[i].string, s4) != 0)
                {
                    strcpy(people[i].string, s2); //s2 = primary
                    stations[people[i].s_list[d - 1]].primary++;
                    //noting down the day of infection since they become primary on day d-x and not always on the very first day;
                    people[i].infect_day = j; //primary on d-x  || d-x to d-1|| d-15 x= 1 to 15
                }
            }
        }
        size--;
    }
    //noting down the IDs of all the primary contacts
    List *primary = new_queue();
    for (int i = 1; i <= peoplecounter; i++)
    {
        if (strcmp(people[i].string, s2) == 0)
        {   
            //queueing up all the primary IDs
            queue_enqueue(primary, i);
        }
    }
    int size_second = queue_size(primary);
    int prim_id;
    while (size_second > 0)
    {
        prim_id = queue_dequeue(primary); //ID of each primary person
        for (int i = 1; i <= peoplecounter; i++)
        {
            //for all people in contact with the primary contact within suitable span of days(varaible), they become secondary contacts.
            for (int j = people[prim_id].infect_day; j < d; j++)
            {
                //secondary status is attained only when a person is not primary or positive
                if (people[i].s_list[j] == people[prim_id].s_list[j] && strcmp(people[i].string, s4) != 0 && strcmp(people[i].string, s2) != 0)
                {
                    strcpy(people[i].string, s3); //s3 = secondary
                    stations[people[i].s_list[d - 1]].secondary++;
                }
            }
        }
        size_second--;
    }
    //we have used order of precedence to award statuses. the order: positive>primary>secondary
    List *primi = new_queue();
    List *secoi = new_queue();
    for (int i = 1; i <= peoplecounter; i++)
    {
        if (strcmp(people[i].string, s2) == 0)
        {
            queue_enqueue(primi, i);
            printf("Primary Contact ID: %d \n", i);
        }
        if (strcmp(people[i].string, s3) == 0)
        {
            queue_enqueue(secoi, i);
            printf("Secondary Contact ID: %d\n", i);
        }
    }
}

//this function accounts for and records the Destination a person reaches on a particular Day.
void movement(int Day, int perid, int Destination)
{
    //only if person is not positive, he can move to another station
    if (people[perid].date == -1)
    {
        people[perid].s_list[Day] = Destination;
    }
    else
    {
        printf("The person has COVID-19 and is currently under quarantine.");
    }
}

//this function ensures that all the people who havent legally moved to another destination are still present in the same station on that day
void stable_transfer(int Day)
{
    for (int i = 1; i <= peoplecounter; i++)
    {
        if (people[i].s_list[Day] == -1)
        {
            //if person hasn't moved, then the station he would be present in is the same as the station he was in the previous day
            people[i].s_list[Day] = people[i].s_list[Day - 1];
        }
    }
}

//after the execution of the code and finding primary and secondary contacts on that day, the list changes
//for another day. Hence, except for the 'positive' status, everythign else is reset.
void reset_list(int Day)
{
    for (int i = 1; i <= peoplecounter; i++)
    {
        //if person was classified as primary or secondary, they are set back to neutral
        if (strcmp(people[i].string, s2) == 0 || strcmp(people[i].string, s3) == 0)
        {
            strcpy(people[i].string, s1);
        }
        //if person was tested 'positive' his 14 day qurantine session has begun and he is decremented by 1 as we move along the days
        if (strcmp(people[i].string, s4) == 0)
        {
            people[i].date--;
        }
        //if days=0, then he is free from covid and well to do
        //CONGRATULATIONS, he is attains the neutra status.
        if (people[i].date == 0)
        {
            strcpy(people[i].string, s1);
            people[i].date = -1;
        }
    }
}