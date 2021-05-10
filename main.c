#include <stdio.h>
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
    //first part of input.
    printf("Enter number of stations, roads and people\n");
    int num_stations, num_roads, num_people;
    int u = 0, v = 0, length = 0;
    char station_name[50];
    scanf("%d %d %d", &num_stations, &num_roads, &num_people);
    peoplecounter = num_people; //essential for list.c

    //initializes graph
    Graph *g = new_graph(num_stations);
    //enter station names as u want it to be, just a fun segment :)
    printf("Enter names of the station:\n");
    for (int i = 0; i < num_stations; i++)
    {
        scanf("%s", station_name);
        //insert vertex with these names into the graph
        graph_add_vertex(g, station_name);
    }
    printf("\n");

    //third part of input which takes in the Bidirectional Paths and the Road Lengths
    printf("Enter the bidirectional paths:\n");
    //scanf for roads to be entered and stored.
    //format of i-1 for edge number
    for (int i = 0; i < num_roads; i++)
    {
        scanf("%d %d %d", &u, &v, &length);
        graph_add_u_edge(g, u - 1, v - 1, length);
    }
    printf("\n");

    //4th part os input which records the station each person is present in at Day 0.
    printf("Enter station number of each person:\n");
    inputppl(num_people);

    //Simulation starts from Day 1 onwards
    int Day = 1;
    char ch = 'D';
    printf("\n");
    printf("\tThe SIMULATION WINDOW HAS STARTED!\n");
    printf("Input 'A' to insert list of covid positive people and display primary and secondary contacts\n");
    printf("Input 'B' to find suitable path from source to destintion, ideally pressed after 'A'\n");
    printf("Input 'C' to record changes in the current station of each person at any day\n");
    printf("Input 'D' to move ahead to the next day of the simulation\n");
    printf("Input 'E' to perform individual station queries \n");
    printf("Input 'F' to perform individual person queries\n");
    printf("Input any other character to exit the entire simulation\n");
    printf("\n");


    while (ch=='A'||ch=='B'||ch=='C'||ch=='D'||ch=='E'||ch=='F')
    {
        printf("For Day: %d, Enter the Query number\n", Day);
        scanf("%s", &ch);
        if (ch == 'A')
        {   
            //new list of covid positive people, hence the previous list of contacts are reset
            reset_list(Day);
            //standard input 
            List *positive_list = new_queue();
            int x;
            int num;
            queue_enqueue(positive_list, Day);
            printf("Enter number of COVID positive people:\n");
            scanf("%d", &num);
            printf("Enter the IDs of the Covid Positive people:\n");
            for (int i = 0; i < num; i++)
            {
                L1: ;
                scanf("%d", &x);
                if(x>peoplecounter)
                {
                    printf("Invalid index, please re-enter: \n");
                    goto L1;
                }
                queue_enqueue(positive_list, x);
            }
            pehlaque(positive_list);
            printf("\n");
        }
        if (ch == 'B')
        {
            int src, dest;
            printf("Enter the stations u want to find the path for:");
            L2: ;
            scanf("%d %d", &src, &dest);
            if(src>num_stations || dest >num_stations)
            {
                printf("Invalid station number, please re-enter: \n");
                goto L2;
            }
            all_paths(g, src - 1, dest - 1);
            printf("\n");
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
                L3: ;
                scanf("%d %d", &pid, &dest);
                if(pid>peoplecounter)
                {
                    printf("Invalid index, please re-enter: \n");
                    goto L3;
                }
                people[pid].source_station = dest;
                movement(Day, pid, dest);
            }
            printf("\n");
        }
        if (ch == 'D')
        {
            stable_transfer(Day);
            Day++;
            printf("\n");
        }
        if (ch == 'E')
        {
            int x;
            printf("Enter Station to be queried\n");
            L4: ;
            scanf("%d", &x);
            if(x>num_stations)
            {
                printf("Invalid station number, please re-enter: \n");
                goto L4;
            }
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
            printf("\n");
        }
        if (ch == 'F')
        {
            individual_person_query();
            printf("\n");
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