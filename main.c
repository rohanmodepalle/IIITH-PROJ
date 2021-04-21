#include<stdio.h>
#include "graph.c"

int main(){
    int vertices = 5;
    Graph* g = new_graph(vertices);
    graph_add_vertex(g,"a");
    graph_add_vertex(g,"b");
    graph_add_vertex(g,"c");
    graph_add_vertex(g,"d");
    graph_add_vertex(g,"e");
    //format of i-1 for edge number
    graph_add_u_edge(g,0,1,10);
    graph_add_u_edge(g,0,3,20);
    graph_add_u_edge(g,1,4,30);
    graph_add_u_edge(g,1,2,40);
    graph_add_u_edge(g,2,3,50);   
    //all_paths(g,0,2);
    shortest_path(g,0,2);
}
