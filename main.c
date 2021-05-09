#include <stdio.h>
//#include "graph.h"
#include "graph.c"
#include "list.c"
#include "extra.c"

//#include "personll.c"

//7 9 7
//a b c d e f g
/* 
1 2 10
1 3 20
3 7 60
2 7 50
7 4 20
7 6 30
6 5 80
6 1 90
3 5 100
*/
//for graphs the stations start from 0 to n-1
//for people and station number in other ques it starts from 1 to n
int main()
{
    printf("Enter number of stations,roads and people\n");
    int num_stations, num_roads, num_people;
    int u = 0, v = 0, length = 0;
    char station_name[50];
    scanf("%d %d %d", &num_stations, &num_roads, &num_people);
    peoplecounter = num_people; //for list.c
    Graph *g = new_graph(num_stations);
    //enter station names
    List *primi = new_queue();
    List *secoi = new_queue();
    printf("Enter names of the station:\n");
    for (int i = 0; i < num_stations; i++)
    {
        scanf("%s", station_name);
        graph_add_vertex(g, station_name);
    }
    printf("\n");
    printf("Enter the bidirectional paths:\n");
    //scanf for roads to be entered and stored.
    //format of i-1 for edge number
    for (int i = 0; i < num_roads; i++)
    {
        scanf("%d %d %d", &u, &v, &length);
        graph_add_u_edge(g, u - 1, v - 1, length);
    }
    printf("\n");
    printf("Enter station number of each person: \n");
    inputppl(num_people);
    int Day = 1;
    char ch;
    while (1)
    {
        printf("For Day: %d, Enter the Query number\n", Day);
        scanf("%s", &ch);
        if (ch == 'Q')
        {
            exit(0);
        }
        if (ch == 'A')
        {
            List *positive_list = new_queue();
            int x;
            int num;
            queue_enqueue(positive_list, Day);
            printf("Enter no of covid poitive people:\n");
            scanf("%d", &num);
            //printf("hi");
            printf("Enter the IDs of the Covid Positive people:\n");
            for (int i = 0; i < num; i++)
            {
                scanf("%d", &x);
                queue_enqueue(positive_list, x);
                //printf("%d \n", x);
            }
            //printf("%d \n", queue_size(positive_list));
            int d, dcomp; //d->day in which list is given
            d = queue_dequeue(positive_list);
            //printf("%d \n", d);
            int size = queue_size(positive_list);
            //printf("%d \n", size);
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
                //printf("%d \n", p_id);
                strcpy(people[p_id].string, s4); //s4 = positive
                stations[people[p_id].s_list[d - 1]].positive++;
                people[p_id].date = 14;
                for (int i = 1; i <= peoplecounter; i++)
                { //people counter = all people in simulation
                    for (int j = dcomp; j < d; j++)
                    {
                        //s_list for each day =
                        if (people[i].s_list[j] == people[p_id].s_list[j] && strcmp(people[i].string, s4) != 0)
                        {
                            strcpy(people[i].string, s2); //s2 = primary
                            stations[people[i].s_list[d - 1]].primary++;
                            //printf("%d \n", i);
                            people[i].infect_day = j; //primary on d-x  || d-x to d-1|| d-15 x= 1 to 15
                        }
                    }
                }
                size--;
            }
            //Day D ss D-1
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
                            stations[people[i].s_list[d - 1]].secondary++;
                        }
                    }
                }
                size_second--;
            }

            for (int i = 1; i <= peoplecounter; i++)
            {
                if (strcmp(people[i].string, s2) == 0)
                {
                    queue_enqueue(primi, i);
                    printf("p %d \n", i);
                }
                if (strcmp(people[i].string, s3) == 0)
                {
                    queue_enqueue(secoi, i);
                    printf("s %d\n", i);
                }
            }
        }
        if (ch == 'B')
        {
            int src, dest;
            printf("Enter the stations u want to find the path for:");
            scanf("%d %d", &src, &dest);
            all_paths(g, src - 1, dest - 1);
        }
        if (ch == 'C')
        {
            int changes;
            printf("Enter number of movement changes:\n");
            scanf("%d", &changes);
            printf("Enter Person ID and new destination he reaches on this day:\n");
            for (int i = 0; i < changes; i++)
            {
                int pid, dest;
                scanf("%d %d", &pid, &dest);
                people[pid].source_station = dest;
                movement(Day, pid, dest);
            }
        }
        if (ch == 'D')
        {
            stable_transfer(Day);
            reset_list(Day);
            Day++;
        }
        if (ch == 'E')
        {
            int x;
            printf("Enter Station to be queried\n");
            scanf("%d", &x);
            int ctr1 = 0, ctr2 = 0, ctr3 = 0;
            for (int i = 1; i <= num_people; i++)
            {
                if (people[i].source_station == x)
                {
                    if (strcmp(people[i].string, s4) == 0)
                    {
                        ctr1++;
                        insertelement(&stations[x].root_positive, i);
                    }
                    else if (strcmp(people[i].string, s3) == 0)
                    {
                        ctr2++;
                        insertelement(&stations[x].root_secondary, i);
                    }
                    else if (strcmp(people[i].string, s2) == 0)
                    {
                        ctr3++;
                        insertelement(&stations[x].root_primary, i);
                    }
                    else
                    {
                        printf("Error\n");
                    }
                }
            }
            stations[x].positive = ctr1;
            stations[x].secondary = ctr2;
            stations[x].primary = ctr3;
            individual_station_query(x);
        }
        if (ch == 'F')
        {
            individual_person_query();
        }
    }
}

/* 
input format
input -> num_stations, num_roads, num_ people
input -> station_names //this also adds vertices to the graph which is necessary
input -> enter all the bidirectional paths and the road lengths
input -> for all the number of people we had taken, accept their source stations
day 0 -> source_station
we can just assume simulation for increasing days until "simulation exit is pressed"
    our option window contains-
    1. List of covid positive people //which returns number of primary and secondary contact and their ids
    2. Gives shortest path and safest path between 2 stations....movement is also accepted to go to new destination
    3. Returns status of the person and the station of that day
    4. Go to next day or exit the simulation
when u go to next day, some carry ons are-
people who havent moved, stay in same station, hence the 'stable tansfer' function
all covid positive people day of recover = date-1
*/