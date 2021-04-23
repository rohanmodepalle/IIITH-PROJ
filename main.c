#include<stdio.h>
#include "graph.c"

int main(){
    printf("Enter number of stations,roads and people\n");
    int num_stations,num_roads,num_people;
    int u=0,v=0,length=0;
    char station_name[50];
    scanf("%d %d %d",&num_stations,&num_roads,&num_people);
    Graph* g = new_graph(num_stations);
    //enter station names
    for(int i=0;i<num_stations;i++){
        scanf("%s",station_name);
        graph_add_vertex(g,station_name);
    }
    //scanf for roads to be entered and stored.
    //format of i-1 for edge number
    // for(int i = 0;i<num_roads;i++){
    //     scanf("%d %d %d",&u,&v,&length);
    //     graph_add_u_edge(g,u,v,length);
    // }
    graph_add_u_edge(g,0,1,10);
    graph_add_u_edge(g,0,3,20);
    graph_add_u_edge(g,0,2,60);
    graph_add_u_edge(g,1,4,30);
    graph_add_u_edge(g,1,2,40);
    graph_add_u_edge(g,2,3,50);
    graph_add_u_edge(g,0,5,15);
    graph_add_u_edge(g,5,4,95);   
    all_paths(g,0,2);
    //shortest_path(g,0,2);
    int** parr;
    parr = all_paths(g,0,2);
    for(int i = 0;i<row;i++){
        for(int j =0;j<column;j++){
            printf("%d ",parr[i][j]);
        }
        printf("\n");
    }
}
